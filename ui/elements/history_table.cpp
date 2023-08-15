#include "history_table.h"
#include "cpp/imgui_stdlib.h"
#include <ctime>
#include <string>

namespace {
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::duration<float, std::milli> duration;
}

namespace UI {
    HistoryTable::HistoryTable(ImGuiWindowFlags flags, std::vector<data::Timer> timers) : m_timers(timers) {
        setFlags(flags);
    }

    bool HistoryTable::begin() {
        return ImGui::BeginTable(HISTORY_TABLE_ID, 5, m_flags);
    }

    void HistoryTable::end() {
        ImGui::EndTable();
    }

    void HistoryTable::style() {
        ImGui::TableSetupColumn("Title");
        ImGui::TableSetupColumn("Date");
        //ImGui::TableSetupColumn("Comments");
        ImGui::TableSetupColumn("Start");
        //ImGui::TableSetupColumn("End");
        ImGui::TableSetupColumn("Duration");

        ImGui::TableNextRow(ImGuiTableRowFlags_Headers);

        for (int column = 0; column < 4; column++) {
            ImGui::TableSetColumnIndex(column);
            const char* column_name = ImGui::TableGetColumnName(column); // Retrieve named passed to TableSetupColumn()
            ImGui::PushID(column);
            //ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::TableHeader(column_name);
            ImGui::PopID();
        }
        for (auto& timer : m_timers)
        {
            ImGui::TableNextRow();
            //char buf[255];

            // Title
            ImGui::TableSetColumnIndex(0);
            ImGui::Text(timer.getTitle().c_str());

            // Date
            ImGui::TableSetColumnIndex(1);
            //const auto date = timer.getDate();
            ImGui::Text(data::Timer::dateToString(timer.getDate()).c_str());

            // Comments
            /*ImGui::TableSetColumnIndex(2);
            ImGui::Text(timer.getComments());*/

            // Start
            ImGui::TableSetColumnIndex(2);
            ImGui::Text(data::Timer::dateToString(timer.getStartTime()).c_str());
            
            // Duration
            ImGui::TableSetColumnIndex(3);
            if (timer.isRunning()) {
                ImGui::Text("Running");
            }
            else {
                //std::string s = std::vformat("{:%d %H:%M:%S}")
                const auto duration = std::chrono::system_clock::time_point{ timer.getDuration() };
                ImGui::Text(data::Timer::durationToString(duration).c_str());
            }
        }
    }
}