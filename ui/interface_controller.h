#ifndef INTERFACE_CONTROLLER_INCLUDED
#define INTERFACE_CONTROLLER_INCLUDED

#pragma once
#include <memory>
#include "imgui.h"
#include "../data/data_controller.h"

namespace UI {
    class InterfaceController {
    public:
        InterfaceController(std::shared_ptr<data::DataController> dataController);
        ~InterfaceController();
        void renderInterface();

    private:
        std::shared_ptr<data::DataController> m_dataController;
    };
}

#endif