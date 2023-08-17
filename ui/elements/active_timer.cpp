#pragma once
#include "active_timer.h"
#include <ctime>
#include "cpp/imgui_stdlib.h"

namespace UI {
    Timer::Timer(ImGuiWindowFlags flags,const std::shared_ptr<data::Timer> timer) : m_timer(timer) {
        setFlags(flags);
    }

    bool Timer::begin() {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.5f);
        std::string id{ TIMER_ELEMENT_ID + std::to_string(m_timer->getId()) };
        return ImGui::BeginChild(id.c_str(), ImVec2(0, 80.0f), true, m_flags);
    }

    void Timer::end() {
        ImGui::EndChild();
        ImGui::PopStyleVar();
    }

    void Timer::style() {
        ImGui::SeparatorText(m_timer->getTitle().c_str());
        // Date
        ImGui::Text(data::Timer::dateToString(m_timer->getDate()).c_str());
        // Timer runtime
        ImGui::Text(data::Timer::durationToString(m_timer->getRuntime()).c_str());

        ImGui::SameLine();
        if (ImGui::Button("Play/Pause")) {
            // Play pause functionality
            m_timer->togglePause();
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop")) {
            // Stop timer functionality
            m_timer->stop();
        }

    }
}