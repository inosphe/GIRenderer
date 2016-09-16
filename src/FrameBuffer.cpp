//
// Created by inosphe on 2016. 9. 15..
//

#include <GL/glew.h>
#include <string.h>
#include "FrameBuffer.h"

Render::FrameBuffer::FrameBuffer(int nTextureNum)
:m_nTextureNum(nTextureNum){

}

Render::FrameBuffer::~FrameBuffer() {

}

void Render::FrameBuffer::Init() {
	m_uTextures = new GLuint[m_nTextureNum];
	memset(m_uTextures, 0, sizeof(GLuint)*m_nTextureNum);

	glGenFramebuffers(1, &m_uGBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_uGBuffer);

	glGenTextures(m_nTextureNum, m_uTextures);
	for(int i=0; i<m_nTextureNum; ++i){
		glBindTexture(GL_TEXTURE_2D, m_uTextures[i]);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 640, 480);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	glGenTextures(1, &m_uDepthMap);
	glBindTexture(GL_TEXTURE_2D, m_uDepthMap);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, 640, 480);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for(int i=0; i<m_nTextureNum; ++i){
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, m_uTextures[i], 0);
	}
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_uDepthMap, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Render::FrameBuffer::Clear() {
	if(m_uTextures){
		glDeleteTextures(m_nTextureNum, m_uTextures);
		glDeleteTextures(1, &m_uDepthMap);
		glDeleteFramebuffers(1, &m_uGBuffer);

		SAFE_DELETE_ARRAY(m_uTextures);
		m_uTextures = nullptr;
	}

	m_uDepthMap = 0;
}

void Render::FrameBuffer::RenderBegin() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_uGBuffer);
	GLenum drawBuffers[m_nTextureNum];
	for(int i=0; i<m_nTextureNum; ++i)
		drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(m_nTextureNum, drawBuffers);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::FrameBuffer::RenderEnd() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
