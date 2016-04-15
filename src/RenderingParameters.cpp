//
// Created by inosphe on 2016. 4. 8..
//

#include "IScene.h"
#include "Camera.h"
#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <util/GLUtil.h>
#include "RenderingParameters.h"
#include "Texture.h"


namespace Render{
	RenderingParameters::RenderingParameters(GLuint uProgram)
	:m_uProgram(uProgram)
	{

	}

	void RenderingParameters::Init() {
		m_uTransformLocation = glGetUniformLocation(m_uProgram, "ObjectTransform");
		m_uLookLocation = glGetUniformLocation(m_uProgram, "Look");
		m_uViewProjLocation = glGetUniformLocation(m_uProgram, "ViewProjection");
		m_uTextureLocation = glGetUniformLocation(m_uProgram, "Tex0");
	}

	void RenderingParameters::SetObjectTransform(const glm::mat4x4 &matTransform) {
		glUniformMatrix4fv(m_uTransformLocation, 1, GL_FALSE, glm::value_ptr(matTransform));
//		assert(glGetError() == GL_NO_ERROR);
	}

	void RenderingParameters::BindCamera(Camera *pCamera) {
		// set the uniform
		glUniformMatrix4fv(m_uViewProjLocation, 1, GL_FALSE, value_ptr(pCamera->GetViewProj()));
		auto dir = pCamera->Dir();
		dir = glm::normalize(dir);
		glUniform3fv(m_uLookLocation, 1, value_ptr(dir));
		assert(glGetError() == GL_NO_ERROR);
	}

	void RenderingParameters::BindTexture(int index, const GLuint id) {
		assert(index == 0);

		glUniform1i(m_uTextureLocation, id);
//		assert(glGetError() == GL_NO_ERROR);
	}
}
