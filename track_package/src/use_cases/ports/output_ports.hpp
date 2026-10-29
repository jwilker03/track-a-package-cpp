// [Layer 2 — Use Cases]
// Dependency Rule: depends only on Entities and this layer. These interfaces are owned by
// the use cases; the adapters in Layer 3 implement them.
#pragma once
#include <optional>
#include <string>
#include "entities/package.hpp"
#include "use_cases/dtos.hpp"

namespace track::use_cases {

// Persistence port. Any storage (memory, SQL, file) must satisfy this.
class PackageGateway {
public:
    virtual ~PackageGateway() = default;
    virtual bool exists(const entities::TrackingNumber& number) const = 0;
    virtual void save(const entities::Package& package) = 0;
    virtual std::optional<entities::Package> find(const entities::TrackingNumber& number) const = 0;
};

// Presentation port. The use case says what happened, not how to show it.
class TrackingPresenter {
public:
    virtual ~TrackingPresenter() = default;
    virtual void present(const TrackingReport& report) = 0;
    virtual void present_not_found(const std::string& tracking_number) = 0;
    virtual void present_invalid(const std::string& reason) = 0;
};

}  // namespace track::use_cases
