#ifndef INTERFACE_CONTROLLER_INCLUDED
#define INTERFACE_CONTROLLER_INCLUDED

#pragma once
#include "imgui.h"
#include "elements/base_layout.h"

namespace UI {
    class InterfaceController {
    public:
        InterfaceController();
        ~InterfaceController();
        void createRootLayout(ImGuiWindowFlags flags);

    private:
    };
}

#endif