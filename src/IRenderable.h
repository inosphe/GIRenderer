//
// Created by inosphe on 2016. 4. 2..
//

#ifndef PROJECT_IRENDERABLE_H
#define PROJECT_IRENDERABLE_H

#include <vector>

namespace Render{
	class RenderingParameters;

	class IRenderable {
	public:
		IRenderable();
		virtual ~IRenderable();
		virtual void Clear(){}

		virtual void UpdateForRender(){}
		virtual void Render(RenderingParameters& rp) = 0;

	};
}



#endif //PROJECT_IRENDERABLE_H
