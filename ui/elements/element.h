#ifndef ELEMENT_INTERFACE_INCLUDED
#define ELEMENT_INTERFACE_INCLUDED

#pragma once
#include "imgui.h"
#include <string>

namespace UI {
    class Element {
    public:
        virtual render() = 0;
        void setFlags(int flags) { m_flags = flags; };
        void renderIn(std::string parent) {
            if (ImGui::Begin(parent)) {
                this->render();
                ImGui::End();
            }
        };
    protected:
        int m_flags;
    };
}
#endif
