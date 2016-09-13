//
// Created by inosphe on 2016. 6. 19..
//

#ifndef PROJECT_RENDERPASSDEFERRED0_H
#define PROJECT_RENDERPASSDEFERRED0_H

#include "RenderPass.h"

constexpr int num_framebuffer = 5;
constexpr int num_color_attachment = 4;

namespace Render{
	class RenderPassDeferred0 : public RenderPass {
	public:
		virtual void Init(const char *szVertexShader, const char *szFragShader) override;

		virtual void Clear() override;

		virtual void RenderBegin() override;
		virtual void RenderEnd() override;

		void InitFramebuffer();

		GLuint m_uGBuffer;
		GLuint m_uGBufferTex[num_framebuffer];
	};
};

#endif //PROJECT_RENDERPASSDEFERRED0_H
