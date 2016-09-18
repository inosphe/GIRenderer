//
// Created by inosphe on 2016. 6. 19..
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <util/GLUtil.h>
#include "RenderPass.h"
#include "Exception.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>

namespace Render{
	void RenderPass::Init(const char* szVertShader, const char* szGeoShader, const char* szFragShader) {
		try{
			ShaderParam::InitProgram();

			LoadShader(GL_VERTEX_SHADER, szVertShader);
			LoadShader(GL_GEOMETRY_SHADER, szGeoShader);
			LoadShader(GL_FRAGMENT_SHADER, szFragShader);
			glLinkProgram(GetProgram());

			ShaderParam::InitVariables();
		}
		catch(const Core::Exception& ex){
			assert(false);
		}
	}

	void RenderPass::Init(const std::vector<std::pair<GLuint, std::string>>& vecShaders) {
		try{
			ShaderParam::InitProgram();

			for(auto shader : vecShaders){
				LoadShader(shader.first, shader.second.c_str());
			}
			glLinkProgram(GetProgram());

			ShaderParam::InitVariables();
		}
		catch(const Core::Exception& ex){
			assert(false);
		}
	}

	void RenderPass::Clear() {
		ShaderParam::Clear();

		if(m_pFrameBuffer){
			m_pFrameBuffer->Clear();
			m_pFrameBuffer = nullptr;
		}
	}

	void RenderPass::RenderBegin() {
		glDisable(GL_BLEND);
		glUseProgram(GetProgram());

		if(m_pFrameBuffer){
			m_pFrameBuffer->RenderBegin();
		}
		else{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	void RenderPass::RenderEnd() {
		if(m_pFrameBuffer){
			m_pFrameBuffer->RenderEnd();
		}
		else{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	void RenderPass::LoadShader(GLuint type, const char *szShader) {
		if(szShader)
			glAttachShader(GetProgram(), GLUtil::LoadShader(type, szShader));
	}
}