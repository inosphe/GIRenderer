//
// Created by inosphe on 2016. 4. 14..
//

#ifndef PROJECT_NANOGUIIMPLEMENTATION_H
#define PROJECT_NANOGUIIMPLEMENTATION_H

#include "common_header.h"
#include <nanogui/screen.h>
#include <GLFW/glfw3.h>

class GLFWwindow;

class NanoGUIImplementation  : public nanogui::Screen{
public:
	NanoGUIImplementation();
	virtual ~NanoGUIImplementation();
	void Init(GLFWwindow* pWindow);

protected:
	void InitLayout();
	void InitCallbacks(GLFWwindow* pWindow);

private:
	static void OnCharCallback(GLFWwindow *w, unsigned int codepoint);
	static void OnDropCallback(GLFWwindow *w, int count, const char **filenames);
	static void OnFrameBufferSizeCallback(GLFWwindow* w, int width, int height);
};


#endif //PROJECT_NANOGUIIMPLEMENTATION_H
