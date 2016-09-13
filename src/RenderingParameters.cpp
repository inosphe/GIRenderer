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
#include <sstream>

namespace Render{
	RenderingParameters::RenderingParameters(GLuint uProgram)
	:m_uProgram(uProgram)
	{

	}

	void RenderingParameters::Init() {
		m_uTransformLocation = glGetUniformLocation(m_uProgram, "ObjectTransform");
		m_uLookLocation = glGetUniformLocation(m_uProgram, "Look");
		m_uCameraPosLocation = glGetUniformLocation(m_uProgram, "CameraPos");
		m_uViewProjLocation = glGetUniformLocation(m_uProgram, "ViewProjection");

		assert(m_nTextureNum>0);

		for(int i=0; i<m_nTextureNum; ++i){
			const std::ostringstream& strTexVarName = static_cast<const std::ostringstream&>(std::ostringstream() << "Tex" << std::dec << i);
			const char* szTexVarName = strTexVarName.str().c_str();
			const GLint loc = glGetUniformLocation(m_uProgram, szTexVarName);
			m_vecTextureLocation.push_back(loc);
		}

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

		if(m_uCameraPosLocation >= 0){
			glUniform3fv(m_uCameraPosLocation, 1, value_ptr(camera.GetPosition()));
		}

		GLUtil::CheckError();
		assert(glGetError() == GL_NO_ERROR);
	}

	void RenderingParameters::BindTexture(int index, GLuint uTexture) {
		if(index < m_vecTextureLocation.size()){
			GLint loc = m_vecTextureLocation[index];
			if(loc >= 0)
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, uTexture);
				glUniform1i(loc, 0);
		}
	}

	void RenderingParameters::SetTextureNum(uint32_t nTextureNum) {
		m_nTextureNum = nTextureNum;
	}
}
