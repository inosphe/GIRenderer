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
		virtual void Clear() override;

		virtual void RenderBegin(int iFrameBuffer, bool bClean) override;
		virtual void RenderEnd() override;
	};
};

#endif //PROJECT_RENDERPASSDEFERRED0_H
