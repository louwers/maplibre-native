// LD_PRELOAD shim: tracks live pthread/C11 TSS keys with the call stack that created each one.
#define _GNU_SOURCE
#include <dlfcn.h>
#include <execinfo.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

#define MAXK 4096
static char* stacks[MAXK];
static int live, total;
static pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
static __thread int busy;

static char* capture(void) {
    const char* e = getenv("KEYSHIM_FRAMES");
    int want = e ? atoi(e) : 16;
    if (want > 48) want = 48;
    void* bt[64];
    int n = backtrace(bt, want + 2);
    char buf[8192];
    size_t len = 0;
    buf[0] = 0;
    for (int i = 2; i < n && len < sizeof buf - 300; i++) {
        Dl_info di;
        if (dladdr(bt[i], &di) && di.dli_fname) {
            const char* m = strrchr(di.dli_fname, '/');
            m = m ? m + 1 : di.dli_fname;
            len += snprintf(buf + len, sizeof buf - len, "%s%s+0x%lx", len ? " < " : "", m,
                            (unsigned long)((char*)bt[i] - (char*)di.dli_fbase));
            if (di.dli_sname) len += snprintf(buf + len, sizeof buf - len, "(%s)", di.dli_sname);
        } else {
            len += snprintf(buf + len, sizeof buf - len, "%s?", len ? " < " : "");
        }
    }
    return strdup(buf);
}

static void on_create(unsigned k) {
    if (busy) return;
    busy = 1;
    char* s = capture();
    pthread_mutex_lock(&mu);
    if (k < MAXK) {
        free(stacks[k]);
        stacks[k] = s;
    } else {
        free(s);
    }
    live++;
    total++;
    pthread_mutex_unlock(&mu);
    busy = 0;
}

static void on_delete(unsigned k) {
    if (busy) return;
    busy = 1;
    pthread_mutex_lock(&mu);
    if (k < MAXK) {
        free(stacks[k]);
        stacks[k] = NULL;
    }
    live--;
    pthread_mutex_unlock(&mu);
    busy = 0;
}

int keyshim_live(void) { return live; }

void keyshim_report(void) {
    static char done[MAXK];
    pthread_mutex_lock(&mu);
    fprintf(stderr, "keyshim: created=%d live=%d\n", total, live);
    memset(done, 0, sizeof done);
    for (int i = 0; i < MAXK; i++) {
        if (!stacks[i] || done[i]) continue;
        int count = 0;
        for (int j = i; j < MAXK; j++) {
            if (stacks[j] && !done[j] && strcmp(stacks[i], stacks[j]) == 0) {
                done[j] = 1;
                count++;
            }
        }
        fprintf(stderr, "keyshim: %d live key(s) created at: %s\n", count, stacks[i]);
    }
    pthread_mutex_unlock(&mu);
}

int pthread_key_create(pthread_key_t* k, void (*d)(void*)) {
    static int (*real)(pthread_key_t*, void (*)(void*));
    if (!real) real = dlsym(RTLD_NEXT, "pthread_key_create");
    int r = real(k, d);
    if (r == 0) {
        on_create(*k);
    } else {
        fprintf(stderr, "keyshim: pthread_key_create failed (%d)\n", r);
        keyshim_report();
    }
    return r;
}

int pthread_key_delete(pthread_key_t k) {
    static int (*real)(pthread_key_t);
    if (!real) real = dlsym(RTLD_NEXT, "pthread_key_delete");
    int r = real(k);
    if (r == 0) on_delete(k);
    return r;
}

// glibc's tss_create calls its internal __pthread_key_create, which bypasses the hooks above.
int tss_create(tss_t* k, tss_dtor_t d) {
    static int (*real)(tss_t*, tss_dtor_t);
    if (!real) real = dlsym(RTLD_NEXT, "tss_create");
    int r = real(k, d);
    if (r == thrd_success) on_create((unsigned)*k);
    return r;
}

void tss_delete(tss_t k) {
    static void (*real)(tss_t);
    if (!real) real = dlsym(RTLD_NEXT, "tss_delete");
    real(k);
    on_delete((unsigned)k);
}

__attribute__((destructor)) static void keyshim_fini(void) {
    if (getenv("KEYSHIM_REPORT_AT_EXIT")) keyshim_report();
}
