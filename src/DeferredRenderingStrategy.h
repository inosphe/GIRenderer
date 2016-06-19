//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_DEFERREDRENDERINGSTRATEGY_H
#define PROJECT_DEFERREDRENDERINGSTRATEGY_H

#include "IRenderingStrategy.h"
#include "Quad.h"
#include "DummyModel.h"

namespace Render{
	class DeferredRenderingStrategy : public IRenderingStrategy{
	public:
		DeferredRenderingStrategy();
		virtual ~DeferredRenderingStrategy();

		void Init() override;


		virtual void Render(const Camera& camera, std::function<void()> fRenderModels) override ;

	private:
		void InitFrameBuffer();

	private:
		Quad m_quad;
		DummyModel m_dummy;
	};
}

#endif //PROJECT_DEFERREDRENDERINGSTRATEGY_H
