//
// Created by inosphe on 2016. 3. 28..
//

#include <OpenGL/OpenGL.h>
#include "Application.h"
#include "ResourceManager.h"
#include "TestScene.h"
#include "Renderer.h"
#include "ForwardRenderingStrategy.h"
#include "Logger.h"
#include <OPENGL/glu.h>
#include "IMovableObject.h"
#include <OpenGL/OpenGL.h>
#include "Application.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "ForwardRenderingStrategy.h"
#include "Logger.h"
#include <OPENGL/glu.h>
#include "IMovableObject.h"
#include "util/GLUtil.h"
#include "Camera.h"
#include "Timer.h"
#include "GUI.h"
#include "SceneManager.h"
#include <InputManager.h>

namespace Core {
	Application::Application(GLFWwindow* pWindow)
	:m_pWindow(pWindow)
	{

	}

	bool Application::Initialize() {
		if(!InitResourceManager())
			return false;

		m_pRenderer = new Render::Renderer();
		m_pRenderer->Init();
		m_pRenderer->InitRenderingStrategy<Render::ForwardRenderingStrategy>();

		glFrontFace(GL_CW);
//		glCullFace(GL_;
//		glDisable(GL_CULL_FACE);

		m_pTimer = new Core::Timer();
		m_pTimer->Init();

		m_pGUI = new GUI(m_pWindow);
		m_pGUI->Init();

		m_pInputManager = new InputManager();
		m_pInputManager->Init(m_pWindow);
		m_pInputManager->AddDelegate(this);
		m_pInputManager->AddDelegate(m_pGUI);

		m_pSceneManager = new SceneManager(this);
		m_pSceneManager->Create();
		return true;
	}

	bool Application::InitResourceManager() {
		m_pResourceManager = new Resource::ResourceManager();
		m_pResourceManager->Init();

		return true;
	}

	void Application::Clear() {
		m_pSceneManager->Destroy();
		SAFE_DELETE(m_pSceneManager);

		m_pResourceManager->Clear();
		SAFE_DELETE(m_pResourceManager);
		SAFE_DELETE(m_pTimer);
		m_pInputManager->RemoveDelegate(m_pGUI);
		SAFE_DELETE(m_pGUI);
		m_pInputManager->Clear();
		SAFE_DELETE(m_pInputManager);

		SAFE_DELETE(m_pTimer);
	}

	Application::~Application() {
		Clear();
	}

	void Application::Update() {
		m_pTimer->Update();
		m_pSceneManager->Update(m_pTimer->GetDelta());

		GLUtil::CheckError();

		int state = glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_RIGHT);
		static double x,y;
		double _x = x, _y = y;
		glfwGetCursorPos(m_pWindow, &x, &y);
		if (state == GLFW_PRESS){
			m_pMoveTarget->Rotate((x-_x)/100.0f, (y-_y)/100.0f);
		}
		else{
			m_pInputManager->OnMousePos(x, y);
		}
	}

	void Application::Render() {
		m_pRenderer->RenderBegin();
		m_pSceneManager->Render(m_pRenderer->GetRenderingParameters());
		m_pRenderer->RenderEnd();



		if(m_state.bRenderGUI)
			m_pGUI->Render();

		glfwSwapBuffers(m_pWindow);
	}

	void Application::SetCamera(std::shared_ptr<Render::Camera> pCamera) {
		m_pRenderer->SetCamera(pCamera);
		m_pMoveTarget = pCamera.get();
	}

	bool Application::OnKeyPress(int key, int scancode, int mods) {
		switch(key){
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(m_pWindow, GL_TRUE);
				return true;
			case GLFW_KEY_T:
				this->m_state.bRenderGUI=!this->m_state.bRenderGUI;
				return true;
			case GLFW_KEY_W:
				this->m_pMoveTarget->Up();
				return true;
			case GLFW_KEY_S:
				this->m_pMoveTarget->Down();
				return true;
			case GLFW_KEY_A:
				this->m_pMoveTarget->Left();
				return true;
			case GLFW_KEY_D:
				this->m_pMoveTarget->Right();
				return true;
			default:
				return false;
		}
	}

	bool Application::OnKeyRepeat(int key, int scancode, int mods) {
		switch(key){
			case GLFW_KEY_W:
				this->m_pMoveTarget->Up();
				return true;
			case GLFW_KEY_S:
				this->m_pMoveTarget->Down();
				return true;
			case GLFW_KEY_A:
				this->m_pMoveTarget->Left();
				return true;
			case GLFW_KEY_D:
				this->m_pMoveTarget->Right();
				return true;
			default:
				return false;
		}
	}

	bool Application::OnKeyRelease(int key, int scancode, int mods) {
		switch(key){
			case GLFW_KEY_W:
				this->m_pMoveTarget->Stop();
				return true;
			case GLFW_KEY_S:
				this->m_pMoveTarget->Stop();
				return true;
			case GLFW_KEY_A:
				this->m_pMoveTarget->Stop();
				return true;
			case GLFW_KEY_D:
				this->m_pMoveTarget->Stop();
				return true;
			default:
				return false;
		}
	}
}
