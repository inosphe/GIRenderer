//
// Created by inosphe on 2016. 6. 18..
//

#include "GameObject.h"
#include "IModel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

int GameObject::Counter = 0;

GameObject::GameObject():IMovableObject(), m_eType(GameObject::Type::Entity), m_ID(Counter++) {
	string name = "GameObject";
	name += m_ID;
	SetName(name);
}

GameObject::GameObject(Type type):IMovableObject(), m_eType(type), m_ID(Counter++) {
	string name = "GameObject";
	name += m_ID;
	SetName(name);
}

GameObject::GameObject(Type type, Render::IModel *pModel):IMovableObject(), m_eType(type), m_pModel(pModel), m_ID(Counter++) {
	string name = "GameObject";
	name += m_ID;
	SetName(name);
}

GameObject::~GameObject() {

}

void GameObject::SetName(const string &strName) {
	m_strName = strName;
}

void GameObject::Render(Render::ShaderParam& shader) {
	if(m_pModel)
		m_pModel->Render(shader);
}

void GameObject::Update(int ms) {
	IMovableObject::Update(ms);
	if(m_pModel)
		m_pModel->UpdateForRender();
}

const glm::mat4 GameObject::GetViewProj() const{
	glm::mat4 identity(1.0f);

	// calculate ViewProjection matrix

	glm::vec3 dir = glm::vec3(0.0f, 0.0f, -1.0f) * m_qRotation;

	glm::vec3 center = m_vPosition + dir;

	glm::mat4 Projection = glm::perspective(70.0f, 4.0f / 3.0f, 1.0f, 10000.f);
	glm::mat4 View = glm::lookAtRH(m_vPosition, center, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 ViewProjection = Projection*View;

	return ViewProjection;
}