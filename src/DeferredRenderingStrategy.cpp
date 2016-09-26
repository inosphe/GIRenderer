//
// Created by inosphe on 2016. 3. 28..
//

#include "DeferredRenderingStrategy.h"
#include <cassert>
#include "util/GLUtil.h"
#include "Exception.h"
#include "RenderPassDeferred0.h"
#include "Light.h"

#define SHADER (*GetCurrentRenderPass())

namespace Render{
	DeferredRenderingStrategy::DeferredRenderingStrategy()
	:IRenderingStrategy()
	, m_quad(1, 1, 640, 480, 0.0f, false)
	, m_quad2(lpv_size, lpv_size*lpv_size, lpv_size, lpv_size*lpv_size, 0.0f, true)
	{
	}

	DeferredRenderingStrategy::~DeferredRenderingStrategy() {
		SAFE_DELETE(tex_r);
		SAFE_DELETE(tex_g);
		SAFE_DELETE(tex_b);
		SAFE_DELETE(m_pFrameBuffer);
	}

	void DeferredRenderingStrategy::Init() {
		IRenderingStrategy::Init();

		tex_r = new DummyGradientTexture(lpv_size, 0);
		tex_g = new DummyGradientTexture(lpv_size, 1);
		tex_b = new DummyGradientTexture(lpv_size, 2);

		m_pFrameBuffer = new FrameBuffer(1);
		m_pFrameBuffer->Init();

		//Main Gbuffer
		{
			RenderPassDeferred0* pGPass = new RenderPassDeferred0();
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::VIEWPROJ, "ViewProjection");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TRANSFORM, "ObjectTransform");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX0, "Tex0", 0);
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::CAMERA_POS, "CameraPos");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LOOK, "Look");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_POS, "light_pos");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_DIR, "light_dir");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_INTENSITY, "light_intensity");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::SHADOW_VIEWPROJ, "ShadowViewProj");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::USE_SHADOW, "use_shadow");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::SHADOW_MAP, "ShadowMap", 8);
			std::vector<std::pair<GLuint, std::string>> vecShaders;
			vecShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/deferred.vert.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/rsm.frag.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/unpack_pos.glsl"));
			pGPass->Init(vecShaders);

			FrameBuffer* pGPassFrameBuffer = new FrameBuffer(4);
			pGPassFrameBuffer->Init();
			pGPass->SetFrameBuffer(std::shared_ptr<FrameBuffer>(pGPassFrameBuffer), 0);

			AddRenderPass(pGPass, RENDER_PASS_ENUM::MAIN_GBUFFER);
		}

		//Light Gbuffer
		{
			RenderPassDeferred0* pGPass = new RenderPassDeferred0();
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::VIEWPROJ, "ViewProjection");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TRANSFORM, "ObjectTransform");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX0, "Tex0", 0);
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::CAMERA_POS, "CameraPos");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LOOK, "Look");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_POS, "light_pos");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_DIR, "light_dir");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_INTENSITY, "light_intensity");
			pGPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::USE_SHADOW, "use_shadow");
			std::vector<std::pair<GLuint, std::string>> vecShaders;
			vecShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/deferred.vert.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/rsm.frag.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/unpack_pos.glsl"));
			pGPass->Init(vecShaders);

			for(int i=0; i<1; ++i){
				FrameBuffer* pGPassFrameBuffer = new FrameBuffer(4);
				pGPassFrameBuffer->Init();
				pGPass->SetFrameBuffer(std::shared_ptr<FrameBuffer>(pGPassFrameBuffer), i);
			}
			AddRenderPass(pGPass, RENDER_PASS_ENUM::LIGHT_GBUFFER);
		}

		{
			RenderPass* pRenderPass= new RenderPass();
			std::vector<std::pair<GLuint, std::string>> vecShaders;
			vecShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/quad.vert.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/quad.frag.glsl"));
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX0, "Tex0", 0);
			pRenderPass->Init(vecShaders);
			FrameBuffer* pFB = new FrameBuffer(1, lpv_size, lpv_size*lpv_size);
			pFB->Init();
			pRenderPass->SetFrameBuffer(std::shared_ptr<FrameBuffer>(pFB), 0);
			AddRenderPass(pRenderPass, RENDER_PASS_ENUM::DOWNSAMPLE_GBUFFER);
		}

		{
			RenderPass* pLightPass0 = new RenderPass();
			pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_DIFFUSE, "Diffuse", 0);
			pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_POS, "Pos", 1);
			pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, "Normal", 2);
			pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LPV_SIZE, "lpv_size");
			pLightPass0->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LPV_CELL_SIZE, "lpv_cellsize");
			std::vector<std::pair<GLuint, std::string>> vecShader;
			vecShader.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/quad.vert.glsl"));
			vecShader.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/testlighting.frag.glsl"));
			vecShader.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/unpack_pos.glsl"));
			vecShader.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/volume_coord.glsl"));
			pLightPass0->Init(vecShader);
			pLightPass0->BindProgram();
			pLightPass0->BindInt(SHADER_UNIFORM_ENUM::LPV_SIZE, lpv_size);
			pLightPass0->BindInt(SHADER_UNIFORM_ENUM::LPV_CELL_SIZE, lpv_cellsize);
			FrameBuffer* pFB = new FrameBuffer(1);
			pFB->Init();
			pLightPass0->SetFrameBuffer(std::shared_ptr<FrameBuffer>(pFB), 0);
			AddRenderPass(pLightPass0, RENDER_PASS_ENUM::TEST_LIGHTING);
		}

		//test lighting2
		{
			RenderPass* pPass = new RenderPass();
			std::vector<std::pair<GLuint, std::string>> vecLightInjectShaders;
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/lpv_inject.vert.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/unpack_pos.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/volume_coord.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/testlighting2.frag.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/sh_func.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/unpack_pos.glsl"));
			pPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_LIGHT, "Light", 0);
			pPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_POS, "Pos", 1);
			pPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, "Normal", 2);
			pPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LPV_SIZE, "lpv_size");
			pPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LPV_CELL_SIZE, "lpv_cellsize");
			pPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::R0, "Gradient", 3);
			pPass->Init(vecLightInjectShaders);
			pPass->BindProgram();
			pPass->BindInt(SHADER_UNIFORM_ENUM::LPV_SIZE, lpv_size);
			pPass->BindInt(SHADER_UNIFORM_ENUM::LPV_CELL_SIZE, lpv_cellsize);
			FrameBuffer* pFB = new FrameBuffer(3, lpv_size, lpv_size*lpv_size);
			pFB->Init();
			pFB->m_color[0] = 0.5f;
			pFB->m_color[1] = 0.5f;
			pFB->m_color[2] = 0.5f;
			pFB->m_color[3] = 0.5f;
			pPass->SetFrameBuffer(std::shared_ptr<FrameBuffer>(pFB), 0);
			AddRenderPass(pPass, RENDER_PASS_ENUM::TEST_LIGHTING2);
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
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/unpack_pos.glsl"));
			pLightInjectPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_LIGHT, "Light", 0);
			pLightInjectPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_POS, "Pos", 1);
			pLightInjectPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, "Normal", 2);
			pLightInjectPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LPV_SIZE, "lpv_size");
			pLightInjectPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LPV_CELL_SIZE, "lpv_cellsize");
			pLightInjectPass->Init(vecLightInjectShaders);
			pLightInjectPass->BindProgram();
			pLightInjectPass->BindInt(SHADER_UNIFORM_ENUM::LPV_SIZE, lpv_size);
			pLightInjectPass->BindInt(SHADER_UNIFORM_ENUM::LPV_CELL_SIZE, lpv_cellsize);

			for(int i=0; i<2; ++i){
				FrameBuffer* pFB = new FrameBuffer(3, lpv_size, lpv_size*lpv_size);
				pFB->Init();
				pFB->m_color[0] = 0.5f;
				pFB->m_color[1] = 0.5f;
				pFB->m_color[2] = 0.5f;
				pFB->m_color[3] = 0.5f;
				pLightInjectPass->SetFrameBuffer(std::shared_ptr<FrameBuffer>(pFB), i);
			}
			AddRenderPass(pLightInjectPass, RENDER_PASS_ENUM::LIGHT_INJECT);
		}

		//LPV propagate
		{
			RenderPass* pPropagatePass = new RenderPass();
			std::vector<std::pair<GLuint, std::string>> vecLightInjectShaders;
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/lpv_propagate.vert.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/unpack_pos.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/lpv_propagate.frag.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/unpack_pos.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/volume_coord.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/sh_func.glsl"));
			pPropagatePass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_VOLUME, "LPV", 0);
			pPropagatePass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_POS, "Pos", 3);
			pPropagatePass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LPV_SIZE, "lpv_size");
			pPropagatePass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LPV_CELL_SIZE, "lpv_cellsize");
			pPropagatePass->Init(vecLightInjectShaders);
			pPropagatePass->BindProgram();
			pPropagatePass->BindInt(SHADER_UNIFORM_ENUM::LPV_SIZE, lpv_size);
			pPropagatePass->BindInt(SHADER_UNIFORM_ENUM::LPV_CELL_SIZE, lpv_cellsize);
			for(int i=0; i<2; ++i){
				pPropagatePass->SetFrameBuffer(GetRenderPass(RENDER_PASS_ENUM::LIGHT_INJECT)->GetFrameBuffer(i), i);
			}
			AddRenderPass(pPropagatePass, RENDER_PASS_ENUM::LIGHT_PROPAGATE);
		}

		{
			RenderPass* pRenderPass= new RenderPass();
			std::vector<std::pair<GLuint, std::string>> vecLightInjectShaders;
			vecLightInjectShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/quad.vert.glsl"));
			vecLightInjectShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/quad_test.frag.glsl"));
			pRenderPass->Init(vecLightInjectShaders);
			FrameBuffer* pFB = new FrameBuffer(1, lpv_size, lpv_size*lpv_size);
			pFB->Init();
			pRenderPass->SetFrameBuffer(std::shared_ptr<FrameBuffer>(pFB), 0);
			AddRenderPass(pRenderPass, RENDER_PASS_ENUM::QUAD_TEST);
		}

		{
			RenderPass* pRenderPass= new RenderPass();
			std::vector<std::pair<GLuint, std::string>> vecShaders;
			vecShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/quad.vert.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/quad_add3.frag.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/unpack_pos.glsl"));
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX0, "Tex_src");
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX1, "Tex_dst", 3);
			pRenderPass->Init(vecShaders);
			for(int i=0; i<2; ++i){
				FrameBuffer* pFB = new FrameBuffer(3, lpv_size, lpv_size*lpv_size);
				pFB->SetClearColor(0.5f, 0.5f, 0.5f, 0.5f);
				pFB->Init();
				pRenderPass->SetFrameBuffer(std::shared_ptr<FrameBuffer>(pFB), i);
			}
//			pRenderPass->SetFrameBuffer(GetRenderPass(RENDER_PASS_ENUM::LIGHT_INJECT)->GetFrameBuffer());
			AddRenderPass(pRenderPass, RENDER_PASS_ENUM::ACCUM_LPV);
		}

		{
			RenderPass* pRenderPass= new RenderPass();
			std::vector<std::pair<GLuint, std::string>> vecShaders;
			vecShaders.push_back(std::make_pair(GL_VERTEX_SHADER, "shader/quad.vert.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/post_lpv.frag.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/volume_coord.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/unpack_pos.glsl"));
			vecShaders.push_back(std::make_pair(GL_FRAGMENT_SHADER, "shader/sh_func.glsl"));
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_LIGHT, "Light", 0);
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_DIFFUSE, "Diffuse", 1);
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_POS, "Pos", 2);
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, "Normal", 3);
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_VOLUME, "LPV", 4);
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LPV_SIZE, "lpv_size");
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LPV_CELL_SIZE, "lpv_cellsize");
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_POS, "light_pos");
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_DIR, "light_dir");
			pRenderPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::LIGHT_INTENSITY, "light_intensity");
			pRenderPass->Init(vecShaders);
			pRenderPass->BindProgram();
			pRenderPass->BindInt(SHADER_UNIFORM_ENUM::LPV_SIZE, lpv_size);
			pRenderPass->BindInt(SHADER_UNIFORM_ENUM::LPV_CELL_SIZE, lpv_cellsize);
			AddRenderPass(pRenderPass, RENDER_PASS_ENUM::POST_LPV);
		}

		RenderPass* pScreenPass = new RenderPass();
		pScreenPass->AddShaderUnfiorm(SHADER_UNIFORM_ENUM::TEX0, "Tex0");
		pScreenPass->Init("shader/quad.vert.glsl", nullptr, "shader/quad.frag.glsl");
		AddRenderPass(pScreenPass, RENDER_PASS_ENUM::RENDER_TO_SCREEN);
	}

	void DeferredRenderingStrategy::Render(const Camera& camera, const std::vector<GameObject::PTR>& vecLights, std::function<void()> fRenderModels) {
		glDisable(GL_BLEND);
		//glDepthRange(0.0, 1024.0);

		GLint viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		RenderGStage(camera, vecLights, fRenderModels);
		for(auto light : vecLights){
			LPVInject(dynamic_cast<Light*>(light.get()), fRenderModels);
		}
		const int iteration = 2;
		LPVPropagate(iteration);
		LPVFinal(m_bDebugMode?m_pFrameBuffer: nullptr, vecLights);

		//__QuadTest();
		__CoordTest();

		glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

		if(m_bDebugMode && m_pFrameBuffer)
			RenderScreen();

		std::vector<GLuint> vecTextures;
		GLint viewport2[4] = {500, 0, lpv_size, lpv_size*lpv_size};
		vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::QUAD_TEST)->GetFrameBuffer(0)->m_uTextures[0]);
		//RenderTexToScreen(viewport2, RENDER_PASS_ENUM::RENDER_TO_SCREEN, 1, vecTextures);

	}

	void DeferredRenderingStrategy::RenderTexToScreen(GLint viewport[4], int nRenderPass, int split_h, const GLuint* textures, int num) {
		int sx = viewport[0];
		int sy = viewport[1];
		int sw = viewport[2];
		int sh = viewport[3];

		int num_w = num/static_cast<float>(split_h)+0.9f;

		RenderBegin(nRenderPass, 0, true);
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

	void DeferredRenderingStrategy::RenderTexToScreen(GLint viewport[4], int nRenderPass, int split_h, const std::vector<GLuint>& vecTextures) {
		RenderTexToScreen(viewport, nRenderPass, split_h, &vecTextures[0], vecTextures.size());
	}

	void DeferredRenderingStrategy::Clear() {
//		GetRenderPass(RENDER_PASS_ENUM::ACCUM_LPV)->SetFrameBuffer(GetRenderPass(RENDER_PASS_ENUM::LIGHT_INJECT)->GetFrameBuffer());

		IRenderingStrategy::Clear();
	}

	void DeferredRenderingStrategy::LPVInject(Light* pLight, std::function<void()> fRenderModels) {
		FrameBuffer* pLightGStageFB = GetRenderPass(RENDER_PASS_ENUM::LIGHT_GBUFFER)->GetFrameBuffer(0).get();

		GLuint texGDiffuse = pLightGStageFB->m_uTextures[0];
		GLuint texGNormal = pLightGStageFB->m_uTextures[1];
		GLuint texGPos = pLightGStageFB->m_uTextures[2];
		GLuint texGLight = pLightGStageFB->m_uTextures[3];

		RenderBegin(RENDER_PASS_ENUM::LIGHT_GBUFFER, 0, true);
			SHADER.BindViewProj(SHADER_UNIFORM_ENUM::VIEWPROJ, *pLight);
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LOOK, pLight->Dir(), true);
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::CAMERA_POS, pLight->GetPosition(), false);
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LIGHT_POS, pLight->GetPosition(), false);
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LIGHT_DIR, pLight->Dir(), true);
			SHADER.BindFloat(SHADER_UNIFORM_ENUM::LIGHT_INTENSITY, pLight->GetIntensity());
			SHADER.BindInt(SHADER_UNIFORM_ENUM::USE_SHADOW, 0);
			fRenderModels();
		RenderEnd();

		RenderBegin(RENDER_PASS_ENUM::LIGHT_INJECT, 0, true);
			//glDisable(GL_DEPTH_TEST);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_LIGHT, texGLight);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, texGNormal);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_POS, texGPos);
			m_quad2.Render(SHADER);
			//glEnable(GL_DEPTH_TEST);
		RenderEnd();

		RenderBegin(RENDER_PASS_ENUM::TEST_LIGHTING2, 0, true);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_LIGHT, texGLight);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, texGNormal);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_POS, texGPos);
			GLuint tex[] = {tex_r->GetID(), tex_g->GetID(), tex_b->GetID()};
			SHADER.BindTextures(SHADER_UNIFORM_ENUM::R0, tex, 3);
			m_quad2.Render(SHADER);
		RenderEnd();
	}

	void DeferredRenderingStrategy::LPVPropagate(int iteration) {
		FrameBuffer* pLightInjectFB = GetRenderPass(RENDER_PASS_ENUM::LIGHT_INJECT)->GetFrameBuffer(0).get();
		FrameBuffer* pLPVPropagateFB = GetRenderPass(RENDER_PASS_ENUM::LIGHT_PROPAGATE)->GetFrameBuffer(0).get();

		/*
		GLuint texLPVPropagate[] = {
				pLightInjectFB->m_uTextures[0]
				, pLightInjectFB->m_uTextures[1]
				, pLightInjectFB->m_uTextures[2]
		};
		 */

		GLuint texLPVPropagate[] = {
				pLPVPropagateFB->m_uTextures[0]
				, pLPVPropagateFB->m_uTextures[1]
				, pLPVPropagateFB->m_uTextures[2]
		};

		//just for clear
//		GetRenderPass(RENDER_PASS_ENUM::ACCUM_LPV)->GetFrameBuffer(1)->RenderBegin(true);
//		GetRenderPass(RENDER_PASS_ENUM::ACCUM_LPV)->GetFrameBuffer(1)->RenderEnd();

		GetRenderPass(RENDER_PASS_ENUM::LIGHT_PROPAGATE)->UseFrameBuffer(0);
		for(int i=1; i<iteration; ++i){
			RenderBegin(RENDER_PASS_ENUM::LIGHT_PROPAGATE, i%2, false);
				SHADER.BindTextures(SHADER_UNIFORM_ENUM::LIGHT_VOLUME, texLPVPropagate, 3);
				m_quad.Render(SHADER);
			RenderEnd();

			for(int j=0; j<3; ++j){
				texLPVPropagate[j] = GetRenderPass(RENDER_PASS_ENUM::LIGHT_PROPAGATE)->GetFrameBuffer(i%2)->m_uTextures[j];
			}

			/*
			FrameBuffer* pLPVAcuumNextFB = GetRenderPass(RENDER_PASS_ENUM::ACCUM_LPV)->GetFrameBuffer((i+1)%2).get();
			RenderBegin(RENDER_PASS_ENUM::ACCUM_LPV, i%2, i==0);
				if(i==0)
					SHADER.BindTextures(SHADER_UNIFORM_ENUM::TEX0, GetRenderPass(RENDER_PASS_ENUM::LIGHT_INJECT)->GetFrameBuffer(0)->m_uTextures, 3);
				else
					SHADER.BindTextures(SHADER_UNIFORM_ENUM::TEX0, pLPVAcuumNextFB->m_uTextures, 3);
				SHADER.BindTextures(SHADER_UNIFORM_ENUM::TEX1, texLPVPropagate, 3);
				m_quad.Render(SHADER);
			RenderEnd();
			*/
		}
	}

	void DeferredRenderingStrategy::__QuadTest() {
		RenderBegin(RENDER_PASS_ENUM::QUAD_TEST, 0, true);
//			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			m_quad2.Render(SHADER);
//			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		RenderEnd();
	}

	void DeferredRenderingStrategy::LPVFinal(FrameBuffer* pFrameBuffer, const std::vector<GameObject::PTR>& vecLights) {
		const unsigned long MAX_LIGHT_COUNT = 1;
		FrameBuffer* pGStageFB = GetRenderPass(RENDER_PASS_ENUM::MAIN_GBUFFER)->GetFrameBuffer(0).get();

		RenderBegin(RENDER_PASS_ENUM::POST_LPV, pFrameBuffer, true);

			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_LIGHT, pGStageFB->m_uTextures[3]);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_DIFFUSE, pGStageFB->m_uTextures[0]);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_POS, pGStageFB->m_uTextures[2]);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, pGStageFB->m_uTextures[1]);
//			SHADER.BindTextures(SHADER_UNIFORM_ENUM::LIGHT_VOLUME, GetRenderPass(RENDER_PASS_ENUM::ACCUM_LPV)->GetCurFrameBuffer()->m_uTextures, 3);
			SHADER.BindTextures(SHADER_UNIFORM_ENUM::LIGHT_VOLUME, GetRenderPass(RENDER_PASS_ENUM::LIGHT_PROPAGATE)->GetCurFrameBuffer()->m_uTextures, 3);
//			SHADER.BindTextures(SHADER_UNIFORM_ENUM::LIGHT_VOLUME, GetRenderPass(RENDER_PASS_ENUM::LIGHT_INJECT)->GetFrameBuffer(0)->m_uTextures, 3);
			for(int i=0; i<std::min(vecLights.size(), MAX_LIGHT_COUNT); ++i){
				Light& light = *dynamic_cast<Light*>(vecLights[i].get());
				SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LIGHT_POS, light.GetPosition(), false);
				SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LIGHT_DIR, light.Dir(), true);
				SHADER.BindFloat(SHADER_UNIFORM_ENUM::LIGHT_INTENSITY, light.GetIntensity());
			}
			m_quad.Render(SHADER);
		RenderEnd();
	}

	void DeferredRenderingStrategy::__CoordTest() {
		GLuint tex_gradient[] = {tex_r->GetID(), tex_g->GetID(), tex_b->GetID()};
		FrameBuffer* pGStageFB = GetRenderPass(RENDER_PASS_ENUM::MAIN_GBUFFER)->GetFrameBuffer(0).get();


		RenderBegin(RENDER_PASS_ENUM::TEST_LIGHTING, 0, true);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_NORMAL, pGStageFB->m_uTextures[1]);
			SHADER.BindTexture(SHADER_UNIFORM_ENUM::GBUFFER_POS, pGStageFB->m_uTextures[2]);
			SHADER.BindTextures(SHADER_UNIFORM_ENUM::R0, tex_gradient, 3);
			m_quad.Render(SHADER);
		RenderEnd();
	}

	void DeferredRenderingStrategy::RenderScreen() {
		FrameBuffer* pGStageFB = GetRenderPass(RENDER_PASS_ENUM::MAIN_GBUFFER)->GetFrameBuffer(0).get();
		FrameBuffer* pLightGStageFB = GetRenderPass(RENDER_PASS_ENUM::LIGHT_GBUFFER)->GetFrameBuffer(0).get();

		GLint viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		std::vector<GLuint> vecTextures;
		vecTextures.push_back(m_pFrameBuffer->m_uTextures[0]);

//		vecTextures.push_back(pGStageFB->m_uTextures[0]); //diffuse
		vecTextures.push_back(pGStageFB->m_uTextures[1]); //normal
//		vecTextures.push_back(pGStageFB->m_uTextures[2]); //pos
		vecTextures.push_back(pGStageFB->m_uTextures[3]);
//		vecTextures.push_back(pGStageFB->m_uDepthMap);
		for(int i=0; i<3; ++i){
//			vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::LIGHT_INJECT)->GetCurFrameBuffer()->m_uTextures[i]);
			vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::LIGHT_PROPAGATE)->GetFrameBuffer(0)->m_uTextures[i]);
//			vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::ACCUM_LPV)->GetFrameBuffer(0)->m_uTextures[i]);
			vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::LIGHT_PROPAGATE)->GetFrameBuffer(1)->m_uTextures[i]);
//			vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::ACCUM_LPV)->GetFrameBuffer(1)->m_uTextures[i]);
//			vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::ACCUM_LPV)->GetCurFrameBuffer()->m_uTextures[i]);
		}
		//vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::QUAD_TEST)->GetFrameBuffer(0)->m_uTextures[0]);
//		vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::TEST_LIGHTING)->GetFrameBuffer(0)->m_uTextures[0]); //depth
		GLuint tex_gradient[] = {tex_r->GetID(), tex_g->GetID(), tex_b->GetID()};
//		for(int i=0; i<3; ++i){
//			vecTextures.push_back(GetRenderPass(RENDER_PASS_ENUM::TEST_LIGHTING2)->GetFrameBuffer(0)->m_uTextures[i]); //depth
//			vecTextures.push_back(tex_gradient[i]); //depth
//		}

//		vecTextures.push_back(pLightGStageFB->m_uTextures[0]);
		vecTextures.push_back(pLightGStageFB->m_uTextures[1]);
//		vecTextures.push_back(pLightGStageFB->m_uTextures[2]);
		vecTextures.push_back(pLightGStageFB->m_uTextures[3]);
//		vecTextures.push_back(pLightGStageFB->m_uDepthMap);

		RenderTexToScreen(viewport, RENDER_PASS_ENUM::RENDER_TO_SCREEN, 3, vecTextures);
	}

	void DeferredRenderingStrategy::RenderGStage(const Camera& camera, const std::vector<GameObject::PTR>& vecLights, std::function<void()> fRenderModels) {
		const unsigned long MAX_LIGHT_COUNT = 1;

		RenderBegin(RENDER_PASS_ENUM::MAIN_GBUFFER, 0, true);
			SHADER.BindViewProj(SHADER_UNIFORM_ENUM::VIEWPROJ, camera);
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LOOK, camera.Dir(), true);
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::CAMERA_POS, camera.GetPosition(), false);
			for(int i=0; i<std::min(vecLights.size(), MAX_LIGHT_COUNT); ++i){
				Light& light = *dynamic_cast<Light*>(vecLights[i].get());
				SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LIGHT_POS, light.GetPosition(), false);
				SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LIGHT_DIR, light.Dir(), true);
				SHADER.BindFloat(SHADER_UNIFORM_ENUM::LIGHT_INTENSITY, light.GetIntensity());
				SHADER.BindViewProj(SHADER_UNIFORM_ENUM::SHADOW_VIEWPROJ, light);
				SHADER.BindInt(SHADER_UNIFORM_ENUM::USE_SHADOW, 1);
				SHADER.BindTexture(SHADER_UNIFORM_ENUM::SHADOW_MAP, GetRenderPass(LIGHT_GBUFFER)->GetFrameBuffer(0)->m_uDepthMap);
			}
			fRenderModels();
		RenderEnd();
	}
}
