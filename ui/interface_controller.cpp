#include "interface_controller.h"

namespace UI {
    InterfaceController::InterfaceController() {}
    InterfaceController::~InterfaceController() {}

    void InterfaceController::renderInterface() {
        // Application layout will be placed within one full screen parent window
        static ImGuiWindowFlags root_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration;
        UI::RootWindow root{ root_flags };
        root.render([]() {
            ImGui::Text("Hello World");
            });
    }
}