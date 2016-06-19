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
		void Clear();
		void SetObjectTransform(const glm::mat4x4& matTransform);

		void BindCamera(const Camera& camera);
		void BindTexture(int index);

	private:
		GLuint m_uProgram = 0;

		GLint m_uTransformLocation = -1;
		GLint m_uLookLocation = -1;
		GLint m_uViewProjLocation = -1;
		GLint m_uTextureLocation = -1;
	};
}


#endif //PROJECT_RENDERINGPARAMETERS_H
