// [Layer 2 — Use Cases]
// Dependency Rule: depends only on the Entities layer and the standard library.
// DTOs are plain data crossing the boundary. They carry no framework types.
#pragma once
#include <string>
#include <vector>
#include "entities/package.hpp"

namespace track::use_cases {

struct RegisterPackageRequest {
    std::string tracking_number;
    std::string carrier;
};

struct TrackPackageRequest {
    std::string tracking_number;
};

struct EventDto {
    entities::PackageStatus status;
    std::string location;
    std::string description;
};

struct TrackingReport {
    std::string tracking_number;
    std::string carrier;
    entities::PackageStatus status;
    std::vector<EventDto> events;
};

}  // namespace track::use_cases
