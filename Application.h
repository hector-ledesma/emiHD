#ifndef EMIHD_APPLICATION_INCLUDED
#define EMIHD_APPLICATION_INCLUDED

#pragma once
#include "ui/dearimgui_controller.h"
#include "ui/interface_controller.h"

namespace 
{

}

namespace emiHD	
{


class Application {
	public:
		Application();
		~Application();
		void run();
	private:
		UI::ImGuiController		m_imgui;
		UI::InterfaceController m_interface;
};
}

#endif