#include "root_window.h"

namespace UI {
    RootWindow::RootWindow(ImGuiWindowFlags flags) {
        setFlags(flags);
    };

    bool RootWindow::begin() {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        return ImGui::Begin(BASE_LAYOUT_ID, NULL, m_flags);
    }

    void RootWindow::style() {
        // I want to use the "work area"
        {
            ImGui::Text("#BaseWindow");

            // LEFT PANEL
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.5f);
            ImGui::BeginChild(BASE_LPANEL_ID, ImVec2(ImGui::GetContentRegionAvail().x * 0.25f, 0), true, window_flags);
            ImGui::Text("Left Panel ");
            ImGui::EndChild();
            ImGui::PopStyleVar();
        }
        //CreatePanelContainers();
    }
}