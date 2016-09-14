//
// Created by inosphe on 2016. 3. 28..
//

#include "Renderer.h"
#include "IRenderingStrategy.h"
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "IScene.h"
#include <cassert>

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

	void Renderer::SetCamera(std::shared_ptr<Render::Camera> pCamera) {
		m_pCamera = pCamera;
	}

	void Renderer::Render(std::function<void()> fRenderModels) {
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_pRenderingStrategy->Render(GetTargetCameraRef(), fRenderModels);
	}
}


