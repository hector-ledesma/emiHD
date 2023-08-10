#include "left_container.h"

namespace UI {
    RootLPanel::RootLPanel(ImGuiWindowFlags flags) {
        setFlags(flags);
    }
    bool RootLPanel::begin() {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.5f);
        return ImGui::BeginChild(ROOT_LPANEL_ID, ImVec2(ImGui::GetContentRegionAvail().x * 0.25f, 0), true, m_flags);
    }
    void RootLPanel::end() {
        ImGui::PopStyleVar();
        ImGui::EndChild();
    }

    void RootLPanel::style() {
        ImGui::SeparatorText("Timer Container ");
    }
}