//
// Created by inosphe on 2016. 6. 19..
//

#include <GL/glew.h>
#include <util/GLUtil.h>
#include "RenderPassDeferred0.h"

void Render::RenderPassDeferred0::Clear() {
	RenderPass::Clear();
}

void Render::RenderPassDeferred0::RenderBegin(int iFrameBuffer, bool bClean) {
	RenderPass::RenderBegin(iFrameBuffer, bClean);
}

void Render::RenderPassDeferred0::RenderEnd() {
	RenderPass::RenderEnd();
}
