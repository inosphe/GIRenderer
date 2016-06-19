//
// Created by inosphe on 2016. 6. 19..
//

#ifndef PROJECT_RENDERPASS_H
#define PROJECT_RENDERPASS_H

namespace Render{
	class RenderingParameters;

	class RenderPass {
	public:
		virtual void Init(const char* szVertShader, const char* szFragShader);
		virtual void Clear();

		virtual void RenderBegin();
		virtual void RenderEnd();

		RenderingParameters& GetShader(){return *m_pParameters;}

	private:
		GLuint m_uProgram = 0;
		RenderingParameters* m_pParameters = nullptr;
	};
}


#endif //PROJECT_RENDERPASS_H
