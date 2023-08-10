# CMakeList.txt : CMake project for emiHD, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("emiHD")
add_executable (emiHD "emiHD.cpp" "emiHD.h" "ui/dearimgui_controller" "Application.cpp" "ui/elements/root_window.cpp" "ui/interface_controller.cpp" "ui/interface_controller.h" "ui/elements/element.h" "ui/elements/left_container.h" "ui/elements/left_conatiner.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET emiHD PROPERTY CXX_STANDARD 20)
endif()

## imgui ---
# set dirs
set(IMGUI_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/imgui")
set(IMGUI_BACKENDS_DIR ${IMGUI_ROOT_DIR}/backends)
set(IMGUI_MISC_DIR ${IMGUI_ROOT_DIR}/misc)

file(GLOB IMGUI_SOURCE_FILES ${IMGUI_ROOT_DIR}/*.h ${IMGUI_ROOT_DIR}/*.cpp)
add_library(imgui INTERFACE)
# main lib
target_sources(imgui INTERFACE ${IMGUI_SOURCE_FILES})
# backend
target_sources(imgui INTERFACE ${IMGUI_BACKENDS_DIR}/imgui_impl_win32.h ${IMGUI_BACKENDS_DIR}/imgui_impl_win32.cpp)
target_sources(imgui INTERFACE ${IMGUI_BACKENDS_DIR}/imgui_impl_dx12.h ${IMGUI_BACKENDS_DIR}/imgui_impl_dx12.cpp)
# misc
target_sources(imgui INTERFACE ${IMGUI_MISC_DIR}/cpp/imgui_stdlib.h ${IMGUI_MISC_DIR}/cpp/imgui_stdlib.cpp)
# inclue imgui directories
target_include_directories(imgui INTERFACE
	${IMGUI_ROOT_DIR}
	${IMGUI_BACKENDS_DIR}
	${IMGUI_MISC_DIR}
)
# link libraries
target_link_libraries(imgui INTERFACE 
	d3d12 
	dxgi 
	d3dcompiler 
	dxguid
	dxcompiler
)
## imgui END --

target_link_libraries(emiHD imgui)