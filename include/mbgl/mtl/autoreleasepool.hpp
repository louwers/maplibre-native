// RAII wrapper for an autorelease pool

namespace mbgl::util {
struct AutoReleasePool {
    void* pool;
    AutoReleasePool();
    ~AutoReleasePool();
};
} // namespace mbgl::util
