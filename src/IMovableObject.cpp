//
// Created by inosphe on 2016. 4. 5..
//

#include "IMovableObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

glm::vec3 XAXIS(1.0f, .0f, .0f);
glm::vec3 YAXIS(.0f, 1.0f, .0f);
glm::vec3 ZAXIS(.0f, .0f, -1.0f);


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
	Move(-ZAXIS);
}

void IMovableObject::Down() {
	Move(ZAXIS);
}

void IMovableObject::Left() {
	Move(-XAXIS);
}

void IMovableObject::Right() {
	Move(XAXIS);
}

void IMovableObject::Stop() {
	m_vVelocity = glm::vec3(0.0f);
}

void IMovableObject::Move(const glm::vec3 &move) {
	auto zaxis = Dir();
	auto yaxis = YAXIS;
	auto xaxis = glm::cross(zaxis, yaxis);
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
	auto zaxis = ZAXIS * m_qRotation;
	auto yaxis = YAXIS;
	auto xaxis = glm::cross(zaxis, yaxis);

	m_qRotation = glm::rotate(m_qRotation, tx, yaxis);
	m_qRotation = glm::rotate(m_qRotation, ty, xaxis);
}

void IMovableObject::Update(int ms) {
	m_vPosition += m_vVelocity * (ms / 1000.0f);
}

glm::vec3 IMovableObject::Dir() const{
	return ZAXIS * m_qRotation;
}

void IMovableObject::SetDirection(const glm::vec3 &dir) {
//	m_qRotation = glm::angleAxis()
	glm::vec3 a, b;
	a = ZAXIS;
	b = glm::normalize(dir);
	glm::vec3 axis = glm::cross(a, b);
	float rad = glm::dot(a, b);
	m_qRotation = glm::angleAxis(rad, axis);
}

glm::vec3 IMovableObject::GetEuler() {
	return glm::eulerAngles(m_qRotation);
}


void IMovableObject::SetEuler(glm::vec3 &rot) {
	glm::quat qx = glm::angleAxis(rot.x, XAXIS);
	glm::quat qy = glm::angleAxis(rot.y, YAXIS);
	glm::quat qz = glm::angleAxis(rot.z, ZAXIS);
	m_qRotation = qx*qy*qz;
}

void IMovableObject::SetEulerElement(int i, float v) {
	glm::vec3 euler = GetEuler();
	euler[i] = v;
	SetEuler(euler);
}
