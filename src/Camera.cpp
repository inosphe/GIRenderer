//
// Created by inosphe on 2016. 4. 5..
//

#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

namespace Render{
	Camera::Camera() {
		SetName("Main camera");
	}

	Camera::~Camera() {

	}

	void Camera::Init() {
		SetPosition(glm::vec3(0, 250.0f, 50.0f));
	}

	const glm::mat4 Camera::GetViewProj() const{
		glm::mat4 identity(1.0f);

		// calculate ViewProjection matrix

		glm::vec3 dir = glm::vec3(0.0f, 0.0f, -1.0f) * m_qRotation;

		glm::vec3 center = m_vPosition + dir;

		glm::mat4 Projection = glm::perspective(70.0f, 4.0f / 3.0f, 10.0f, 2000.f);
		glm::mat4 View = glm::lookAtRH(m_vPosition, center, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 ViewProjection = Projection*View;

		return ViewProjection;
	}

}
