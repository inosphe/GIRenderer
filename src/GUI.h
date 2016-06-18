//
// Created by inosphe on 2016. 4. 14..
//

#ifndef PROJECT_GUI_H
#define PROJECT_GUI_H


#include <nanogui/object.h>
#include <InputDelegate.h>

class NanoGUIImplementation;
class GLFWwindow;
class ObjectPropertyWindow;

class GUI : public Core::InputDelegate{
public:
	GUI(GLFWwindow* pWindow);
	virtual ~GUI();
	void Init();
	void Render();
	void Clear();

	virtual bool OnMouseButton(int button, int action, int modifier);

	virtual bool OnMousePos(int x, int y);
	virtual bool OnKeyPress(int key, int scancode, int mods);
	virtual bool OnKeyRepeat(int key, int scancode, int mods);
	virtual bool OnKeyRelease(int key, int scancode, int mods);
	virtual bool OnScroll(double x, double y);

	ObjectPropertyWindow* MakeObjectPropertyWindow();

private:
	GLFWwindow* m_pWindow = nullptr;
	nanogui::ref<NanoGUIImplementation> m_pScreen;
};


#endif //PROJECT_GUI_H
