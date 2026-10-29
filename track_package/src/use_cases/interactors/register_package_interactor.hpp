// [Layer 2 — Use Cases]
// Dependency Rule: depends only on Entities and this layer.
#pragma once
#include <optional>
#include <string>
#include "entities/package.hpp"
#include "use_cases/dtos.hpp"
#include "use_cases/ports/input_ports.hpp"
#include "use_cases/ports/output_ports.hpp"

namespace track::use_cases {

class RegisterPackageInteractor final : public RegisterPackagePort {
public:
    explicit RegisterPackageInteractor(PackageGateway& gateway) : gateway_(gateway) {}

    std::optional<std::string> execute(const RegisterPackageRequest& req) override {
        try {
            entities::TrackingNumber number(req.tracking_number);
            if (gateway_.exists(number))
                return "already registered: " + req.tracking_number;
            gateway_.save(entities::Package(number, req.carrier));
            return std::nullopt;
        } catch (const entities::DomainError& e) {
            return std::string(e.what());
        }
    }

private:
    PackageGateway& gateway_;
};

}  // namespace track::use_cases
