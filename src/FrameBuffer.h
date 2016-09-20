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
		FrameBuffer(int nTextureNum, int w, int h);
		FrameBuffer(int nTextureNum);
		virtual ~FrameBuffer();

		void Init();
		void Clear();

		void RenderBegin(bool bClear=true);
		void RenderEnd();

		GLuint* m_uTextures = nullptr;
		GLuint m_uDepthMap = 0;

		void SetClearColor(float r, float g, float b, float a);

		float m_color[4] = {0, 0, 0, 1};

	private:
		GLuint m_uGBuffer = 0;
		int m_nTextureNum = 0;
		int m_iW = 640;
		int m_iH = 480;

		GLint m_prev_viewport[4];
	};
}



#endif //PROJECT_FRAMEBUFFER_H
