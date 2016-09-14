//
// Created by inosphe on 2016. 9. 14..
//

#ifndef PROJECT_SHADERPARAM_H
#define PROJECT_SHADERPARAM_H

#include "common_header.h"

#include <GLFW/glfw3.h>
#include <map>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Render{
	enum SHADER_UNIFORM_ENUM {
		TRANSFORM
		, LOOK
		, CAMERA_POS
		, VIEWPROJ
		, GBUFFER_DIFFUSE
		, GBUFFER_POS
		, GBUFFER_NORMAL
		, GBUFFER_LIGHT
		, GBUFFER_DEPTH
		, TEX0
		, TEX1
		, TEX2
		, LIGHT_VOLUME
		, LIGHT_VOLUME_TEST
	};

	class Camera;

	class ShaderParam {
	public:
		ShaderParam(){}
		virtual ~ShaderParam(){}

		void Init();

		void AddShaderUnfiorm(SHADER_UNIFORM_ENUM val, std::string varName);

		void BindMat4x4const(SHADER_UNIFORM_ENUM eVal, glm::mat4x4& matTransform);
		void BindViewProj(SHADER_UNIFORM_ENUM eVal, const Camera& camera);
		void BindVec3f(SHADER_UNIFORM_ENUM eVal, const glm::vec3 v);
		void BindTexture(SHADER_UNIFORM_ENUM eVal, int index, GLuint uTexture);

	protected:
		GLuint m_uProgram = 0;

	private:
		std::map<SHADER_UNIFORM_ENUM, std::pair<std::string, GLint>> m_mapShaderUniform;
	};
}

#endif //PROJECT_SHADERPARAM_H
