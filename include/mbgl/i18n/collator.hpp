#pragma once

#include <optional>

#include <memory>
#include <string>

namespace mbgl {
namespace platform {

class Collator {
public:
    explicit Collator(bool caseSensitive, bool diacriticSensitive, const std::optional<std::string>& locale = std::nullopt);
    int compare(const std::string& lhs, const std::string& rhs) const;
    std::string resolvedLocale() const;
    bool operator==(const Collator& other) const;

private:
    class Impl;
    std::shared_ptr<Impl> impl;
};

} // namespace platform
} // namespace mbgl
