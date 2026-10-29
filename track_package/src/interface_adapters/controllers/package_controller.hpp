// [Layer 3 — Interface Adapters]
// Dependency Rule: depends inward only. Turns raw command input into use-case requests
// and returns view data. It knows nothing about how the CLI reads input or prints output.
#pragma once
#include <string>
#include <vector>
#include "interface_adapters/presenters/text_tracking_presenter.hpp"
#include "use_cases/ports/input_ports.hpp"

namespace track::adapters {

class PackageController {
public:
    PackageController(use_cases::RegisterPackagePort& register_port,
                      use_cases::TrackPackagePort& track_port,
                      TextTrackingPresenter& presenter)
        : register_(register_port), track_(track_port), presenter_(presenter) {}

    std::string register_package(const std::string& number, const std::string& carrier) {
        auto error = register_.execute({number, carrier});
        return error ? *error : "Registered " + number;
    }

    std::vector<std::string> track(const std::string& number) {
        presenter_.clear();
        track_.execute({number});
        return presenter_.lines();
    }

private:
    use_cases::RegisterPackagePort& register_;
    use_cases::TrackPackagePort& track_;
    TextTrackingPresenter& presenter_;
};

}  // namespace track::adapters
