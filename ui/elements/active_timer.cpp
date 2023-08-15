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
        return ImGui::BeginChild(TIMER_ELEMENT_ID+m_timer->getId(), ImVec2(0, 80.0f), true, m_flags);
    }

    void Timer::end() {
        ImGui::PopStyleVar();
        ImGui::EndChild();
    }

    void Timer::style() {
        ImGui::SeparatorText(m_timer->getTitle().c_str());
        // Date
        ImGui::Text(data::Timer::dateToString(m_timer->getDate()).c_str());
        // Timer runtime
        std::chrono::system_clock::time_point elapsed;
        if (m_paused) {
            elapsed = std::chrono::system_clock::time_point{ paused_at - m_timer->getStartTime() };
        }
        else {
            elapsed = std::chrono::system_clock::time_point{ std::chrono::system_clock::now() - m_timer->getStartTime() };
        }
        ImGui::Text(data::Timer::durationToString(elapsed).c_str());

        ImGui::SameLine();
        if (ImGui::Button("Play/Pause")) {
            // Play pause functionality
            togglePause();
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop")) {
            // Stop timer functionality
            stopTimer();
        }
    }

    void Timer::togglePause() {
        if (m_paused) {
            // unpause
            std::chrono::system_clock::time_point prev_elapsed{paused_at - m_timer->getStartTime()};
            std::chrono::system_clock::time_point new_time{ std::chrono::system_clock::now() - prev_elapsed};
            m_timer->updateTime(new_time);
        }
        else {
            // pause
            paused_at = std::chrono::system_clock::now();
        }
        m_paused = !m_paused;
    }
    void Timer::stopTimer() {
        
        // If paused, make sure to store updated start time.
        if (m_paused) {
            std::chrono::system_clock::time_point prev_elapsed{ paused_at - m_timer->getStartTime() };
            std::chrono::system_clock::time_point new_time{ std::chrono::system_clock::now() - prev_elapsed };
            m_timer->updateTime(new_time);
        }
        m_timer->setDuration(std::chrono::system_clock::now() - m_timer->getStartTime());
    }
}