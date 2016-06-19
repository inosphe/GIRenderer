//
// Created by inosphe on 2016. 6. 19..
//

#include <GLFW/glfw3.h>
#include <util/GLUtil.h>
#include "RenderPass.h"
#include "Exception.h"
#include "RenderingParameters.h"

namespace Render{
	void RenderPass::Init(const char* szVertShader, const char* szFragShader) {
		try{
			m_uProgram = glCreateProgram();
			glAttachShader(m_uProgram, GLUtil::LoadShader(GL_VERTEX_SHADER, szVertShader));
			glAttachShader(m_uProgram, GLUtil::LoadShader(GL_FRAGMENT_SHADER, szFragShader));
			glLinkProgram(m_uProgram);

			m_pParameters = new RenderingParameters(m_uProgram);
			m_pParameters->Init();
		}
		catch(const Core::Exception& ex){
			assert(false);
		}
	}

	void RenderPass::Clear() {
		if(m_uProgram)
			glDeleteProgram(m_uProgram);
		m_uProgram = 0;

		if(m_pParameters)
			m_pParameters->Clear();
		SAFE_DELETE(m_pParameters);
	}

	void RenderPass::RenderBegin() {
		glDisable(GL_BLEND);
		glUseProgram(m_uProgram);
	}

	void RenderPass::RenderEnd() {
	}
}