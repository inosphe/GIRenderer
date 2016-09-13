//
// Created by inosphe on 2016. 4. 8..
//

#ifndef PROJECT_RENDERINGPARAMETERS_H
#define PROJECT_RENDERINGPARAMETERS_H

#include <glm/mat4x4.hpp>
#include <GLFW/glfw3.h>
#include <vector>

namespace Render{
	class Camera;
	class Texture;

	class RenderingParameters {
	public:
		RenderingParameters(GLuint uProgram);

		void SetTextureNum(uint32_t nTextureNum);

		void Init();
		void Clear();
		void SetObjectTransform(const glm::mat4x4& matTransform);

		void BindCamera(const Camera& camera);
		void BindTexture(int index, GLuint uTexture);

	private:
		GLuint m_uProgram = 0;

		GLint m_uTransformLocation = -1;
		GLint m_uLookLocation = -1;
		GLint m_uCameraPosLocation = -1;
		GLint m_uViewProjLocation = -1;
		std::vector<GLint> m_vecTextureLocation;

		uint32_t m_nTextureNum = 0;
	};
}


#endif //PROJECT_RENDERINGPARAMETERS_H
