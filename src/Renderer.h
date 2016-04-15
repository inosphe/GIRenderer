//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_RENDERER_H
#define PROJECT_RENDERER_H

#include <cassert>
#include <GLFW/glfw3.h>
#include "IRenderingStrategy.h"
#include "RenderingParameters.h"
#include <memory>

class IScene;

namespace Render {
	class Camera;
	class RenderingParameters;

	class Renderer {
	public:
		Renderer();
		virtual ~Renderer();

		void Init();
		void Clear();

		template <typename T, typename... C>
		void InitRenderingStrategy(C... args){
			assert(!m_pRenderingStrategy);

			m_pRenderingStrategy = new T(m_uProgram, args...);
			m_pRenderingStrategy->Init();

			m_pParameters = new RenderingParameters(m_uProgram);
			m_pParameters->Init();
		};

		void RenderBegin();
		void RenderEnd();

		void SetCamera(std::shared_ptr<Render::Camera> pCamera);
		std::shared_ptr<Render::Camera> GetTargetCamera(){return m_pCamera;}
		Render::Camera* GetTargetCameraRaw(){return m_pCamera.get();}
		inline RenderingParameters& GetRenderingParameters(){return *m_pParameters;}

		GLuint m_uProgram = 0;
	private:
		RenderingParameters* m_pParameters = nullptr;
		IRenderingStrategy* m_pRenderingStrategy = nullptr;
		std::shared_ptr<Render::Camera> m_pCamera = nullptr;

	};
};



#endif //PROJECT_RENDERER_H
