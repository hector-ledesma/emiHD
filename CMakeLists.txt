# CMakeList.txt : CMake project for emiHD, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("emiHD")
add_executable (emiHD WIN32 "emiHD.cpp" "emiHD.h" "Application.cpp" "Application.h")
target_link_options(emiHD PRIVATE -mwindows)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET emiHD PROPERTY CXX_STANDARD 20)
endif()

## ui source		---
#set dirs
set(UI_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/ui")
set(UI_ELEMENTS_DIR "${UI_ROOT_DIR}/elements")

file(GLOB UI_SOURCE_FILES ${UI_ROOT_DIR}/*.h ${UI_ROOT_DIR}/*.cpp)
file(GLOB UI_ELEMENT_SOURCE_FILES ${UI_ELEMENTS_DIR}/*.h ${UI_ELEMENTS_DIR}/*.cpp)
#add_library(emiHD_ui INTERFACE)
target_sources(emiHD PUBLIC ${UI_SOURCE_FILES})
target_sources(emiHD PUBLIC ${UI_ELEMENT_SOURCE_FILES})
## ui source END	---

## business logic source		---
#set dirs
set(BACKEND_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/data")
set(BACKEND_ELEMENTS_DIR "${BACKEND_ROOT_DIR}/elements")

file(GLOB BACKEND_SOURCE_FILES ${BACKEND_ROOT_DIR}/*.h ${BACKEND_ROOT_DIR}/*.cpp)
file(GLOB BACKEND_ELEMENTS_SOURCE_FILES ${BACKEND_ELEMENTS_DIR}/*.h ${BACKEND_ELEMENTS_DIR}/*.cpp)
#add_library(emiHD_backend INTERFACE)
target_sources(emiHD PUBLIC ${BACKEND_SOURCE_FILES})
target_sources(emiHD PUBLIC ${BACKEND_ELEMENTS_SOURCE_FILES})
## business logic source END	---

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


set(SQLITE_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/sqlite")
message("SQLITE Dir ${SQLITE_SRC_DIR}" )
file(GLOB SQLITE_SRC_FILES ${SQLITE_SRC_DIR}/*.h ${SQLITE_SRC_DIR}/*.c)
message("SQLITE Source files ${SQLITE_SRC_FILES}" )

target_include_directories(emiHD PUBLIC ${SQLITE_SRC_DIR})
target_link_directories(emiHD PUBLIC ${SQLITE_SRC_DIR})
target_sources(emiHD PUBLIC ${SQLITE_SRC_FILES})


target_link_libraries(emiHD imgui)