#include "interface_controller.h"

namespace UI {
    InterfaceController::InterfaceController() {}
    InterfaceController::~InterfaceController() {}
    void InterfaceController::createRootLayout(ImGuiWindowFlags flags) {
        UI::BaseLayout layout{flags};
        layout.render();
    }
}