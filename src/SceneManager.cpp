//
// Created by inosphe on 2016. 6. 18..
//

#include "SceneManager.h"
#include "TestScene3.h"
#include "Renderer.h"
#include "ObjectPropertyWindow.h"
#include "GUI.h"
#include "TestScene3.h"

namespace Core{
	SceneManager::SceneManager(Application *pApp):m_pApp(pApp) {

	}

	SceneManager::~SceneManager() {
		Destroy();
	}

	bool SceneManager::Create() {
		m_pScene = new TestScene3(*m_pApp);
		m_pScene->Init();

		m_pWindow0 = m_pApp->GetGUI().MakeObjectPropertyWindow();
		m_pWindow0->SetObjects(m_pScene->GetObjects());

		return true;
	}

	bool SceneManager::Destroy() {
		SAFE_DELETE(m_pScene);
		SAFE_DELETE(m_pWindow0);
		return true;
	}

	void SceneManager::Update(int ms) {
		m_pScene->Update(ms);
		m_pWindow0->Update();
	}

	void SceneManager::Render(Render::ShaderParam& shader) {
		m_pScene->Render(shader);
	}
}
