#include "interface_controller.h"
#include "elements/root_window.h"
#include "elements/left_container.h"
#include "elements/right_container.h"
#include "elements/timer_container.h"
#include <string>
namespace {
}
namespace UI {
    InterfaceController::InterfaceController() {}
    InterfaceController::~InterfaceController() {}

    void InterfaceController::renderInterface() {
        // Application layout will be placed within one full screen parent window
        static ImGuiWindowFlags root_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration;
        UI::RootWindow root{ root_flags };
        root.render([]{
            ImGuiWindowFlags none_flags = ImGuiWindowFlags_None;
            UI::RootLPanel lPanel{ none_flags };
            lPanel.render([none_flags] {
                UI::TimerContainer timerContainer{ none_flags };
                timerContainer.render();
                });

            ImGui::SameLine();

            UI::RootRPanel rPanel{ none_flags };
            rPanel.render();
            });
            // I want to use the "work area"
        /*const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        if (!ImGui::Begin(ROOT_WINDOW_ID, NULL, root_flags)) return;
        ImGui::Text("#BaseWindow");

        // LEFT PANEL
        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 2.5f);
            ImGui::BeginChild(ROOT_LPANEL_ID, ImVec2(ImGui::GetContentRegionAvail().x * 0.25f, 0), true, window_flags);
            ImGui::Text("Left Panel ");
            // TIMER PANEL
            {
                ImGui::BeginChild(TIMER_PANEL_ID, ImVec2(0, ImGui::GetContentRegionAvail().y * 0.75f), true, window_flags);
                ImGui::Text("Timers Panel");
                // Timers
                {
                    
                    char buf[255];
                    sprintf(buf, "Application started at: 00:00:00");
                    ImGui::Text(buf);
                    sprintf(buf, "Time elapsed: 00:00:00");
                    ImGui::Text(buf);
                }
                ImGui::EndChild();
            }
            // WIDGETS PANEL
            {
                ImGui::BeginChild(WIDGETS_PANEL_ID, ImVec2(0, 0), true, window_flags);
                ImGui::Text("Widgets Panel");
                static ImGuiInputTextFlags input_flags = ImGuiInputTextFlags_AllowTabInput;
                static char text[2048];
                ImGui::InputTextMultiline("##comment", text, 2048, ImVec2(-FLT_MIN, 0), input_flags);
                ImGui::Button("Save");
                ImGui::EndChild();
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();
        // RIGHT PANEL
        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            ImGui::BeginChild(ROOT_RPANEL_ID, ImVec2(0, 0), true, window_flags);
            ImGui::Text("Right Panel ");
            ImGui::Text("History Panel ");
            // History Panel data
            {
                ImGuiTableFlags table_flags = ImGuiTableFlags_Borders | ImGuiTableFlags_NoSavedSettings;

                if (ImGui::BeginTable("History", 6, table_flags))
                {
                    ImGui::TableSetupColumn("Date");
                    ImGui::TableSetupColumn("Title");
                    ImGui::TableSetupColumn("Comments");
                    ImGui::TableSetupColumn("Start");
                    ImGui::TableSetupColumn("End");
                    ImGui::TableSetupColumn("Duration");

                    ImGui::TableNextRow(ImGuiTableRowFlags_Headers);

                    for (int column = 0; column < 6; column++) {
                        ImGui::TableSetColumnIndex(column);
                        const char* column_name = ImGui::TableGetColumnName(column); // Retrieve named passed to TableSetupColumn()
                        ImGui::PushID(column);
                        //ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                        ImGui::TableHeader(column_name);
                        ImGui::PopID();
                    }
                    for (int i = 0; i < 12; i++)
                    {
                        ImGui::TableNextRow();
                        char buf[255];
                        // Date
                        sprintf(buf, "01/01/2023");
                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text(buf);
                        // Title
                        sprintf(buf, "Studying");
                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text(buf);
                        // Comments
                        sprintf(buf, "Complete math quota. Progressed through program.");
                        ImGui::TableSetColumnIndex(2);
                        ImGui::Text(buf);
                        // Start
                        sprintf(buf, "13:23 PM");
                        ImGui::TableSetColumnIndex(3);
                        ImGui::Text(buf);
                        // End
                        sprintf(buf, "18:15 PM");
                        ImGui::TableSetColumnIndex(4);
                        ImGui::Text(buf);
                        // Duration
                        sprintf(buf, "4:52 Hours");
                        ImGui::TableSetColumnIndex(5);
                        ImGui::Text(buf);
                    }
                    ImGui::EndTable();
                }
            }
            ImGui::EndChild();

        }
        ImGui::PopStyleVar();
        ImGui::End(); // End rood window*/
    }
}