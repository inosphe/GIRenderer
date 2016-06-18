//
// Created by inosphe on 2016. 4. 6..
//

#include "IScene.h"

IScene::IScene(Core::Application& app)
:m_app(app)
{

}

void IScene::Update(int ms) {
	for(auto obj: GetObjects()){
		obj->Update(ms);
	}
}

void IScene::Render(Render::RenderingParameters &rp) {
	for(auto model: GetObjects()){
		model->Render(rp);
	}
}
