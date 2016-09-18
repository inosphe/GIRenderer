//
// Created by inosphe on 2016. 3. 28..
//

#include "IRenderingStrategy.h"
#include "RenderPass.h"

namespace Render{

	IRenderingStrategy::IRenderingStrategy(){
	}

	IRenderingStrategy::~IRenderingStrategy() {
		Clear();
	}

	void IRenderingStrategy::Init(){
	}

	void IRenderingStrategy::Clear(){
		for(auto pRenderPass : m_vecRenderPass){
			SAFE_DELETE(pRenderPass);
		}
		m_vecRenderPass.clear();
	}

	void IRenderingStrategy::RenderBegin(int nRenderPass) {
		SetRenderPass(nRenderPass);
		GetCurrentRenderPass()->RenderBegin();
	}

	void IRenderingStrategy::RenderEnd() {
		GetCurrentRenderPass()->RenderEnd();
	}

	uint32_t IRenderingStrategy::AddRenderPass(RenderPass *pRenderPass, int at) {
		for(uint32_t i=m_vecRenderPass.size(); i<=at; ++i){
			m_vecRenderPass.push_back(nullptr);
		}

		if(at>=0){
			m_vecRenderPass[at] = pRenderPass;
			return at;
		}
		else{
			m_vecRenderPass.push_back(pRenderPass);
			return m_vecRenderPass.size()-1;
		}

	}
}
