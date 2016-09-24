//
// Created by inosphe on 2016. 6. 19..
//

#ifndef PROJECT_RENDERPASS_H
#define PROJECT_RENDERPASS_H

#include "ShaderParam.h"
#include "FrameBuffer.h"
#include <vector>

namespace Render{
	class RenderPass : public ShaderParam{
	public:

	public:
		virtual void Init(const char* szVertShader, const char* szGeoShader, const char* szFragShader);
		virtual void Init(const std::vector<std::pair<GLuint, std::string>>& vecShaders);

		void LoadShader(GLuint type, const char* szShader);
		virtual void Clear();

		virtual void RenderBegin(int iFrameBuffer, bool bClear);
		virtual void RenderBegin(FrameBuffer* pFB, bool bClear);
		virtual void RenderEnd();

		void SetFrameBuffer(std::shared_ptr<FrameBuffer> pFrameBuffer, int at);
		std::shared_ptr<FrameBuffer> GetFrameBuffer(int at);
		inline std::shared_ptr<FrameBuffer> GetCurFrameBuffer(){return m_pCurFrameBuffer;}
		void UseFrameBuffer(int at);
		inline uint32_t FrameBufferNum(){return m_vecFrameBuffers.size();}

	private:
		std::vector<std::shared_ptr<FrameBuffer>> m_vecFrameBuffers;
		std::shared_ptr<FrameBuffer> m_pCurFrameBuffer = nullptr;
	};
}


#endif //PROJECT_RENDERPASS_H
