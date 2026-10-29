// [Layer 2 — Use Cases]
// Dependency Rule: depends only on Entities and this layer.
#pragma once
#include "entities/package.hpp"
#include "use_cases/dtos.hpp"
#include "use_cases/ports/input_ports.hpp"
#include "use_cases/ports/output_ports.hpp"

namespace track::use_cases {

class TrackPackageInteractor final : public TrackPackagePort {
public:
    TrackPackageInteractor(const PackageGateway& gateway, TrackingPresenter& presenter)
        : gateway_(gateway), presenter_(presenter) {}

    void execute(const TrackPackageRequest& req) override {
        try {
            entities::TrackingNumber number(req.tracking_number);
            auto package = gateway_.find(number);
            if (!package) {
                presenter_.present_not_found(req.tracking_number);
                return;
            }
            presenter_.present(to_report(*package));
        } catch (const entities::DomainError& e) {
            presenter_.present_invalid(e.what());
        }
    }

private:
    static TrackingReport to_report(const entities::Package& p) {
        TrackingReport report{p.number().value(), p.carrier(), p.status(), {}};
        for (const auto& e : p.history())
            report.events.push_back({e.status, e.location, e.description});
        return report;
    }

    const PackageGateway& gateway_;
    TrackingPresenter& presenter_;
};

}  // namespace track::use_cases
