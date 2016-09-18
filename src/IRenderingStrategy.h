//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_IRENDERINGSTRATEGY_H
#define PROJECT_IRENDERINGSTRATEGY_H

#include <GLFW/glfw3.h>
#include "common_header.h"
#include <vector>
#include <functional>

namespace Render{
	class RenderingParameters;
	class RenderPass;
	class Camera;

	class IRenderingStrategy {
	public:
		IRenderingStrategy();
		virtual ~IRenderingStrategy();

		virtual void Init();
		virtual void Clear();

		uint32_t AddRenderPass(RenderPass* pRenderPass, int at=-1);

		void RenderBegin(int nRenderPass);
		void RenderEnd();

		inline void SetRenderPass(int i){m_nRenderPass = i;}
		inline RenderPass* GetRenderPass(int i){return m_vecRenderPass[i];}
		inline RenderPass* GetCurrentRenderPass(){return GetRenderPass(m_nRenderPass);}

		virtual void Render(const Camera& camera, std::function<void()> fRenderModels)=0;
	protected:
		int m_nRenderPass = 0;
		std::vector<RenderPass*> m_vecRenderPass;
	};
};


#endif //PROJECT_IRENDERINGSTRATEGY_H
