// [Layer 3 — Interface Adapters]
// Dependency Rule: depends inward only. Converts use-case output into display-ready lines.
#pragma once
#include <string>
#include <vector>
#include "entities/package.hpp"
#include "use_cases/ports/output_ports.hpp"

namespace track::adapters {

class TextTrackingPresenter final : public use_cases::TrackingPresenter {
public:
    void present(const use_cases::TrackingReport& r) override {
        lines_.push_back("Package " + r.tracking_number + " via " + r.carrier);
        lines_.push_back("Status: " + to_text(r.status));
        for (const auto& e : r.events)
            lines_.push_back("  [" + to_text(e.status) + "] " + e.location + " - " + e.description);
    }

    void present_not_found(const std::string& tracking_number) override {
        lines_.push_back("No package found: " + tracking_number);
    }

    void present_invalid(const std::string& reason) override {
        lines_.push_back("Invalid request: " + reason);
    }

    void clear() { lines_.clear(); }
    const std::vector<std::string>& lines() const { return lines_; }

private:
    static std::string to_text(entities::PackageStatus s) {
        switch (s) {
            case entities::PackageStatus::Registered:     return "Registered";
            case entities::PackageStatus::InTransit:      return "In transit";
            case entities::PackageStatus::OutForDelivery: return "Out for delivery";
            case entities::PackageStatus::Delivered:      return "Delivered";
            case entities::PackageStatus::Exception:      return "Exception";
        }
        return "Unknown";
    }

    std::vector<std::string> lines_;
};

}  // namespace track::adapters
