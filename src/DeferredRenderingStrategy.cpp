//
// Created by inosphe on 2016. 3. 28..
//

#include "DeferredRenderingStrategy.h"
#include <cassert>
#include "util/GLUtil.h"
#include "Exception.h"
#include "RenderPassDeferred0.h"
#include "Camera.h"

namespace Render{
	DeferredRenderingStrategy::DeferredRenderingStrategy():IRenderingStrategy(){

	}

	DeferredRenderingStrategy::~DeferredRenderingStrategy() {

	}

	void DeferredRenderingStrategy::Init() {
		IRenderingStrategy::Init();

		RenderPassDeferred0* pGPass = new RenderPassDeferred0();
		pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::VIEWPROJ, "ViewProjection");
		pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TRANSFORM, "ObjectTransform");
		pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX0, "Tex0");
		pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::CAMERA_POS, "CameraPos");
		pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LOOK, "Look");
		pGPass->Init("shader/deferred.vert.glsl", "shader/rsm.frag.glsl");
		AddRenderPass(pGPass, 0);

		RenderPass* pLightPass0 = new RenderPass();
		pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_DIFFUSE, "Diffuse");
		pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_POS, "Pos");
		pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, "Normal");
		pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_VOLUME_TEST, "LV");
		pLightPass0->Init("shader/quad.vert.glsl", "shader/testlighting.frag.glsl");
		AddRenderPass(pLightPass0, 1);

		RenderPass* pScreenPass = new RenderPass();
		pScreenPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX0, "Tex0");
		pScreenPass->Init("shader/quad.vert.glsl", "shader/quad.frag.glsl");
		AddRenderPass(pScreenPass, 2);
	}

	void DeferredRenderingStrategy::Render(const Camera& camera, std::function<void()> fRenderModels) {
		RenderPassDeferred0* pRenderPass0 = dynamic_cast<RenderPassDeferred0*>(GetRenderPass(0));

		GLint viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );
		glViewport(0, 0, 640, 480);

#define SHADER (*GetCurrentRenderPass())

		RenderBegin(0);
			SHADER.BindViewProj(SHADER_UNIFORM_ENUM::VIEWPROJ, camera);
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LOOK, camera.Dir());
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::CAMERA_POS, camera.GetPosition());
			fRenderModels();
		RenderEnd();

		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

		GLuint nTexScreen[4] = {
			pRenderPass0->m_uGBufferTex[3]   //light
			, pRenderPass0->m_uGBufferTex[1] //normal
			, pRenderPass0->m_uGBufferTex[2] //pos
			, pRenderPass0->m_uGBufferTex[4] //depth
		};

		RenderToScreen(2, nTexScreen, 4);
	}

	void DeferredRenderingStrategy::RenderToScreen(int nRenderPass, GLuint* textures, int num) {
		GLint viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		int sx = viewport[0];
		int sy = viewport[1];
		int sw = viewport[2];
		int sh = viewport[3];

#define SHADER (*GetCurrentRenderPass())

		RenderBegin(nRenderPass);
			GLint max_num = std::min(num, 4);
			for(int i=0; i<max_num; ++i){
				if(textures[i] >= 0){
					int x = sx + sw/2*(i%2);
					int y = sy + sh/2*(i/2);
					int w = sw/2;
					int h = sh/2;
					glViewport(x, y, w, h);
					SHADER.BindTexture(SHADER_UNIFORM_ENUM::TEX0, 0, textures[i]);
					m_quad.Render(SHADER);
				}
			}
		RenderEnd();

		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	}
}
