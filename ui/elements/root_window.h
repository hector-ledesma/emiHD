#ifndef BASE_LAYOUT_INCLUDED
#define BASE_LAYOUT_INCLUDED

#pragma once
#define BASE_LAYOUT_ID "base_layout"
#define BASE_LPANEL_ID "base_l_layout"
#define BASE_RPANEL_ID "base_r_layout"

#include "element.h"
#include "imgui.h"

namespace UI {
    class RootWindow : public Element {
    public:
        RootWindow(ImGuiWindowFlags flags);
        bool begin();
        void style();
    };
}
#endif