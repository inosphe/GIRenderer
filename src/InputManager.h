//
// Created by inosphe on 2016. 4. 14..
//

#ifndef PROJECT_INPUTMANAGER_H
#define PROJECT_INPUTMANAGER_H

#include <vector>

class GLFWwindow;
class GLFWcursor;

namespace Core{
	class InputDelegate;

	class InputManager {
	public:
		void Init(GLFWwindow* pWindow);
		void AddDelegate(InputDelegate* pDelegate);
		void RemoveDelegate(InputDelegate* pDelegate);
		void Clear();

		void OnMousePos(int x, int y);

	protected:
		static void OnMouseButton(GLFWwindow *w, int button, int action, int modifiers);
		static void OnKey(GLFWwindow *w, int key, int scancode, int action, int mods);
		static void OnScroll(GLFWwindow *w, double x, double y);

	private:
		std::vector<InputDelegate*> m_vecInputDelegates;
		GLFWcursor* m_pCursor = nullptr;
	};
}


#endif //PROJECT_INPUTMANAGER_H
