#include "base_layout.h"

namespace UI {
    BaseLayout::BaseLayout(ImGuiWindowFlags flags) {
        setFlags(flags);
    };

    void BaseLayout::render() {
        // I want to use the "work area"
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        if (ImGui::Begin(BASE_LAYOUT_ID, NULL, m_flags))
        {
            ImGui::Text("Parent window successfully created");
        }
        //CreatePanelContainers();
        ImGui::End();
    }
}