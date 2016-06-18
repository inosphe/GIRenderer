//
// Created by inosphe on 2016. 4. 14..
//

#include "GUI.h"
#include <nanogui/nanogui.h>
#include <iostream>
#include "NanoGUIImplementation.h"
#include "ObjectPropertyWindow.h"
#include "Logger.h"


GUI::GUI(GLFWwindow *pWindow)
:m_pWindow(pWindow)
{

}

GUI::~GUI() {

}

void GUI::Init() {
	nanogui::init();
	{
		m_pScreen = new NanoGUIImplementation();
		m_pScreen->Init(m_pWindow);
	}
}

void GUI::Render() {
	m_pScreen->drawWidgets();
}

void GUI::Clear() {
	nanogui::shutdown();
}

bool GUI::OnMousePos(int x, int y) {
	return m_pScreen->cursorPosCallbackEvent(x, y);
}

bool GUI::OnMouseButton(int button, int action, int modifier) {
	Logger::Debug("mouse button");
	return m_pScreen->mouseButtonCallbackEvent(button, action, modifier);
}

bool GUI::OnKeyPress(int key, int scancode, int mods) {
	return m_pScreen->keyCallbackEvent(key, scancode, GLFW_PRESS, mods);
}

bool GUI::OnKeyRepeat(int key, int scancode, int mods) {
	return m_pScreen->keyCallbackEvent(key, scancode, GLFW_REPEAT, mods);
}

bool GUI::OnKeyRelease(int key, int scancode, int mods) {
	return m_pScreen->keyCallbackEvent(key, scancode, GLFW_RELEASE, mods);
}

bool GUI::OnScroll(double x, double y) {
	return m_pScreen->scrollCallbackEvent(x, y);
}

ObjectPropertyWindow *GUI::MakeObjectPropertyWindow() {
	return new ObjectPropertyWindow(m_pScreen);
}
