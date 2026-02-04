#pragma once

#include <mbgl/actor/scheduler.hpp>

namespace mbgl {
namespace test {

/// Returns a shared ThreadPoolHandle for all tests.
/// This mimics the production pattern of sharing a pool across components.
inline ThreadPoolHandle& getThreadPoolHandle() {
    static ThreadPoolHandle handle = ThreadPoolHandle::create();
    return handle;
}

} // namespace test
} // namespace mbgl
