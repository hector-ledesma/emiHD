#pragma once
#include "active_timer.h"
#include <ctime>
#include "cpp/imgui_stdlib.h"

namespace UI {
    Timer::Timer(ImGuiWindowFlags flags, data::Timer timer) : m_timer(timer) {
        setFlags(flags);
    }

    bool Timer::begin() {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.5f);
        return ImGui::BeginChild(TIMER_ELEMENT_ID+m_timer.getId(), ImVec2(0, 80.0f), true, m_flags);
    }

    void Timer::end() {
        ImGui::PopStyleVar();
        ImGui::EndChild();
    }

    void Timer::style() {
        ImGui::SeparatorText(m_timer.getTitle().c_str());
        // Date
        ImGui::Text(data::Timer::dateToString(m_timer.getDate()).c_str());
        // Timer runtime
        std::chrono::system_clock::time_point elapsed{ std::chrono::system_clock::now() - m_timer.getStartTime() };
        ImGui::Text(data::Timer::durationToString(elapsed).c_str());

        ImGui::SameLine();
        if (ImGui::Button("Play/Pause")) {
            // Play pause functionality
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop")) {
            // Stop timer functionality
        }

    }
}