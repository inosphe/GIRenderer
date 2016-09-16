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
		SAFE_DELETE(tex_r);
		SAFE_DELETE(tex_g);
		SAFE_DELETE(tex_b);
	}

	void DeferredRenderingStrategy::Init() {
		IRenderingStrategy::Init();

		tex_r = new DummyGradientTexture(0);
		tex_g = new DummyGradientTexture(1);
		tex_b = new DummyGradientTexture(2);

		RenderPassDeferred0* pGPass = new RenderPassDeferred0();
		pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::VIEWPROJ, "ViewProjection");
		pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TRANSFORM, "ObjectTransform");
		pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX0, "Tex0");
		pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::CAMERA_POS, "CameraPos");
		pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LOOK, "Look");
		pGPass->Init("shader/deferred.vert.glsl", "shader/rsm.frag.glsl");

		FrameBuffer* pGPassFrameBuffer = new FrameBuffer(4);
		pGPassFrameBuffer->Init();
		pGPass->SetFrameBuffer(pGPassFrameBuffer);

		AddRenderPass(pGPass, 0);

		RenderPass* pLightPass0 = new RenderPass();
		pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_DIFFUSE, "Diffuse", 0);
		pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_POS, "Pos", 1);
		pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, "Normal", 2);
		pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_VOLUME_R, "LV_R", 3);
		pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_VOLUME_G, "LV_G", 4);
		pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_VOLUME_B, "LV_B", 5);
		pLightPass0->Init("shader/quad.vert.glsl", "shader/testlighting.frag.glsl");
		AddRenderPass(pLightPass0, 1);

		FrameBuffer* pLVFrameBuffer = new FrameBuffer(1);
		pLVFrameBuffer->Init();
		pLightPass0->SetFrameBuffer(pLVFrameBuffer);

		RenderPass* pScreenPass = new RenderPass();
		pScreenPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX0, "Tex0");
		pScreenPass->Init("shader/quad.vert.glsl", "shader/quad.frag.glsl");
		AddRenderPass(pScreenPass, 2);
	}

	void DeferredRenderingStrategy::Render(const Camera& camera, std::function<void()> fRenderModels) {
		RenderPassDeferred0* pRenderPass0 = dynamic_cast<RenderPassDeferred0*>(GetRenderPass(0));
		FrameBuffer* pGPassFrameBuffer = pRenderPass0->GetFrameBuffer();

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

		RenderBegin(1);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_DIFFUSE, pGPassFrameBuffer->m_uTextures[0]);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, pGPassFrameBuffer->m_uTextures[1]);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_POS, pGPassFrameBuffer->m_uTextures[2]);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::LIGHT_VOLUME_R, tex_r->GetID());
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::LIGHT_VOLUME_G, tex_g->GetID());
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::LIGHT_VOLUME_B, tex_b->GetID());
			m_quad.Render(SHADER);
		RenderEnd();


		GLuint nTexScreen[4] = {
			pGPassFrameBuffer->m_uTextures[3]   //light
			, pGPassFrameBuffer->m_uTextures[1] //normal
			, pGPassFrameBuffer->m_uTextures[2] //pos
//			tex_r->GetID(), tex_g->GetID(), tex_b->GetID()
			, GetRenderPass(1)->GetFrameBuffer()->m_uTextures[0] //depth
		};


		RenderToScreen(viewport, 2, nTexScreen, 4);

//		GLint viewport2[4] = {viewport[0]+viewport[2]/2, viewport[1], viewport[2]/2, viewport[3]/2};
//		GLuint nTexScreen2[4] = {tex_r->GetID(), tex_g->GetID(), tex_b->GetID(), 0};
//		RenderToScreen(viewport2, 2, nTexScreen2, 4);

		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	}

	void DeferredRenderingStrategy::RenderToScreen(GLint viewport[4], int nRenderPass, GLuint* textures, int num) {
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
					SHADER.BindTexture(SHADER_UNIFORM_ENUM::TEX0, textures[i]);
					m_quad.Render(SHADER);
				}
			}
		RenderEnd();
	}
}
