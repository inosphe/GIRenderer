//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_APPLICATION_H
#define PROJECT_APPLICATION_H

class GLFWwindow;
class IScene;

#include "KeyMap.h"
#include "ResourceManager.h"
#include "AppState.h"
#include <map>

namespace Render{
	class Renderer;
	class Camera;
}

namespace Resource{
	class ResourceManager;
}

class IMovableObject;
class GUI;

namespace Core {
	class Timer;
	class InputManager;
	class SceneManager;

	class Application {
	public:
		Application(GLFWwindow* pWindow);
		~Application();

		bool Initialize();
		void InitInputs();
		void Clear();

		void Update();
		void Render();


		void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
		inline Resource::ResourceManager& GetResourceManager(){return *m_pResourceManager;}

		void SetCamera(std::shared_ptr<Render::Camera> pCamera);
		GUI& GetGUI(){return *m_pGUI;}

	private:
		bool InitResourceManager();

	private:
		AppState m_state;
		GLFWwindow* m_pWindow = nullptr;
		Resource::ResourceManager* m_pResourceManager = nullptr;
		Render::Renderer * m_pRenderer = nullptr;
		SceneManager* m_pSceneManager = nullptr;
		IMovableObject* m_pMoveTarget = nullptr;
		Core::Timer* m_pTimer = nullptr;

		std::map<ACTION_MAP_TYPE::first_type, ACTION_MAP_TYPE::second_type> m_mapActionKeys;

		GUI* m_pGUI = nullptr;

		InputManager* m_pInputManager = nullptr;
	};
}

#endif //PROJECT_APPLICATION_H



