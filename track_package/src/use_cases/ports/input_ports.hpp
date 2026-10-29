// [Layer 2 — Use Cases]
// Dependency Rule: depends only on Entities and this layer. Outer layers call these interfaces.
#pragma once
#include <optional>
#include <string>
#include "use_cases/dtos.hpp"

namespace track::use_cases {

class RegisterPackagePort {
public:
    virtual ~RegisterPackagePort() = default;
    // Returns an error message on failure, std::nullopt on success.
    virtual std::optional<std::string> execute(const RegisterPackageRequest&) = 0;
};

class TrackPackagePort {
public:
    virtual ~TrackPackagePort() = default;
    virtual void execute(const TrackPackageRequest&) = 0;
};

}  // namespace track::use_cases
