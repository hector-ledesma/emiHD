#include "Application.h"

namespace emiHD {
    Application::Application() : m_imgui(), m_data(), m_interface(m_data) {}
    Application::~Application() {}

    void Application::run() {
        // Initialize UI
        if (!m_imgui.init()) return;
        // Main loop
        bool done = false;
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
            
        }
        // Cleanup UI
        m_imgui.cleanup();
    }
}