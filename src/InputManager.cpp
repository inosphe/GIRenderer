//
// Created by inosphe on 2016. 4. 14..
//

#include "InputManager.h"
#include "Logger.h"
#include <InputDelegate.h>
#include <GLFW/glfw3.h>
#include <map>

static std::map<GLFWwindow*, Core::InputManager*> mapCallbackDelegate;

namespace Core{
	void InputManager::Init(GLFWwindow *pWindow) {
		mapCallbackDelegate[pWindow] = this;


//		glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//		glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_pCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		glfwSetCursor(pWindow, m_pCursor);

		glfwSetMouseButtonCallback(pWindow, &InputManager::OnMouseButton);
		glfwSetKeyCallback(pWindow, &InputManager::OnKey);
		glfwSetScrollCallback(pWindow, &InputManager::OnScroll);
	}

	void InputManager::OnMouseButton(GLFWwindow *w, int button, int action, int modifiers) {
//		Logger::Debug("OnMouseButton");
		for(auto id : mapCallbackDelegate[w]->m_vecInputDelegates){
			if(id->OnMouseButton(button, action, modifiers))
				break;
		}
	}


	void InputManager::OnKey(GLFWwindow *w, int key, int scancode, int action, int mods) {
		auto f = [key, action, mods](auto id, int scancode){
			switch(action){
				case GLFW_PRESS:
					return id->OnKeyPress(key, action, mods);
				case GLFW_REPEAT:
					return id->OnKeyRepeat(key, action, mods);
				case GLFW_RELEASE:
					return id->OnKeyRelease(key, action, mods);
				default:
					return true;

			}
		};

		for(auto id : mapCallbackDelegate[w]->m_vecInputDelegates){
			if(f(id, scancode))
				break;
		}
	}

	void InputManager::OnScroll(GLFWwindow *w, double x, double y) {
		for(auto id : mapCallbackDelegate[w]->m_vecInputDelegates){
			if(id->OnScroll(x, y))
				break;
		}
	}

	void InputManager::AddDelegate(InputDelegate *pDelegate) {
		m_vecInputDelegates.push_back(pDelegate);
	}

	void InputManager::RemoveDelegate(InputDelegate *pDelegate) {
		std::remove(m_vecInputDelegates.begin(), m_vecInputDelegates.end(), pDelegate);
	}

	void InputManager::Clear() {
		if(m_pCursor)
			glfwDestroyCursor(m_pCursor);
		m_pCursor = nullptr;
	}

	void InputManager::OnMousePos(int x, int y) {
		for(auto id : m_vecInputDelegates){
			if(id->OnMousePos(x, y))
				break;
		}
	}
}

