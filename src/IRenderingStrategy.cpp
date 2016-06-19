//
// Created by inosphe on 2016. 3. 28..
//

#include "IRenderingStrategy.h"
#include "RenderingParameters.h"
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

	void IRenderingStrategy::AddRenderPass(RenderPass *pRenderPass, int i) {
		if(i>=0){
			m_vecRenderPass.insert(m_vecRenderPass.begin()+i, pRenderPass);
		}
		else{
			m_vecRenderPass.push_back(pRenderPass);
		}
	}

	RenderingParameters &IRenderingStrategy::GetShader() {
		return GetCurrentRenderPass()->GetShader();
	}
}
