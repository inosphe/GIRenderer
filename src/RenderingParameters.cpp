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

		GLUtil::CheckError();
	}

	void RenderingParameters::Clear() {

	}

	void RenderingParameters::SetObjectTransform(const glm::mat4x4 &matTransform) {
		if(m_uTransformLocation<0)
			return;

		glUniformMatrix4fv(m_uTransformLocation, 1, GL_FALSE, glm::value_ptr(matTransform));
//		assert(glGetError() == GL_NO_ERROR);
	}

	void RenderingParameters::BindCamera(const Camera& camera) {
		if(m_uViewProjLocation >= 0){
			// set the uniform
			GLUtil::CheckError();
			glm::mat4 matViewProj = camera.GetViewProj();
			glUniformMatrix4fv(m_uViewProjLocation, 1, GL_FALSE, value_ptr(matViewProj));
			GLUtil::CheckError();
		}

		if(m_uLookLocation >= 0){
			auto dir = camera.Dir();
			dir = glm::normalize(dir);
			glUniform3fv(m_uLookLocation, 1, value_ptr(dir));
		}

		GLUtil::CheckError();
		assert(glGetError() == GL_NO_ERROR);
	}

	void RenderingParameters::BindTexture(int index) {
		if(m_uTextureLocation < 0)
			return;
		assert(index == 0);

		glUniform1i(m_uTextureLocation, index);
//		assert(glGetError() == GL_NO_ERROR);
	}
}
