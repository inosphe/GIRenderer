//
// Created by inosphe on 2016. 3. 28..
//

#include "DeferredRenderingStrategy.h"
#include <cassert>
#include "util/GLUtil.h"
#include "Exception.h"
#include "RenderingParameters.h"
#include "RenderPassDeferred0.h"
#include "Camera.h"

namespace Render{
	DeferredRenderingStrategy::DeferredRenderingStrategy():IRenderingStrategy(){

	}

	DeferredRenderingStrategy::~DeferredRenderingStrategy() {

	}

	void DeferredRenderingStrategy::Init() {
		IRenderingStrategy::Init();

		RenderPassDeferred0* pRenderPass0 = new RenderPassDeferred0();
		pRenderPass0->Init("shader/deferred.vert.glsl", "shader/deferred.frag.glsl");
		AddRenderPass(pRenderPass0, 0);

		RenderPass* pRenderPass1 = new RenderPass();
		pRenderPass1->Init("shader/quad.vert.glsl", "shader/quad.frag.glsl");
		AddRenderPass(pRenderPass1, 1);
	}

	void DeferredRenderingStrategy::Render(const Camera& camera, std::function<void()> fRenderModels) {
		RenderPassDeferred0* pRenderPass0 = dynamic_cast<RenderPassDeferred0*>(GetRenderPass(0));

		GLint viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );
		glViewport(0, 0, 640, 480);

		RenderBegin(0);
			GetShader().BindCamera(camera);
			fRenderModels();
		RenderEnd();

		int x = viewport[0];
		int y = viewport[1];
		int w = viewport[2];
		int h = viewport[3];

		RenderBegin(1);
			glActiveTexture(GL_TEXTURE0);

			glViewport(x, y, w/2, h/2);
			glBindTexture(GL_TEXTURE_2D, pRenderPass0->m_uGBufferTex[0]);
			GetShader().BindTexture(0);
			m_quad.Render(GetShader());

			glViewport(x+w/2, y, w/2, h/2);
			glBindTexture(GL_TEXTURE_2D, pRenderPass0->m_uGBufferTex[1]);
			GetShader().BindTexture(0);
			m_quad.Render(GetShader());

			glViewport(x, y+h/2, w/2, h/2);
			glBindTexture(GL_TEXTURE_2D, pRenderPass0->m_uGBufferTex[2]);
			GetShader().BindTexture(0);
			m_quad.Render(GetShader());

			glViewport(x+w/2, y+h/2, w/2, h/2);
			glBindTexture(GL_TEXTURE_2D, pRenderPass0->m_uGBufferTex[3]);
			GetShader().BindTexture(0);
			m_quad.Render(GetShader());
		RenderEnd();

		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	}
}
