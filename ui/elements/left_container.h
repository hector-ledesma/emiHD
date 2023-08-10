#ifndef ROOT_LPANEL_INCLUDED
#define ROOT_LPANEL_INCLUDED

#pragma once
#define ROOT_LPANEL_ID "root_lpanel"

#include "element.h"
#include "imgui.h"

namespace UI {
    class RootLPanel : public Element {
    public:
        RootLPanel(ImGuiWindowFlags flags);
    protected:
        bool begin();
        void end();
        void style();
    };
}
#endif