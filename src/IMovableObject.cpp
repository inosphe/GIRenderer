//
// Created by inosphe on 2016. 4. 5..
//

#include "IMovableObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


IMovableObject::IMovableObject()
:m_vPosition(0.0f), m_vScale(1.0f)
{

}

IMovableObject::~IMovableObject() {

}

void IMovableObject::SetPosition(const glm::vec3 &pos) {
	m_vPosition = pos;
}

void IMovableObject::Up(){
	Move(glm::vec3(0, 0, -1));
}

void IMovableObject::Down() {
	Move(glm::vec3(0, 0, 1));
}

void IMovableObject::Left() {
	Move(glm::vec3(-1, 0, 0));
}

void IMovableObject::Right() {
	Move(glm::vec3(1, 0, 0));
}

void IMovableObject::Stop() {
	m_vVelocity = glm::vec3(0.0f);
}

void IMovableObject::Move(const glm::vec3 &move) {
	auto zaxis = Dir();
	auto yaxis = glm::vec3(0.0f, 1.0f, 0.0f);
	auto xaxis = glm::cross(yaxis, zaxis);
	m_vVelocity = move.x * xaxis * 300.0f;
	m_vVelocity += move.y * yaxis * 300.0f;
	m_vVelocity += move.z * zaxis * 300.0f;
}

glm::mat4x4 IMovableObject::GetTransform() {
	glm::mat4x4 matTranslate = glm::translate(glm::mat4x4(1.0f), m_vPosition);
	glm::mat4x4 matRotate = glm::toMat4(m_qRotation);
	glm::mat4x4 matScale = glm::scale(glm::mat4x4(1.0f), m_vScale);
	return matTranslate*matRotate*matScale;
}

void IMovableObject::Rotate(float tx, float ty) {
	auto zaxis = glm::vec3(0.0f, 0.0f, 1.0f) * m_qRotation;
	auto yaxis = glm::vec3(0.0f, 1.0f, 0.0f);
	auto xaxis = glm::cross(yaxis, zaxis);

	m_qRotation = glm::rotate(m_qRotation, tx, yaxis);
	m_qRotation = glm::rotate(m_qRotation, ty, xaxis);
}

void IMovableObject::Update(int ms) {
	m_vPosition += m_vVelocity * (ms / 1000.0f);
}

glm::vec3 IMovableObject::Dir() {
	return glm::vec3(0.0f, 0.0f, 1.0f) * m_qRotation;
}

void IMovableObject::SetDirection(const glm::vec3 &dir) {
//	m_qRotation = glm::angleAxis()
	glm::vec3 a, b;
	a = glm::normalize(dir);
	b = glm::vec3(.0f, .0f, -1.0f);
	glm::vec3 axis = glm::cross(a, b);
	float rad = glm::dot(a, b);
	m_qRotation = glm::angleAxis(rad, axis);
}
