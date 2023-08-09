#include "dearimgui_controller.h"

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace {
}

namespace UI {
    // public methods
    ImGuiController::ImGuiController() {}
    ImGuiController::~ImGuiController(){}

    void ImGuiController::init() {

    }
    // private methods
    void ImGuiController::CreateApplicationWindow() {
        // Create application window
        
        WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"emiHD WNDCLASS", nullptr };
        ::RegisterClassExW(&wc);

        HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"emiHD HWND", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);
    }

    bool ImGuiController::CreateDeviceD3D(HWND hWnd)
    {
        // Setup swap chain
        DXGI_SWAP_CHAIN_DESC1 sd;
        {
            ZeroMemory(&sd, sizeof(sd));
            sd.BufferCount = NUM_BACK_BUFFERS;
            sd.Width = 0;
            sd.Height = 0;
            sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
            sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            sd.SampleDesc.Count = 1;
            sd.SampleDesc.Quality = 0;
            sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
            sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
            sd.Scaling = DXGI_SCALING_STRETCH;
            sd.Stereo = FALSE;
        }

        // [DEBUG] Enable debug interface
#ifdef DX12_ENABLE_DEBUG_LAYER
        ID3D12Debug* pdx12Debug = nullptr;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pdx12Debug))))
            pdx12Debug->EnableDebugLayer();
#endif

        // Create device
        D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
        if (D3D12CreateDevice(nullptr, featureLevel, IID_PPV_ARGS(&m_pd3dDevice)) != S_OK)
            return false;

        // [DEBUG] Setup debug interface to break on any warnings/errors
#ifdef DX12_ENABLE_DEBUG_LAYER
        if (pdx12Debug != nullptr)
        {
            ID3D12InfoQueue* pInfoQueue = nullptr;
            m_pd3dDevice->QueryInterface(IID_PPV_ARGS(&pInfoQueue));
            pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
            pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
            pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
            pInfoQueue->Release();
            pdx12Debug->Release();
        }
#endif

        {
            D3D12_DESCRIPTOR_HEAP_DESC desc = {};
            desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
            desc.NumDescriptors = NUM_BACK_BUFFERS;
            desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
            desc.NodeMask = 1;
            if (m_pd3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pd3dRtvDescHeap)) != S_OK)
                return false;

            SIZE_T rtvDescriptorSize = m_pd3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
            D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_pd3dRtvDescHeap->GetCPUDescriptorHandleForHeapStart();
            for (UINT i = 0; i < NUM_BACK_BUFFERS; i++)
            {
                m_mainRenderTargetDescriptor[i] = rtvHandle;
                rtvHandle.ptr += rtvDescriptorSize;
            }
        }

        {
            D3D12_DESCRIPTOR_HEAP_DESC desc = {};
            desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
            desc.NumDescriptors = 1;
            desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
            if (m_pd3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_pd3dSrvDescHeap)) != S_OK)
                return false;
        }

        {
            D3D12_COMMAND_QUEUE_DESC desc = {};
            desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
            desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
            desc.NodeMask = 1;
            if (m_pd3dDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&m_pd3dCommandQueue)) != S_OK)
                return false;
        }

        for (UINT i = 0; i < NUM_FRAMES_IN_FLIGHT; i++)
            if (m_pd3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_frameContext[i].CommandAllocator)) != S_OK)
                return false;

        if (m_pd3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_frameContext[0].CommandAllocator, nullptr, IID_PPV_ARGS(&m_pd3dCommandList)) != S_OK ||
            m_pd3dCommandList->Close() != S_OK)
            return false;

        if (m_pd3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)) != S_OK)
            return false;

        m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if (m_fenceEvent == nullptr)
            return false;

        {
            IDXGIFactory4* dxgiFactory = nullptr;
            IDXGISwapChain1* swapChain1 = nullptr;
            if (CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)) != S_OK)
                return false;
            if (dxgiFactory->CreateSwapChainForHwnd(m_pd3dCommandQueue, hWnd, &sd, nullptr, nullptr, &swapChain1) != S_OK)
                return false;
            if (swapChain1->QueryInterface(IID_PPV_ARGS(&m_pSwapChain)) != S_OK)
                return false;
            swapChain1->Release();
            dxgiFactory->Release();
            m_pSwapChain->SetMaximumFrameLatency(NUM_BACK_BUFFERS);
            m_hSwapChainWaitableObject = m_pSwapChain->GetFrameLatencyWaitableObject();
        }

        CreateRenderTarget();
        return true;
    }

    void ImGuiController::CreateRenderTarget()
    {
        for (UINT i = 0; i < NUM_BACK_BUFFERS; i++)
        {
            ID3D12Resource* pBackBuffer = nullptr;
            m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
            m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, m_mainRenderTargetDescriptor[i]);
            m_mainRenderTargetResource[i] = pBackBuffer;
        }
    }

    void ImGuiController::CleanupDeviceD3D() {
        CleanupRenderTarget();
        if (m_pSwapChain) { m_pSwapChain->SetFullscreenState(false, nullptr); m_pSwapChain->Release(); m_pSwapChain = nullptr; }
        if (m_hSwapChainWaitableObject != nullptr) { CloseHandle(m_hSwapChainWaitableObject); }
        for (UINT i = 0; i < NUM_FRAMES_IN_FLIGHT; i++)
            if (m_frameContext[i].CommandAllocator) { m_frameContext[i].CommandAllocator->Release(); m_frameContext[i].CommandAllocator = nullptr; }
        if (m_pd3dCommandQueue) { m_pd3dCommandQueue->Release(); m_pd3dCommandQueue = nullptr; }
        if (m_pd3dCommandList) { m_pd3dCommandList->Release(); m_pd3dCommandList = nullptr; }
        if (m_pd3dRtvDescHeap) { m_pd3dRtvDescHeap->Release(); m_pd3dRtvDescHeap = nullptr; }
        if (m_pd3dSrvDescHeap) { m_pd3dSrvDescHeap->Release(); m_pd3dSrvDescHeap = nullptr; }
        if (m_fence) { m_fence->Release(); m_fence = nullptr; }
        if (m_fenceEvent) { CloseHandle(m_fenceEvent); m_fenceEvent = nullptr; }
        if (m_pd3dDevice) { m_pd3dDevice->Release(); m_pd3dDevice = nullptr; }

#ifdef DX12_ENABLE_DEBUG_LAYER
        IDXGIDebug1* pDebug = nullptr;
        if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&pDebug))))
        {
            pDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY);
            pDebug->Release();
        }
#endif
    }

    void ImGuiController::CleanupRenderTarget()
    {
        WaitForLastSubmittedFrame();

        for (UINT i = 0; i < NUM_BACK_BUFFERS; i++)
            if (m_mainRenderTargetResource[i]) { m_mainRenderTargetResource[i]->Release(); m_mainRenderTargetResource[i] = nullptr; }
    }

    void ImGuiController::WaitForLastSubmittedFrame()
    {
        FrameContext* frameCtx = &m_frameContext[m_frameIndex % NUM_FRAMES_IN_FLIGHT];

        UINT64 fenceValue = frameCtx->FenceValue;
        if (fenceValue == 0)
            return; // No fence was signaled

        frameCtx->FenceValue = 0;
        if (m_fence->GetCompletedValue() >= fenceValue)
            return;

        m_fence->SetEventOnCompletion(fenceValue, m_fenceEvent);
        WaitForSingleObject(m_fenceEvent, INFINITE);
    }

    FrameContext* ImGuiController::WaitForNextFrameResources()
    {
        UINT nextFrameIndex = m_frameIndex + 1;
        m_frameIndex = nextFrameIndex;

        HANDLE waitableObjects[] = { m_hSwapChainWaitableObject, nullptr };
        DWORD numWaitableObjects = 1;

        FrameContext* frameCtx = &m_frameContext[nextFrameIndex % NUM_FRAMES_IN_FLIGHT];
        UINT64 fenceValue = frameCtx->FenceValue;
        if (fenceValue != 0) // means no fence was signaled
        {
            frameCtx->FenceValue = 0;
            m_fence->SetEventOnCompletion(fenceValue, m_fenceEvent);
            waitableObjects[1] = m_fenceEvent;
            numWaitableObjects = 2;
        }

        WaitForMultipleObjects(numWaitableObjects, waitableObjects, TRUE, INFINITE);

        return frameCtx;
    }

    
    // Win32 message handler
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    LRESULT WINAPI ImGuiController::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        switch (msg)
        {
        case WM_SIZE:
            if (m_pd3dDevice != nullptr && wParam != SIZE_MINIMIZED)
            {
                WaitForLastSubmittedFrame();
                CleanupRenderTarget();
                HRESULT result = m_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT);
                assert(SUCCEEDED(result) && "Failed to resize swapchain.");
                CreateRenderTarget();
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        }
        return ::DefWindowProcW(hWnd, msg, wParam, lParam);
    }
};