cmake_minimum_required(VERSION 2.8)

SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET (CMAKE_CXX_FLAGS "-std=c++14")

set(GLFW_SOURCE_DIR "lib/external/glfw")
set(GLM_SOURCE_DIR "lib/external/glm")
set(GLEW_SOURCE_DIR "lib/external/glew")
set(NANOGUI_DIR "lib/nanogui")
set(FBX_SDK_DIR "/Applications/Autodesk/FBX SDK/2015.1")

set(FBX_SDK_LIB_RELEASE "${FBX_SDK_DIR}/lib/clang/release/libfbxsdk.a")

# Building only the GLFW lib
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")


#SET (CMAKE_AR      "/usr/bin/llvm-ar")
#SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
#SET (CMAKE_NM      "/usr/bin/llvm-nm")
#SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
#SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")

add_subdirectory(${GLFW_SOURCE_DIR} ${GLEW_SOURCE_DIR})
add_subdirectory(${NANOGUI_DIR})


include_directories(${GLFW_SOURCE_DIR}/include
        ${GLFW_SOURCE_DIR}/deps
        ${GLM_SOURCE_DIR}
        ${GLEW_SOURCE_DIR}/include
        ${FBX_SDK_DIR}/include
        ${NANOGUI_DIR}/include
        ${NANOGUI_DIR}/ext/eigen
        ${NANOGUI_DIR}/ext/nanovg/src
        src
        )

add_library(glew STATIC
        ${GLEW_SOURCE_DIR}/src/glew.c
        ${GLEW_SOURCE_DIR}/include
        )

#target_link_libraries(glew ${GLFW_LIBRARIES})

add_definitions(
        -DGLEW_STATIC
)

find_package(OpenGL REQUIRED)
# find_library(COCOA_LIBRARY Cocoa) # import Cocoa lib to COCOA_LIBRARY symbol <replacable with> "-framework Cocoa"


file(GLOB SRC "src/*.cpp" "src/*/*.cpp")

add_executable("opengl-boilerplate" main.cpp ${SRC} src/ObjectPropertyWindow.cpp src/ObjectPropertyWindow.h src/SceneManager.cpp src/SceneManager.h src/GameObject.cpp src/GameObject.h src/Light.cpp src/Light.h src/Quad.cpp src/Quad.h src/RenderPass.cpp src/RenderPass.h src/RenderPassDeferred0.cpp src/RenderPassDeferred0.h src/DummyGradientTexture.cpp src/DummyGradientTexture.h src/ShaderParam.cpp src/ShaderParam.h src/FrameBuffer.cpp src/FrameBuffer.h src/Tweener.cpp src/Tweener.h)
target_link_libraries("opengl-boilerplate" nanogui)
target_link_libraries("opengl-boilerplate" glfw ${GLFW_LIBRARIES} glew ${OPENGL_LIBRARIES} ${FBX_SDK_LIB_RELEASE} "-framework Cocoa" )
#
#if (APPLE)
#    set(APP_NAME "OpenGL Boilerplate")
#
#    # if (EXISTS icon.icns)
#    add_executable(${APP_NAME} MACOSX_BUNDLE main.cpp icon.icns ${SRC})
#    set_source_files_properties("icon.icns" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
#    # else ()
#    # add_executable(${APP_NAME} MACOSX_BUNDLE main.cpp)
#    # endif ()
#
#    target_link_libraries(${APP_NAME} glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES} glew ${FBX_SDK_LIB_RELEASE})
#    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE "icon.icns")
#
#    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME ${APP_NAME})
#    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0")
#    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING "1.0")
#    set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE_INFO_STRING "OpenGL boilerplate example app")
#endif()
