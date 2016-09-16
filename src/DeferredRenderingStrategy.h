//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_DEFERREDRENDERINGSTRATEGY_H
#define PROJECT_DEFERREDRENDERINGSTRATEGY_H

#include "IRenderingStrategy.h"
#include "Quad.h"
#include "DummyModel.h"
#include "DummyGradientTexture.h"

namespace Render{
	class DeferredRenderingStrategy : public IRenderingStrategy{
	public:
		DeferredRenderingStrategy();
		virtual ~DeferredRenderingStrategy();

		void Init() override;

		virtual void Render(const Camera& camera, std::function<void()> fRenderModels) override ;

	protected:
		void RenderToScreen(GLint viewport[4], int nRenderPass, GLuint* textures, int num);

	private:
		void InitFrameBuffer();

	private:
		Quad m_quad;
		DummyModel m_dummy;

	private:
		DummyGradientTexture *tex_r, *tex_g, *tex_b;
	};
}

#endif //PROJECT_DEFERREDRENDERINGSTRATEGY_H
