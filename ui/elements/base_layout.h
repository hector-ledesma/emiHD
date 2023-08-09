#ifndef BASE_LAYOUT_INCLUDED
#define BASE_LAYOUT_INCLUDED

#pragma once
#define BASE_LAYOUT_ID "base_layout"

#include "element.h"
#include "imgui.h"

namespace UI {
    class BaseLayout : public Element {
    public:
        BaseLayout(ImGuiWindowFlags flags);
        void render();
    };
}
#endif