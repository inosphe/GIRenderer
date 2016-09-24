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
			glValidateProgram(GetProgram());
			GLUtil::CheckError();

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
			glValidateProgram(GetProgram());
			GLUtil::CheckError();

			ShaderParam::InitVariables();

		}
		catch(const Core::Exception& ex){
			assert(false);
		}
	}

	void RenderPass::Clear() {
		ShaderParam::Clear();

		for(auto fb : m_vecFrameBuffers){
			fb->Clear();
		}

		m_vecFrameBuffers.clear();
	}

	void RenderPass::RenderBegin(int iFrameBuffer, bool bClear) {
		UseFrameBuffer(iFrameBuffer);
		RenderBegin(m_pCurFrameBuffer.get(), bClear);
	}

	void RenderPass::RenderBegin(FrameBuffer *pFB, bool bClear) {
		BindProgram();

		if(pFB){
			pFB->RenderBegin(bClear);
		}
		else{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			if(bClear)
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}

	void RenderPass::RenderEnd() {
		if(m_pCurFrameBuffer){
			m_pCurFrameBuffer->RenderEnd();
		}
		else{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}

	void RenderPass::LoadShader(GLuint type, const char *szShader) {
		if(szShader)
			glAttachShader(GetProgram(), GLUtil::LoadShader(type, szShader));
	}

	void RenderPass::SetFrameBuffer(std::shared_ptr<FrameBuffer> pFrameBuffer, int at) {
		for(int i=m_vecFrameBuffers.size(); i<=at; ++i){
			m_vecFrameBuffers.push_back(nullptr);
		}
		m_vecFrameBuffers[at] = pFrameBuffer;
	}

	std::shared_ptr<FrameBuffer> RenderPass::GetFrameBuffer(int at) {
		if(at < m_vecFrameBuffers.size()){
			return m_vecFrameBuffers[at];
		}
		else{
			return nullptr;
		}
	}

	void RenderPass::UseFrameBuffer(int at) {
		m_pCurFrameBuffer = GetFrameBuffer(at);
	}
}