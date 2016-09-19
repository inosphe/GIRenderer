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
	DeferredRenderingStrategy::DeferredRenderingStrategy():IRenderingStrategy(), m_quad(32, 32), m_quad2(64, 64*64){
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
		pGPass->Init("shader/deferred.vert.glsl", nullptr, "shader/rsm.frag.glsl");

		FrameBuffer* pGPassFrameBuffer = new FrameBuffer(4);
		pGPassFrameBuffer->Init();
		pGPass->SetFrameBuffer(pGPassFrameBuffer);

		AddRenderPass(pGPass, RENDER_PASS_ENUM::RSM);

		{
			RenderPass* pLightPass0 = new RenderPass();
			pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_DIFFUSE, "Diffuse", 0);
			pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_POS, "Pos", 1);
			pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, "Normal", 2);
			pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::R0, "Gradient", 3);
			std::vector<std::pair<GLuint, std::string>> vecShader;
			vecShader.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/quad.vert.glsl"));
			vecShader.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/testlighting.frag.glsl"));
			vecShader.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/unpack_pos.glsl"));
			vecShader.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/volume_coord.glsl"));
			pLightPass0->Init(vecShader);
			FrameBuffer* pFB = new FrameBuffer(1);
			pFB->Init();
			pLightPass0->SetFrameBuffer(pFB);
			AddRenderPass(pLightPass0, RENDER_PASS_ENUM::TEST_LIGHTING);
		}

		//LPV injection
		{
			RenderPass* pLightInjectPass = new RenderPass();
			std::vector<std::pair<GLuint, std::string>> vecLightInjectShaders;
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/lpv_inject.vert.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/unpack_pos.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/volume_coord.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/lpv_inject.frag.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/sh_func.glsl"));
			pLightInjectPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_LIGHT, "Light", 0);
			pLightInjectPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_POS, "Pos", 1);
			pLightInjectPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, "Normal", 2);
			pLightInjectPass->Init(vecLightInjectShaders);
			FrameBuffer* pFB = new FrameBuffer(3, size, size*size);
			pFB->Init();
			pLightInjectPass->SetFrameBuffer(pFB);
			AddRenderPass(pLightInjectPass, RENDER_PASS_ENUM::LIGHT_INJECT);
		}

		//LPV propagate
		for(int i=0; i<2; ++i) {
			RenderPass* pPropagatePass = new RenderPass();
			std::vector<std::pair<GLuint, std::string>> vecLightInjectShaders;
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/lpv_propagate.vert.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/lpv_propagate.frag.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/unpack_pos.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/volume_coord.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/sh_func.glsl"));
			pPropagatePass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_VOLUME, "LPV", 0);
			pPropagatePass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_POS, "Pos", 2);
			pPropagatePass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::R0, "Gradient", 3);
			pPropagatePass->Init(vecLightInjectShaders);
			FrameBuffer* pFB = new FrameBuffer(3, size, size*size);
			pFB->Init();
			pPropagatePass->SetFrameBuffer(pFB);
			AddRenderPass(pPropagatePass, RENDER_PASS_ENUM::LIGHT_PROPAGATE+i);
		}

		{
			RenderPass* pRenderPass= new RenderPass();
			std::vector<std::pair<GLuint, std::string>> vecLightInjectShaders;
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/quad.vert.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/quad_test.frag.glsl"));
			pRenderPass->Init(vecLightInjectShaders);
			FrameBuffer* pFB = new FrameBuffer(1);
			pFB->Init();
			pRenderPass->SetFrameBuffer(pFB);
			AddRenderPass(pRenderPass, RENDER_PASS_ENUM::QUAD_TEST);
		}


		RenderPass* pScreenPass = new RenderPass();
		pScreenPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX0, "Tex0");
		pScreenPass->Init("shader/quad.vert.glsl", nullptr, "shader/quad.frag.glsl");
		AddRenderPass(pScreenPass, RENDER_PASS_ENUM::RENDER_TO_SCREEN);
	}

	void DeferredRenderingStrategy::Render(const Camera& camera, std::function<void()> fRenderModels) {
		RenderPassDeferred0* pRenderPass0 = dynamic_cast<RenderPassDeferred0*>(GetRenderPass(0));
		FrameBuffer* pGPassFrameBuffer = pRenderPass0->GetFrameBuffer();

		GLint viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );
		glViewport(0, 0, 640, 480);

#define SHADER (*GetCurrentRenderPass())

		RenderBegin(RENDER_PASS_ENUM::RSM);
			SHADER.BindViewProj(SHADER_UNIFORM_ENUM::VIEWPROJ, camera);
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LOOK, camera.Dir());
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::CAMERA_POS, camera.GetPosition());
			fRenderModels();
		RenderEnd();

		GLuint tex_gradient[] = {tex_r->GetID(), tex_g->GetID(), tex_b->GetID()};

		RenderBegin(RENDER_PASS_ENUM::TEST_LIGHTING);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, pGPassFrameBuffer->m_uTextures[1]);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_POS, pGPassFrameBuffer->m_uTextures[2]);
			SHADER.BindTextures(SHADER_UNIFORM_ENUM::R0, tex_gradient, 3);
			m_quad.Render(SHADER);
		RenderEnd();

		RenderBegin(RENDER_PASS_ENUM::LIGHT_INJECT);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_LIGHT, pGPassFrameBuffer->m_uTextures[3]);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, pGPassFrameBuffer->m_uTextures[1]);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_POS, pGPassFrameBuffer->m_uTextures[2]);

//			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			m_quad2.Render(SHADER);
//			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		RenderEnd();


		RenderPass* pLightInjectPass = GetRenderPass(RENDER_PASS_ENUM::LIGHT_INJECT);
		FrameBuffer* pLightInjectFB = pLightInjectPass->GetFrameBuffer();
		GLuint tex_light_propagate_lpv[] = {
				pLightInjectFB->m_uTextures[0]
				, pLightInjectFB->m_uTextures[1]
				, pLightInjectFB->m_uTextures[2]
		};
		for(int i=0; i<2; ++i){
			RenderBegin(RENDER_PASS_ENUM::LIGHT_PROPAGATE+i);
				SHADER.BindTextures(SHADER_UNIFORM_ENUM::LIGHT_VOLUME, tex_light_propagate_lpv, 3);
				SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_POS, pGPassFrameBuffer->m_uTextures[2]);
				SHADER.BindTextures(SHADER_UNIFORM_ENUM::R0, tex_gradient, 3);

				m_quad2.Render(SHADER);
			RenderEnd();

			for(int j=0; j<3; ++j){
				tex_light_propagate_lpv[j] = GetRenderPass(RENDER_PASS_ENUM::LIGHT_PROPAGATE+i)->GetFrameBuffer()->m_uTextures[j];
			}
		}


		RenderBegin(RENDER_PASS_ENUM::QUAD_TEST);
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			m_quad.Render(SHADER);
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		RenderEnd();

		std::vector<GLuint> vecTextures;
		vecTextures.push_back(pGPassFrameBuffer->m_uTextures[3]); //light
		vecTextures.push_back(pGPassFrameBuffer->m_uTextures[1]); //normal
		vecTextures.push_back(pGPassFrameBuffer->m_uTextures[2]); //pos
		for(int i=0; i<3; ++i){
			vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::LIGHT_INJECT)->GetFrameBuffer()->m_uTextures[i]);
//			vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::LIGHT_PROPAGATE)->GetFrameBuffer()->m_uTextures[i]);
			vecTextures.push_back(tex_light_propagate_lpv[i]);
		}
		vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::TEST_LIGHTING)->GetFrameBuffer()->m_uTextures[0]); //depth
//		vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::QUAD_TEST)->GetFrameBuffer()->m_uTextures[0]); //depth
		vecTextures.push_back(tex_r->GetID());
		vecTextures.push_back(tex_g->GetID());
		vecTextures.push_back(tex_b->GetID());

		RenderToScreen(viewport, RENDER_PASS_ENUM::RENDER_TO_SCREEN, 3, vecTextures);

		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

	}

	void DeferredRenderingStrategy::RenderToScreen(GLint viewport[4], int nRenderPass, int split_h, const GLuint* textures, int num) {
		int sx = viewport[0];
		int sy = viewport[1];
		int sw = viewport[2];
		int sh = viewport[3];

		int num_w = num/static_cast<float>(split_h)+0.5f;

		RenderBegin(nRenderPass);
			for(int i=0; i<num; ++i){
				int x = sx + sw/num_w * (i%num_w);
				int y = sy + sh/split_h*(i/num_w);
				int w = sw/num_w;
				int h = sh/split_h;
				glViewport(x, y, w, h);
				SHADER.BindTexture(SHADER_UNIFORM_ENUM::TEX0, textures[i]);
				m_quad.Render(SHADER);
			}
		RenderEnd();

	}

	void DeferredRenderingStrategy::RenderToScreen(GLint viewport[4], int nRenderPass, int split_h, const std::vector<GLuint>& vecTextures) {
		RenderToScreen(viewport, nRenderPass, split_h, &vecTextures[0], vecTextures.size());
	}
}
