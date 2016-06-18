//
// Created by inosphe on 2016. 3. 28..
//

#include "ForwardRenderingStrategy.h"
#include "util/GLUtil.h"
#include "Exception.h"
#include <cassert>
#include "RenderingParameters.h"

namespace Render{
	ForwardRenderingStrategy::ForwardRenderingStrategy()
	:IRenderingStrategy()
	{

	}

	ForwardRenderingStrategy::~ForwardRenderingStrategy() {

	}

	void ForwardRenderingStrategy::Init() {
		IRenderingStrategy::Init();

		try{
			glAttachShader(m_uProgram, GLUtil::LoadShader(GL_VERTEX_SHADER, "shader/textured.vert.glsl"));
			glAttachShader(m_uProgram, GLUtil::LoadShader(GL_FRAGMENT_SHADER, "shader/textured.frag.glsl"));
			glLinkProgram(m_uProgram);

			m_pParameters = new RenderingParameters(m_uProgram);
			m_pParameters->Init();
		}
		catch(const Core::Exception& ex){
			assert(false);
		}
	}

	void ForwardRenderingStrategy::Clear() {
		IRenderingStrategy::Clear();

	}

	void ForwardRenderingStrategy::RenderBegin() {
		IRenderingStrategy::RenderBegin();
		glDisable(GL_BLEND);
	}

	void ForwardRenderingStrategy::RenderEnd() {
		IRenderingStrategy::RenderEnd();
	}
}
