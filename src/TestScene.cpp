//
// Created by inosphe on 2016. 4. 3..
//

#include "TestScene.h"
#include "Camera.h"

TestScene::TestScene(Core::Application& app)
:IScene(app)
{

}

void TestScene::Init() {
	model.Init();
	m_pMainCamera = std::shared_ptr<Render::Camera>(new Render::Camera());
	m_app.SetCamera(m_pMainCamera);
}

void TestScene::Update(int ms) {

}

void TestScene::Render(Render::ShaderParam& shader) {
	model.Render(shader);
}
