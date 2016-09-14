//
// Created by inosphe on 2016. 6. 19..
//

#ifndef PROJECT_RENDERPASS_H
#define PROJECT_RENDERPASS_H

#include "ShaderParam.h"

namespace Render{
	class RenderPass : public ShaderParam{
	public:

	public:
		virtual void Init(const char* szVertShader, const char* szFragShader);
		virtual void Clear();

		virtual void RenderBegin();
		virtual void RenderEnd();
	};
}


#endif //PROJECT_RENDERPASS_H
