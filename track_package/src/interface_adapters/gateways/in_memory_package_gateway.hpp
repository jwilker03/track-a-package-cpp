// [Layer 3 — Interface Adapters]
// Dependency Rule: depends inward only (Use Cases, Entities). Implements the use-case-owned
// PackageGateway port. Contains no framework or I/O headers, so swapping in a database
// later changes nothing in Layers 1 or 2.
#pragma once
#include <map>
#include <optional>
#include <string>
#include "entities/package.hpp"
#include "use_cases/ports/output_ports.hpp"

namespace track::adapters {

class InMemoryPackageGateway final : public use_cases::PackageGateway {
public:
    bool exists(const entities::TrackingNumber& number) const override {
        return packages_.count(number.value()) > 0;
    }

    void save(const entities::Package& package) override {
        packages_.insert_or_assign(package.number().value(), package);
    }

    std::optional<entities::Package> find(const entities::TrackingNumber& number) const override {
        auto it = packages_.find(number.value());
        if (it == packages_.end()) return std::nullopt;
        return it->second;
    }

private:
    std::map<std::string, entities::Package> packages_;
};

}  // namespace track::adapters
