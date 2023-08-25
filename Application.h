#ifndef EMIHD_APPLICATION_INCLUDED
#define EMIHD_APPLICATION_INCLUDED

#pragma once
#include <memory>
#include "ui/dearimgui_controller.h"
#include "ui/interface_controller.h"
#include "data/data_controller.h"


namespace 
{

}

namespace emiHD	
{

	class AppSettings {
	public:
		static bool _refetchTimers;
	private:
		AppSettings() {};
	};

	class Application {
		public:
			Application();
			~Application();
			void run();
		private:
			std::shared_ptr<data::DataController>	m_data;
			UI::ImGuiController						m_imgui;
			UI::InterfaceController					m_interface;
	};
}

#endif