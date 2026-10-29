// [Layer 1 — Entities]
// Dependency Rule: depends only on entities in this layer and the standard library.
// Note: no display formatting here. Presentation belongs to the adapters.
#pragma once
#include <string>
#include <utility>
#include <vector>
#include "entities/domain_error.hpp"
#include "entities/tracking_number.hpp"

namespace track::entities {

enum class PackageStatus { Registered, InTransit, OutForDelivery, Delivered, Exception };

struct TrackingEvent {
    PackageStatus status;
    std::string location;
    std::string description;
};

class Package {
public:
    Package(TrackingNumber number, std::string carrier)
        : number_(std::move(number)),
          carrier_(std::move(carrier)),
          status_(PackageStatus::Registered) {
        if (carrier_.empty()) throw DomainError("carrier is required");
    }

    const TrackingNumber& number() const noexcept { return number_; }
    const std::string& carrier() const noexcept { return carrier_; }
    PackageStatus status() const noexcept { return status_; }
    const std::vector<TrackingEvent>& history() const noexcept { return history_; }

    // Business rule: Delivered is terminal. Nothing may be recorded after it.
    void record_event(TrackingEvent event) {
        if (status_ == PackageStatus::Delivered)
            throw DomainError("cannot record events on a delivered package");
        status_ = event.status;
        history_.push_back(std::move(event));
    }

private:
    TrackingNumber number_;
    std::string carrier_;
    PackageStatus status_;
    std::vector<TrackingEvent> history_;
};

}  // namespace track::entities
