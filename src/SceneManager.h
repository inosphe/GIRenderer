//
// Created by inosphe on 2016. 6. 18..
//

#ifndef PROJECT_SCENEMANAGER_H
#define PROJECT_SCENEMANAGER_H

#include "common_header.h"
#include "IScene.h"

class ObjectPropertyWindow;

class IScene;

namespace Core{
	class Application;

	class SceneManager {

	public:
		SceneManager(Application* pApp);
		virtual ~SceneManager();

		bool Create();
		bool Destroy();

		void Update(int ms);
		void Render(Render::ShaderParam& shader);
		inline IScene* GetScene(){return m_pScene;}

	protected:
		Application* m_pApp = nullptr;
		IScene* m_pScene = nullptr;

		ObjectPropertyWindow* m_pWindow0 = nullptr;
	};
}
#endif //PROJECT_SCENEMANAGER_H
