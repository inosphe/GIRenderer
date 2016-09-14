//
// Created by inosphe on 2016. 4. 2..
//

#ifndef PROJECT_IRENDERABLE_H
#define PROJECT_IRENDERABLE_H

#include "ShaderParam.h"

namespace Render{
	class IRenderable {
	public:
		IRenderable();
		virtual ~IRenderable();
		virtual void Clear(){}

		virtual void UpdateForRender(){}
		virtual void Render(Render::ShaderParam& shader) = 0;

	};
}



#endif //PROJECT_IRENDERABLE_H
