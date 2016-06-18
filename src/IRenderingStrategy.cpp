//
// Created by inosphe on 2016. 3. 28..
//

#include "IRenderingStrategy.h"
#include "RenderingParameters.h"

namespace Render{

	IRenderingStrategy::IRenderingStrategy(){
	}

	IRenderingStrategy::~IRenderingStrategy() {
		Clear();
	}

	void IRenderingStrategy::Init(){
		m_uProgram = glCreateProgram();
	}

	void IRenderingStrategy::Clear(){
		if(m_uProgram)
			glDeleteProgram(m_uProgram);
		m_uProgram = 0;

		if(m_pParameters)
			m_pParameters->Clear();
		SAFE_DELETE(m_pParameters);
	}

	void IRenderingStrategy::RenderBegin() {
		glUseProgram(m_uProgram);
	}

	void IRenderingStrategy::RenderEnd() {

	}
}
