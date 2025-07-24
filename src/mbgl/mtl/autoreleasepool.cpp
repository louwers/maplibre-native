#include <mbgl/mtl/autoreleasepool.hpp>

extern "C" void* objc_autoreleasePoolPush(void);
extern "C" void objc_autoreleasePoolPop(void*);

namespace mbgl::util {
AutoReleasePool::AutoReleasePool()
    : pool(objc_autoreleasePoolPush()) {}

AutoReleasePool::~AutoReleasePool() {
    objc_autoreleasePoolPop(pool);
}

}; // namespace mbgl::util
