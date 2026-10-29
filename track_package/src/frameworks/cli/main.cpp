// [Layer 4 — Frameworks & Drivers]
// Dependency Rule: this is the outermost layer and may depend on every inner layer.
// It is the composition root: the only place that names concrete types and wires them
// together. All I/O (std::iostream) lives here and nowhere inside.
#include <iostream>
#include <sstream>
#include <string>

#include "interface_adapters/controllers/package_controller.hpp"
#include "interface_adapters/gateways/in_memory_package_gateway.hpp"
#include "interface_adapters/presenters/text_tracking_presenter.hpp"
#include "use_cases/interactors/register_package_interactor.hpp"
#include "use_cases/interactors/track_package_interactor.hpp"

using namespace track;

int main() {
    // Composition root: construct outward-to-inward and inject dependencies.
    adapters::InMemoryPackageGateway gateway;
    adapters::TextTrackingPresenter presenter;
    use_cases::RegisterPackageInteractor register_pkg(gateway);
    use_cases::TrackPackageInteractor track_pkg(gateway, presenter);
    adapters::PackageController controller(register_pkg, track_pkg, presenter);

    std::cout << "Commands: register <number> <carrier> | track <number> | quit\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream in(line);
        std::string cmd, arg1, arg2;
        in >> cmd >> arg1 >> arg2;

        if (cmd == "quit") {
            break;
        } else if (cmd == "register") {
            std::cout << controller.register_package(arg1, arg2) << "\n";
        } else if (cmd == "track") {
            for (const auto& l : controller.track(arg1)) std::cout << l << "\n";
        } else {
            std::cout << "unknown command\n";
        }
    }
    return 0;
}
