//
// Created by inosphe on 2016. 3. 28..
//

#include "Renderer.h"
#include "IRenderingStrategy.h"
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "IScene.h"
#include <cassert>
#include "RenderingParameters.h"

namespace Render {
	Renderer::Renderer(){

	}

	Renderer::~Renderer() {

	}

	void Renderer::Init() {

	}

	void Renderer::Clear() {
		if(m_pRenderingStrategy){
			m_pRenderingStrategy->Clear();
		}
	}

	void Renderer::RenderBegin() {
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_pRenderingStrategy->RenderBegin();
		auto shader = m_pRenderingStrategy->GetShader();
		shader.BindCamera(GetTargetCameraRaw());
	}

	void Renderer::RenderEnd() {
		m_pRenderingStrategy->RenderEnd();
	}

	void Renderer::SetCamera(std::shared_ptr<Render::Camera> pCamera) {
		m_pCamera = pCamera;
	}
}


