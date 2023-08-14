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
        char buf[256];
        // Timer runtime
        typedef std::chrono::high_resolution_clock clock;
        typedef std::chrono::duration<float, std::milli> duration;

        duration elapsed = clock::now() - m_timer.getStartTime();
        std::string s = std::to_string(elapsed.count());
        ImGui::PushItemWidth(120.0f);
        ImGui::InputText("##", &s);
        ImGui::SameLine();
        ImGui::Button("Play/Pause");
        // Date
        const auto date = m_timer.getDate();
        auto timer_date = std::ctime(&date);
        sprintf_s(buf, "Date: %s", timer_date);
        ImGui::Text(buf); 

        //// Start time
        //const auto tp = m_timer.getStartTime();
        //std::string s = std::format("{%H%M}", tp);
        ////sprintf_s(buf, "Start Time: %s", s.c_str());
        //ImGui::Text(buf);

    }
}