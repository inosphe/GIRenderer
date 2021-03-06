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

	m_pMainCamera = std::shared_ptr<Render::Camera>(new Render::Camera());
	m_pMainCamera->Init();
	m_pMainCamera->SetPosition(glm::vec3(-202, 1123, -54.2));
	m_pMainCamera->SetDirection(glm::vec3(-0.5, -1, 0));
	m_app.SetCamera(m_pMainCamera);
	AddGameObject(std::shared_ptr<GameObject>(m_pMainCamera));

	for(auto scene : resources){
		auto model = new Render::FBXModel(scene, m_app.GetResourceManager());
		auto gameobj = std::shared_ptr<GameObject>(new GameObject(GameObject::Type::Entity, model));
		AddGameObject(gameobj);

//		gameobj->SetPosition(glm::vec3(0, 500, 0));
	}

	auto light = new Light();
	light->SetPosition(glm::vec3(-202, 1123, -54.2));
	light->SetDirection(glm::vec3(-0.5, -1, 0));
	light->SetIntensity(1000.0f);
	AddGameObject(std::shared_ptr<GameObject>(light));
}

TestScene3::~TestScene3() {
	models.clear();
}

TestScene3::TestScene3(Core::Application &app)
:IScene(app)
, tween(glm::vec3(-202, 1123, -300), glm::vec3(-202, 1123, 300), 10.0f)
, tween_intensity(glm::vec3(500.0f, 0.0f, 0.0f), glm::vec3(1500.0f, 0.0f, 0.0f), 5.0f)
{

}

void TestScene3::Update(int ms) {
	IScene::Update(ms);

	tween.Update(ms/1000.0f);
	tween_intensity.Update(ms/1000.0f);

	auto light0 = m_vecLights[0];
	if(light0.get()){
		//light0->SetPosition(tween.GetValue());
		//dynamic_cast<Light*>(light0.get())->SetIntensity(tween_intensity.GetValue().x);
	}
}
