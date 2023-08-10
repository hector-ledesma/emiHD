#include "right_container.h"

namespace UI {
    RootRPanel::RootRPanel(ImGuiWindowFlags flags) {
        setFlags(flags);
    }
    bool RootRPanel::begin() {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.5f);
        return ImGui::BeginChild(ROOT_RPANEL_ID, ImVec2(0, 0), true, m_flags);
    }
    void RootRPanel::end() {
        ImGui::PopStyleVar();
        ImGui::EndChild();
    }

    void RootRPanel::style() {
        ImGui::SeparatorText("History Container");
    }
}