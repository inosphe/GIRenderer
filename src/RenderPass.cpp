//
// Created by inosphe on 2016. 6. 19..
//

#include <GLFW/glfw3.h>
#include <util/GLUtil.h>
#include "RenderPass.h"
#include "Exception.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>

namespace Render{
	void RenderPass::Init(const char* szVertShader, const char* szFragShader) {
		try{
			m_uProgram = glCreateProgram();
			glAttachShader(m_uProgram, GLUtil::LoadShader(GL_VERTEX_SHADER, szVertShader));
			glAttachShader(m_uProgram, GLUtil::LoadShader(GL_FRAGMENT_SHADER, szFragShader));
			glLinkProgram(m_uProgram);

			ShaderParam::Init();
		}
		catch(const Core::Exception& ex){
			assert(false);
		}
	}

	void RenderPass::Clear() {
		if(m_uProgram)
			glDeleteProgram(m_uProgram);
		m_uProgram = 0;
	}

	void RenderPass::RenderBegin() {
		glDisable(GL_BLEND);
		glUseProgram(m_uProgram);
	}

	void RenderPass::RenderEnd() {
	}

}