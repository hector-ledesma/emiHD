#include "Application.h"

namespace emiHD {
    Application::Application() : m_imguiController() {}
    Application::~Application() {}

    void Application::run() {
        // Initialize UI
        if (!m_imguiController.init()) return;
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
            m_imguiController.newFrame();

            // Application UI
            {
                m_imguiController.demoWindow();
                m_imguiController.createTestWindow();
            }

            // Rendering
            m_imguiController.render();
            
        }
        // Cleanup UI
        m_imguiController.cleanup();
    }
}