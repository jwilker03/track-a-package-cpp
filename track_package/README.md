# Track a Package (Clean Architecture, C++17)

A small scaffold for registering packages and tracking their status, organized in four
layers. Source-code dependencies point only inward:

    Frameworks & Drivers -> Interface Adapters -> Use Cases -> Entities

| Layer | Path | Contents |
|---|---|---|
| 1. Entities | `src/entities/` | `Package`, `TrackingNumber`, `PackageStatus`, business rules |
| 2. Use Cases | `src/use_cases/` | Interactors, input/output ports, DTOs |
| 3. Interface Adapters | `src/interface_adapters/` | In-memory gateway, text presenter, controller |
| 4. Frameworks & Drivers | `src/frameworks/cli/` | `main.cpp`: composition root and console I/O |

Inner layers include no framework or I/O headers. You can check this with:

    grep -rn "#include <iostream>" src/entities src/use_cases src/interface_adapters

The command should print nothing.

## Build and run

    cmake -S . -B build && cmake --build build
    ./build/track_package

Example session:

    register 1Z999AA10123456784 UPS
    track 1Z999AA10123456784
    track bad!
    quit

## Next steps

- Add an `AddTrackingEvent` use case with its own input port that calls `Package::record_event`.
- Replace `InMemoryPackageGateway` with a database adapter that implements `PackageGateway`.
  The inner layers do not need to change.
