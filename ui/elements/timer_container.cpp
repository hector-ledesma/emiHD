#include "timer_container.h"
namespace UI {
    TimerContainer::TimerContainer(ImGuiWindowFlags flags) {
        setFlags(flags);
    }
    bool TimerContainer::begin() {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.5f);
        return ImGui::BeginChild(TIMER_CONTAINER_ID, ImVec2(0, ImGui::GetContentRegionAvail().y * 0.75f), true, m_flags);
    }
    void TimerContainer::end() {
        ImGui::PopStyleVar();
        ImGui::EndChild();
    }

    void TimerContainer::style() {
        ImGui::SeparatorText("Timers Panel");
    }
}