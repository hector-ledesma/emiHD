#ifndef INTERFACE_CONTROLLER_INCLUDED
#define INTERFACE_CONTROLLER_INCLUDED

#pragma once
#include "imgui.h"
#include "../data/data_controller.h"

namespace UI {
    class InterfaceController {
    public:
        InterfaceController(data::DataController dataController);
        ~InterfaceController();
        void renderInterface();

    private:
        data::DataController m_dataController;
    };
}

#endif