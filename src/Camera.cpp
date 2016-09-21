//
// Created by inosphe on 2016. 4. 5..
//

#include "Camera.h"

namespace Render{
	Camera::Camera():GameObject(GameObject::Type::Camera) {
		SetName("Main camera");
	}

	Camera::~Camera() {

	}

	void Camera::Init() {
		SetPosition(glm::vec3(0, 250.0f, 50.0f));
	}
}
