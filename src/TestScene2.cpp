//
// Created by inosphe on 2016. 4. 6..
//

#include "TestScene2.h"
#include "Camera.h"

TestScene2::TestScene2(Core::Application& app)
:IScene(app)
{

}

void TestScene2::Init() {
	model.Init();
	m_pMainCamera = std::shared_ptr<Render::Camera>(new Render::Camera());
	m_pMainCamera->Init();
	m_app.SetCamera(m_pMainCamera);
}

void TestScene2::Update(int ms) {
	model.Update(ms);
}

void TestScene2::Render(Render::RenderingParameters& rp) {
	model.Render(rp);
}
