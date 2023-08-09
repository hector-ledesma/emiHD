// dearimgui-learning.cpp : Defines the entry point for the application.
//

#include "emiHD.h"
#include "Application.h"
//#include <tchar.h>

#ifdef _DEBUG
#define DX12_ENABLE_DEBUG_LAYER
#endif

#ifdef DX12_ENABLE_DEBUG_LAYER
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")
#endif

int main()
{
    emiHD::Application app;
    app.run();
}
