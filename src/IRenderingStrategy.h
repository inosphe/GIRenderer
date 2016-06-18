//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_IRENDERINGSTRATEGY_H
#define PROJECT_IRENDERINGSTRATEGY_H

#include <GLFW/glfw3.h>
#include "common_header.h"

namespace Render{
	class RenderingParameters;

	class IRenderingStrategy {
	public:
		IRenderingStrategy();
		virtual ~IRenderingStrategy();

		virtual void Init();
		virtual void Clear();

		virtual void RenderBegin();
		virtual void RenderEnd();

		RenderingParameters& GetShader(){return *m_pParameters;}

	protected:
		GLuint m_uProgram = 0;
		RenderingParameters* m_pParameters = nullptr;
	};
};


#endif //PROJECT_IRENDERINGSTRATEGY_H
