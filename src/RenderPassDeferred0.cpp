//
// Created by inosphe on 2016. 6. 19..
//

#include <GL/glew.h>
#include <util/GLUtil.h>
#include "RenderPassDeferred0.h"

void Render::RenderPassDeferred0::Init(const char *szVertexShader, const char *szFragShader) {
	RenderPass::Init(szVertexShader, szFragShader);

	InitFramebuffer();
}

void Render::RenderPassDeferred0::InitFramebuffer() {
	glGenFramebuffers(1, &m_uGBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_uGBuffer);

	glGenTextures(4, m_uGBufferTex);

	for(int i=0; i<3; ++i){
		glBindTexture(GL_TEXTURE_2D, m_uGBufferTex[i]);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 640, 480);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	glBindTexture(GL_TEXTURE_2D, m_uGBufferTex[3]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, 640, 480);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_uGBufferTex[0], 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, m_uGBufferTex[1], 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, m_uGBufferTex[2], 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_uGBufferTex[3], 0);

	GLUtil::CheckError();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Render::RenderPassDeferred0::Clear() {
	glDeleteTextures(4, m_uGBufferTex);
	for(int i=0; i<4; ++i){
		m_uGBufferTex[i] = 0;
	}

	glDeleteFramebuffers(1, &m_uGBuffer);
	m_uGBuffer = 0;

	RenderPass::Clear();
}

void Render::RenderPassDeferred0::RenderBegin() {
	RenderPass::RenderBegin();
	glBindFramebuffer(GL_FRAMEBUFFER, m_uGBuffer);
	GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
	glDrawBuffers(3, drawBuffers);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::RenderPassDeferred0::RenderEnd() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	RenderPass::RenderEnd();
}
