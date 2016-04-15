//
// Created by inosphe on 2016. 4. 8..
//

#include "TestScene3.h"
#include "ResourceManager.h"
#include "IModel.h"
#include "Camera.h"
#include "FBXModel.h"

void TestScene3::Init() {
	IScene::Init();

	auto resources = m_app.GetResourceManager().LoadFBXFromConfig("resources.txt");

	for(auto scene : resources){
		models.push_back(std::shared_ptr<Render::IModel>(new Render::FBXModel(scene, m_app.GetResourceManager())));
	}

	m_pMainCamera = std::shared_ptr<Render::Camera>(new Render::Camera());
	m_pMainCamera->Init();
	m_app.SetCamera(m_pMainCamera);
}

TestScene3::~TestScene3() {
	models.clear();
}

TestScene3::TestScene3(Core::Application &app)
:IScene(app)
{

}

void TestScene3::Render(Render::RenderingParameters &rp) {
	models[0]->Render(rp);
}

void TestScene3::Update(int ms) {
//	models[0]->Update(ms);
	models[0]->UpdateForRender();

	m_pMainCamera->Update(ms);
}
