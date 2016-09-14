//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <cassert>
#include <GLFW/glfw3.h>
#include "IRenderingStrategy.h"
#include "ShaderParam.h"
#include <memory>

class IScene;

namespace Render {
	class Camera;

	class Renderer {
	public:
		Renderer();
		virtual ~Renderer();

		void Init();
		void Clear();

		template <typename T, typename... C>
		void InitRenderingStrategy(C... args){
			assert(!m_pRenderingStrategy);

			m_pRenderingStrategy = new T(args...);
			m_pRenderingStrategy->Init();
		};

		void Render(std::function<void()> fRenderModels);
		inline ShaderParam& GetShader(){return *(ShaderParam*)m_pRenderingStrategy->GetCurrentRenderPass();}
		void SetCamera(std::shared_ptr<Render::Camera> pCamera);
		std::shared_ptr<Render::Camera> GetTargetCamera(){return m_pCamera;}
		Render::Camera& GetTargetCameraRef(){return *m_pCamera.get();}
	private:
		IRenderingStrategy* m_pRenderingStrategy = nullptr;
		std::shared_ptr<Render::Camera> m_pCamera = nullptr;

	};
};



#endif //PROJECT_RENDERER_H
