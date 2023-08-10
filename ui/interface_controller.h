#ifndef INTERFACE_CONTROLLER_INCLUDED
#define INTERFACE_CONTROLLER_INCLUDED

#pragma once
#include "imgui.h"

namespace UI {
    class InterfaceController {
    public:
        InterfaceController();
        ~InterfaceController();
        void renderInterface();

    private:
    };
}

#endif