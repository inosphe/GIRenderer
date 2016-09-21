//
// Created by inosphe on 2016. 4. 8..
//

#include "TestScene3.h"
#include "ResourceManager.h"
#include "IModel.h"
#include "Camera.h"
#include "FBXModel.h"
#include "Light.h"

void TestScene3::Init() {
	IScene::Init();

	auto resources = m_app.GetResourceManager().LoadFBXFromConfig("resources.txt");

	for(auto scene : resources){
		auto model = new Render::FBXModel(scene, m_app.GetResourceManager());
		m_gameObjects.push_back(std::shared_ptr<GameObject>(new GameObject(model)));
	}

	m_pMainCamera = std::shared_ptr<Render::Camera>(new Render::Camera());
	m_pMainCamera->Init();
	m_pMainCamera->SetPosition(glm::vec3(-202, 1123, -54.2));
	m_pMainCamera->SetDirection(glm::vec3(-0.5, -1, 0));
	m_app.SetCamera(m_pMainCamera);
	m_gameObjects.push_back(std::shared_ptr<GameObject>(m_pMainCamera));

	auto light = new Light();
	light->SetDirection(glm::vec3(1.0, -1.0, 1.0));
	m_gameObjects.push_back(std::shared_ptr<GameObject>(light));

}

TestScene3::~TestScene3() {
	models.clear();
}

TestScene3::TestScene3(Core::Application &app)
:IScene(app)
{

}