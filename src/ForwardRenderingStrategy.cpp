//
// Created by inosphe on 2016. 3. 28..
//

#include "ForwardRenderingStrategy.h"
#include "util/GLUtil.h"
#include "Exception.h"
#include <cassert>
#include "RenderPass.h"
#include "Camera.h"

namespace Render{
	ForwardRenderingStrategy::ForwardRenderingStrategy()
	:IRenderingStrategy()
	{

	}

	ForwardRenderingStrategy::~ForwardRenderingStrategy() {

	}

	void ForwardRenderingStrategy::Init() {
		IRenderingStrategy::Init();

		RenderPass* pRenderPass = new RenderPass();
		pRenderPass->Init("shader/textured.vert.glsl", nullptr, "shader/textured.frag.glsl");
		AddRenderPass(pRenderPass, 0);
	}

	void ForwardRenderingStrategy::Render(const Camera& camera, const std::vector<GameObject::PTR>& vecLights, std::function<void()> fRenderModels) {
#define SHADER (*GetCurrentRenderPass())

		RenderBegin(0, 0, true);
			SHADER.BindViewProj(SHADER_UNIFORM_ENUM::VIEWPROJ, camera);
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::LOOK, camera.Dir(), true);
			SHADER.BindVec3f(SHADER_UNIFORM_ENUM::CAMERA_POS, camera.GetPosition(), false);
			fRenderModels();
		RenderEnd();
	}
}
