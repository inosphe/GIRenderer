//
// Created by inosphe on 2016. 4. 8..
//

#ifndef PROJECT_RENDERINGPARAMETERS_H
#define PROJECT_RENDERINGPARAMETERS_H

#include <glm/mat4x4.hpp>
#include <GLFW/glfw3.h>

namespace Render{
	class Camera;
	class Texture;

	class RenderingParameters {
	public:
		RenderingParameters(GLuint uProgram);

		void Init();
		void SetObjectTransform(const glm::mat4x4& matTransform);

		void BindCamera(Camera* pCamera);
		void BindTexture(int index, const GLuint id);

	private:
		GLuint m_uProgram = 0;

		GLuint m_uTransformLocation;
		GLuint m_uLookLocation;
		GLuint m_uViewProjLocation;
		GLuint m_uTextureLocation;
	};
}


#endif //PROJECT_RENDERINGPARAMETERS_H
