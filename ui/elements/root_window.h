#ifndef ROOT_WINDOW_INCLUDED
#define ROOT_WINDOW_INCLUDED

#pragma once
#define ROOT_WINDOW_ID "base_layout"
#define BASE_LPANEL_ID "base_l_layout"
#define BASE_RPANEL_ID "base_r_layout"

#include "element.h"
#include "imgui.h"

namespace UI {
    class RootWindow : public Element {
    public:
        RootWindow(ImGuiWindowFlags flags);
    protected:
        bool begin();
        void end();
        void style();
    };
}
#endif