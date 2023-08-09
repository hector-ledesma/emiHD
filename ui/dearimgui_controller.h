#ifndef DEARIMGUI_CONTROLLER_INCLUDED
#define DEARIMGUI_CONTROLLER_INCLUDED

#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <string>

namespace
{
	struct FrameContext
	{
		ID3D12CommandAllocator* CommandAllocator;
		UINT64                  FenceValue;
	};
}
// TODO:- Update comments for proper documentation once all logic is implemented.
/*
* All logic that pertains to Interface generation and customization 
* whould be structured under /interface
* |- interface/
*  |-- *.cpp/*.h pertaining to Interface control and generation
*  |-- elements/
*    |-- individual elements to be constructed should be separated into their own files
* 
* 
*/
namespace UI {
	/*
	* Interface Controller should only expose methods necessary to represent business 
	* logic onto the GUI.
	*/
	class ImGuiController {
	public:
		ImGuiController();
		~ImGuiController();
		bool init();
		void cleanup();
		void newFrame();
		void render();

		// UI Elements
		void createTestWindow();
		void demoWindow();

	private:
		// Dear ImGui Data
		static int const            NUM_FRAMES_IN_FLIGHT = 3;
		static int const            NUM_BACK_BUFFERS = 3;
		
		const ImVec4				CLEAR_COLOR = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		static WNDCLASSEXW wc;
		static HWND hwnd;
		static FrameContext				m_frameContext[NUM_FRAMES_IN_FLIGHT];
		static UINT						m_frameIndex;
		static ID3D12Device*				m_pd3dDevice;
		static ID3D12DescriptorHeap*		m_pd3dRtvDescHeap;
		static ID3D12DescriptorHeap*		m_pd3dSrvDescHeap;
		static ID3D12CommandQueue*			m_pd3dCommandQueue;
		static ID3D12GraphicsCommandList*	m_pd3dCommandList ;
		static ID3D12Fence*				m_fence;
		static HANDLE						m_fenceEvent;
		static UINT64						m_fenceLastSignaledValue;
		static IDXGISwapChain3*			m_pSwapChain;
		static HANDLE                      m_hSwapChainWaitableObject;
		static ID3D12Resource*				m_mainRenderTargetResource[NUM_BACK_BUFFERS];
		static D3D12_CPU_DESCRIPTOR_HANDLE m_mainRenderTargetDescriptor[NUM_BACK_BUFFERS];

		static void CreateApplicationWindow();
		static bool CreateDeviceD3D(HWND hWnd);
		static void CleanupDeviceD3D();
		static void CreateRenderTarget();
		static void CleanupRenderTarget();
		static void WaitForLastSubmittedFrame();
		FrameContext* WaitForNextFrameResources();
		static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	};

}
#endif