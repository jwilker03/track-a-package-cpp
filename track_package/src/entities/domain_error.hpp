// [Layer 1 — Entities]
// Dependency Rule: this layer depends on nothing outside itself.
// No framework, I/O, or adapter includes are permitted here.
#pragma once
#include <stdexcept>

namespace track::entities {

class DomainError : public std::logic_error {
public:
    using std::logic_error::logic_error;
};

}  // namespace track::entities
