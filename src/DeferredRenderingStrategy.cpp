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
		pRenderPass0->Init("shader/deferred.vert.glsl", "shader/rsm.frag.glsl");
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

		uint32_t nRenderPass = 0;
#define RENDERPSASS (nRenderPass++)

		RenderBegin(RENDERPSASS);
			GetShader().BindCamera(camera);
			fRenderModels();
		RenderEnd();
//
//		RenderBegin(RENDERPSASS);
//			glViewport(x, y, w, h);
//			glBindTexture(GL_TEXTURE_2D, pRenderPass0->m_uGBufferTex[3]);
//			GetShader().BindTexture(0);
//			m_quad.Render(GetShader());
//		RenderEnd();

		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

		GLuint nTexScreen[4] = {
			pRenderPass0->m_uGBufferTex[3]
			, pRenderPass0->m_uGBufferTex[1]
			, pRenderPass0->m_uGBufferTex[2]
			, pRenderPass0->m_uGBufferTex[4]
		};

		RenderToScreen(RENDERPSASS, nTexScreen, 4);
	}

	void DeferredRenderingStrategy::RenderToScreen(int nRenderPass, GLuint* textures, int num) {
		GLint viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		int sx = viewport[0];
		int sy = viewport[1];
		int sw = viewport[2];
		int sh = viewport[3];

		RenderBegin(nRenderPass);
			GLint max_num = std::min(num, 4);
			for(int i=0; i<max_num; ++i){
				if(textures[i] >= 0){
					int x = sx + sw/2*(i%2);
					int y = sy + sh/2*(i/2);
					int w = sw/2;
					int h = sh/2;
					glViewport(x, y, w, h);
					GetShader().BindTexture(0, textures[i]);
					m_quad.Render(GetShader());
				}
			}
		RenderEnd();

		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	}
}
