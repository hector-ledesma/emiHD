#include "root_window.h"

namespace UI {
    RootWindow::RootWindow(ImGuiWindowFlags flags) {
        setFlags(flags);
    };

    bool RootWindow::begin() {
        // I want to use the "work area"
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        return ImGui::Begin(ROOT_WINDOW_ID, NULL, m_flags);
    }

    void RootWindow::end() { 
        ImGui::End(); 
    }

    void RootWindow::style() {
        ImGui::Text("#BaseWindow");
    }
}