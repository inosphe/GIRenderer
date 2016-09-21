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
#include "Camera.h"

const int lpv_size = 32;
const int lpv_cellsize = 64;

namespace Render{
	class DeferredRenderingStrategy : public IRenderingStrategy{
	public:
		enum RENDER_PASS_ENUM{
			MAIN_GBUFFER
			, LIGHT_GBUFFER
			, TEST_LIGHTING
			, LIGHT_INJECT
			, LIGHT_PROPAGATE
			, RENDER_TO_SCREEN
			, POST_LPV
			, QUAD_TEST
			, ACCUM_LPV
			, DOWNSAMPLE_GBUFFER
			, END
		};

	public:
		DeferredRenderingStrategy();
		virtual ~DeferredRenderingStrategy();

		void Init() override;
		void Clear() override;

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

		Camera light;

	private:
		DummyGradientTexture *tex_r, *tex_g, *tex_b;
	};
}

#endif //PROJECT_DEFERREDRENDERINGSTRATEGY_H
