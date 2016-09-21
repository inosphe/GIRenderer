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

void IScene::Render(Render::ShaderParam& shader) {
	for(auto model: GetEntities()){
		model->Render(shader);
	}
}

void IScene::AddGameObject(GameObject::PTR pObject) {
	switch(pObject->GetType()){
		case GameObject::Type::Entity:
			m_vecEntities.push_back(pObject);
			break;
		case GameObject::Type::Light:
			m_vecLights.push_back(pObject);
			break;
		case GameObject::Type::Camera:
			break;
	}

	m_vecObjects.push_back(pObject);
}
