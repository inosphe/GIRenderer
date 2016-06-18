//
// Created by inosphe on 2016. 6. 18..
//

#include "GameObject.h"
#include "IModel.h"

int GameObject::Counter = 0;

GameObject::GameObject():IMovableObject(), m_ID(Counter++) {
	string name = "GameObject";
	name += m_ID;
	SetName(name);
}

GameObject::GameObject(Render::IModel *pModel):IMovableObject(), m_pModel(pModel), m_ID(Counter++) {
	string name = "GameObject";
	name += m_ID;
	SetName(name);
}

GameObject::~GameObject() {

}

void GameObject::SetName(const string &strName) {
	m_strName = strName;
}

void GameObject::Render(Render::RenderingParameters &rp) {
	if(m_pModel)
		m_pModel->Render(rp);
}

void GameObject::Update(int ms) {
	IMovableObject::Update(ms);
	if(m_pModel)
		m_pModel->UpdateForRender();
}
