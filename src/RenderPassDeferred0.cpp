//
// Created by inosphe on 2016. 6. 19..
//

#include <GL/glew.h>
#include <util/GLUtil.h>
#include "RenderPassDeferred0.h"

void Render::RenderPassDeferred0::Init(const char *szVertexShader, const char* szGeoShader, const char *szFragShader) {
	RenderPass::Init(szVertexShader, szGeoShader, szFragShader);
}

void Render::RenderPassDeferred0::Clear() {
	RenderPass::Clear();
}

void Render::RenderPassDeferred0::RenderBegin() {
	RenderPass::RenderBegin();
}

void Render::RenderPassDeferred0::RenderEnd() {
	RenderPass::RenderEnd();
}
