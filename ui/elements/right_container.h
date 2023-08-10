#ifndef ROOT_RPANEL_INCLUDED
#define ROOT_RPANEL_INCLUDED

#pragma once
#define ROOT_RPANEL_ID "root_rpanel"

#include "element.h"
#include "imgui.h"

namespace UI {
    class RootRPanel : public Element {
    public:
        RootRPanel(ImGuiWindowFlags flags);
    protected:
        bool begin();
        void end();
        void style();
    };
}
#endif