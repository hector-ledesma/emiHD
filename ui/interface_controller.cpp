#include "interface_controller.h"
#include "elements/root_window.h"
#include "elements/left_container.h"
#include "elements/right_container.h"
#include "elements/timer_container.h"
#include "elements/active_timer.h"
#include "elements/history_table.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

namespace UI {
    InterfaceController::InterfaceController(data::DataController dataController) :
        m_dataController(dataController)
    {}
    InterfaceController::~InterfaceController() {}

    void InterfaceController::renderInterface() {
        // Application layout will be placed within one full screen parent window
        static ImGuiWindowFlags root_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration;
        UI::RootWindow root{ root_flags };
        static auto& timers = m_dataController.getAllTimers();
        root.render([this] {
            ImGuiWindowFlags none_flags = ImGuiWindowFlags_None;
            UI::RootLPanel lPanel{ none_flags };
            lPanel.render([this, none_flags] {
                UI::TimerContainer timerContainer{ none_flags };
            //timerContainer.render([this, none_flags] {
            static char new_timer_title[256];
            ImGui::InputTextWithHint("##", "Timer Title", new_timer_title, IM_ARRAYSIZE(new_timer_title));
            ImGui::SameLine();
            if (ImGui::Button("New Timer")) {
                // Logic controller create new timer here
                std::string title = new_timer_title;
                if (!title.empty()) {
                    m_dataController.createTimer(title);
                    memset(new_timer_title, 0, 256);
                }
            }
            
            for (auto& timer : timers) {
                if (timer->isRunning()) {
                    UI::Timer active_timer(none_flags, timer);
                    active_timer.render();
                }
            }
            });


            ImGui::SameLine();

            UI::RootRPanel rPanel{ none_flags };
            rPanel.render([this] {
                ImGuiTableFlags table_flags = ImGuiTableFlags_Borders | ImGuiTableFlags_NoSavedSettings;
                UI::HistoryTable history{ table_flags, timers };
                history.render();
                });
            });
    }
}