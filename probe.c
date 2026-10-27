// Creates and destroys a Vulkan instance + device + compute pipeline in a loop and reports how
// many pthread keys are still available after each iteration.
#define _GNU_SOURCE
#include <dlfcn.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

#define CK(x) \
    do { \
        VkResult r_ = (x); \
        if (r_ != VK_SUCCESS) { \
            fprintf(stderr, "%s failed: %d (line %d)\n", #x, (int)r_, __LINE__); \
            exit(2); \
        } \
    } while (0)

// Counts free keys by exhausting them through libc directly (bypassing any LD_PRELOAD shim).
static int free_keys(void) {
    static int (*create)(pthread_key_t*, void (*)(void*));
    static int (*del)(pthread_key_t);
    if (!create) {
        void* h = dlopen("libc.so.6", RTLD_NOW);
        create = dlsym(h, "pthread_key_create");
        del = dlsym(h, "pthread_key_delete");
    }
    pthread_key_t ks[4096];
    int n = 0;
    while (n < 4096 && create(&ks[n], NULL) == 0) n++;
    for (int i = 0; i < n; i++) del(ks[i]);
    return n;
}

static uint32_t* load_spv(const char* path, size_t* size) {
    FILE* f = fopen(path, "rb");
    if (!f) {
        perror(path);
        exit(2);
    }
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint32_t* buf = malloc(n);
    if (fread(buf, 1, n, f) != (size_t)n) exit(2);
    fclose(f);
    *size = (size_t)n;
    return buf;
}

static void run_once(const uint32_t* spv, size_t spv_size, int verbose) {
    VkApplicationInfo app = {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                             .pApplicationName = "probe",
                             .apiVersion = VK_API_VERSION_1_1};
    VkInstanceCreateInfo ici = {.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, .pApplicationInfo = &app};
    VkInstance inst;
    CK(vkCreateInstance(&ici, NULL, &inst));

    uint32_t n = 0;
    CK(vkEnumeratePhysicalDevices(inst, &n, NULL));
    if (n == 0) {
        fprintf(stderr, "no physical devices\n");
        exit(2);
    }
    if (n > 8) n = 8;
    VkPhysicalDevice pds[8];
    VkResult er = vkEnumeratePhysicalDevices(inst, &n, pds);
    if (er != VK_SUCCESS && er != VK_INCOMPLETE) CK(er);
    VkPhysicalDevice pd = pds[0];
    if (verbose) {
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(pd, &props);
        printf("device: %s (driver version 0x%x, %u device(s))\n", props.deviceName, props.driverVersion, n);
    }

    uint32_t qn = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(pd, &qn, NULL);
    if (qn > 16) qn = 16;
    VkQueueFamilyProperties qp[16];
    vkGetPhysicalDeviceQueueFamilyProperties(pd, &qn, qp);
    uint32_t qf = UINT32_MAX;
    for (uint32_t i = 0; i < qn; i++) {
        if (qp[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
            qf = i;
            break;
        }
    }
    if (qf == UINT32_MAX) {
        fprintf(stderr, "no compute queue\n");
        exit(2);
    }

    float prio = 1.0f;
    VkDeviceQueueCreateInfo qci = {.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                                   .queueFamilyIndex = qf,
                                   .queueCount = 1,
                                   .pQueuePriorities = &prio};
    VkDeviceCreateInfo dci = {.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                              .queueCreateInfoCount = 1,
                              .pQueueCreateInfos = &qci};
    VkDevice dev;
    CK(vkCreateDevice(pd, &dci, NULL, &dev));
    VkQueue queue;
    vkGetDeviceQueue(dev, qf, 0, &queue);

    VkShaderModuleCreateInfo smci = {.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
                                     .codeSize = spv_size,
                                     .pCode = spv};
    VkShaderModule sm;
    CK(vkCreateShaderModule(dev, &smci, NULL, &sm));
    VkPipelineLayoutCreateInfo plci = {.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};
    VkPipelineLayout pl;
    CK(vkCreatePipelineLayout(dev, &plci, NULL, &pl));
    VkComputePipelineCreateInfo cpci = {.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
                                        .stage = {.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                                                  .stage = VK_SHADER_STAGE_COMPUTE_BIT,
                                                  .module = sm,
                                                  .pName = "main"},
                                        .layout = pl};
    VkPipeline pipe;
    CK(vkCreateComputePipelines(dev, VK_NULL_HANDLE, 1, &cpci, NULL, &pipe));

    VkCommandPoolCreateInfo cpi = {.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, .queueFamilyIndex = qf};
    VkCommandPool pool;
    CK(vkCreateCommandPool(dev, &cpi, NULL, &pool));
    VkCommandBufferAllocateInfo cbai = {.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                                        .commandPool = pool,
                                        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                                        .commandBufferCount = 1};
    VkCommandBuffer cb;
    CK(vkAllocateCommandBuffers(dev, &cbai, &cb));
    VkCommandBufferBeginInfo cbbi = {.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
    CK(vkBeginCommandBuffer(cb, &cbbi));
    vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_COMPUTE, pipe);
    vkCmdDispatch(cb, 4, 1, 1);
    CK(vkEndCommandBuffer(cb));

    VkFenceCreateInfo fci = {.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};
    VkFence fence;
    CK(vkCreateFence(dev, &fci, NULL, &fence));
    VkSubmitInfo si = {.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .commandBufferCount = 1, .pCommandBuffers = &cb};
    CK(vkQueueSubmit(queue, 1, &si, fence));
    CK(vkWaitForFences(dev, 1, &fence, VK_TRUE, UINT64_MAX));
    CK(vkDeviceWaitIdle(dev));

    vkDestroyFence(dev, fence, NULL);
    vkDestroyCommandPool(dev, pool, NULL);
    vkDestroyPipeline(dev, pipe, NULL);
    vkDestroyPipelineLayout(dev, pl, NULL);
    vkDestroyShaderModule(dev, sm, NULL);
    vkDestroyDevice(dev, NULL);
    vkDestroyInstance(inst, NULL);
}

int main(int argc, char** argv) {
    const char* spv_path = argc > 1 ? argv[1] : "probe.spv";
    int iters = argc > 2 ? atoi(argv[2]) : 40;
    size_t spv_size;
    uint32_t* spv = load_spv(spv_path, &spv_size);
    int (*live)(void) = (int (*)(void))dlsym(RTLD_DEFAULT, "keyshim_live");

    int base = free_keys();
    printf("baseline free keys: %d\n", base);
    int first = 0, last = 0;
    for (int i = 0; i < iters; i++) {
        run_once(spv, spv_size, i == 0);
        int f = free_keys();
        if (i == 2) first = f;
        last = f;
        printf("iter %2d: free keys %d (%+d vs baseline)", i, f, f - base);
        if (live) printf(", shim live %d", live());
        printf("\n");
        fflush(stdout);
    }
    if (iters > 3) {
        printf("RESULT: %d key(s) leaked over %d iterations after warm-up (%.2f per iteration)\n", first - last,
               iters - 3, (double)(first - last) / (iters - 3));
    }
    void (*report)(void) = (void (*)(void))dlsym(RTLD_DEFAULT, "keyshim_report");
    if (report) report();
    return 0;
}
