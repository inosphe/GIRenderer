//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_DEFERREDRENDERINGSTRATEGY_H
#define PROJECT_DEFERREDRENDERINGSTRATEGY_H

#include "IRenderingStrategy.h"
#include "Quad.h"
#include "DummyModel.h"
#include "DummyGradientTexture.h"
#include <vector>

namespace Render{
	class DeferredRenderingStrategy : public IRenderingStrategy{
	public:
		enum RENDER_PASS_ENUM{
			RSM
			, TEST_LIGHTING
			, LIGHT_INJECT
			, LIGHT_PROPAGATE
			, LIGHT_PROPAGATE2
			, RENDER_TO_SCREEN
			, QUAD_TEST
			, END
		};

	public:
		DeferredRenderingStrategy();
		virtual ~DeferredRenderingStrategy();

		void Init() override;

		virtual void Render(const Camera& camera, std::function<void()> fRenderModels) override ;

	protected:
		void RenderToScreen(GLint viewport[4], int nRenderPass, int split_h, const GLuint* textures, int num);
		void RenderToScreen(GLint viewport[4], int nRenderPass, int split_h, const std::vector<GLuint>& vecTextures);

	private:
		void InitFrameBuffer();

	private:
		Quad m_quad;
		Quad m_quad2;
		DummyModel m_dummy;

	private:
		DummyGradientTexture *tex_r, *tex_g, *tex_b;
		const int size = 64;
	};
}

#endif //PROJECT_DEFERREDRENDERINGSTRATEGY_H
