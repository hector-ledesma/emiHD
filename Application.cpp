#include "Application.h"

namespace emiHD {
    bool AppSettings::_refetchTimers = false;

    Application::Application() : 
        m_imgui(),
        m_data(std::shared_ptr<data::DataController>(new data::DataController())),
        m_interface(m_data) {
    }

    Application::~Application() {}

    void Application::run() {
        // Initialize UI
        if (!m_imgui.init()) return;
        // Main loop
        bool done = false;
        // Fetch from database on first launch 
        AppSettings::_refetchTimers = true;
        while (!done)
        {
            // Poll and handle messages (inputs, window resize, etc.)
            MSG msg;
            while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                if (msg.message == WM_QUIT) { done = true; }
            }
            if (done) { break; }

            // Start the Dear ImGui frame
            m_imgui.newFrame();

            // Application UI
            m_interface.renderInterface();
            // ImGui Rendering
            m_imgui.render();
            
            // Turn off refetching until application UI requests it
            AppSettings::_refetchTimers = false;
        }
        // Cleanup UI
        m_imgui.cleanup();
    }
}