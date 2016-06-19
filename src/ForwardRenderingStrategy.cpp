//
// Created by inosphe on 2016. 3. 28..
//

#include "ForwardRenderingStrategy.h"
#include "util/GLUtil.h"
#include "Exception.h"
#include <cassert>
#include "RenderingParameters.h"
#include "RenderPass.h"

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
		pRenderPass->Init("shader/textured.vert.glsl", "shader/textured.frag.glsl");
		AddRenderPass(pRenderPass, 0);
	}

	void ForwardRenderingStrategy::Render(const Camera& camera, std::function<void()> fRenderModels) {
		RenderBegin(0);
			GetShader().BindCamera(camera);
			fRenderModels();
		RenderEnd();
	}
}
