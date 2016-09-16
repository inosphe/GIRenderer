//
// Created by inosphe on 2016. 9. 15..
//

#ifndef PROJECT_FRAMEBUFFER_H
#define PROJECT_FRAMEBUFFER_H

#include "common_header.h"
#include <GLFW/glfw3.h>

namespace Render{
	class FrameBuffer {
	public:
		FrameBuffer(int nTextureNum);
		virtual ~FrameBuffer();

		void Init();
		void Clear();

		void RenderBegin();
		void RenderEnd();

		GLuint* m_uTextures = nullptr;
		GLuint m_uDepthMap = 0;
	private:
		GLuint m_uGBuffer = 0;
		int m_nTextureNum = 0;
	};
}



#endif //PROJECT_FRAMEBUFFER_H
