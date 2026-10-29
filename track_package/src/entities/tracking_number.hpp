// [Layer 1 — Entities]
// Dependency Rule: depends only on entities in this layer and the standard library.
#pragma once
#include <cctype>
#include <string>
#include <utility>
#include "entities/domain_error.hpp"

namespace track::entities {

class TrackingNumber {
public:
    explicit TrackingNumber(std::string value) : value_(std::move(value)) {
        if (value_.size() < 8 || value_.size() > 30)
            throw DomainError("tracking number must be 8-30 characters");
        for (unsigned char c : value_)
            if (!std::isalnum(c))
                throw DomainError("tracking number must be alphanumeric");
    }

    const std::string& value() const noexcept { return value_; }
    bool operator==(const TrackingNumber& other) const noexcept { return value_ == other.value_; }

private:
    std::string value_;
};

}  // namespace track::entities
