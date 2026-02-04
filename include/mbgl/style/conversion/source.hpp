#pragma once

#include <mbgl/actor/scheduler.hpp>
#include <mbgl/style/source.hpp>
#include <mbgl/style/conversion.hpp>

#include <memory>
#include <optional>

namespace mbgl {
namespace style {
namespace conversion {

template <>
struct Converter<std::unique_ptr<Source>> {
public:
    std::optional<std::unique_ptr<Source>> operator()(const Convertible& value,
                                                      Error& error,
                                                      const std::string& id,
                                                      const ThreadPoolHandle& threadPoolHandle) const;
};

} // namespace conversion
} // namespace style
} // namespace mbgl
