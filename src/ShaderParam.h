//
// Created by inosphe on 2016. 9. 14..
//

#ifndef PROJECT_SHADERPARAM_H
#define PROJECT_SHADERPARAM_H

#include "common_header.h"
#include "GameObject.h"

#include <GLFW/glfw3.h>
#include <map>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Render{
	enum SHADER_UNIFORM_ENUM {
		TRANSFORM = 0
		, LOOK
		, CAMERA_POS
		, VIEWPROJ
		, LIGHT_POS
		, LIGHT_DIR
		, LIGHT_INTENSITY
		, GBUFFER_DIFFUSE
		, GBUFFER_POS
		, GBUFFER_NORMAL
		, GBUFFER_LIGHT
		, GBUFFER_DEPTH
		, TEX0
		, TEX1
		, TEX2
		, TEX3
		, TEX4
		, TEX5
		, TEX6
		, TEX7
		, LIGHT_VOLUME
		, R0 //reserved
		, R1
		, R2
		, R3
		, LPV_SIZE
		, LPV_CELL_SIZE
	};

	struct UNIFORM_DATA {
		std::string varName;
		GLint loc;
		int index;
	};

	class Camera;

	class ShaderParam {
	public:
		ShaderParam(){}
		virtual ~ShaderParam(){}

		void InitProgram();
		void InitVariables();

		void AddShaderUnfiorm(SHADER_UNIFORM_ENUM val, std::string varName, int index=0);

		void BindMat4x4const(SHADER_UNIFORM_ENUM eVal, glm::mat4x4& matTransform);
		void BindViewProj(SHADER_UNIFORM_ENUM eVal, const GameObject& camera);
		void BindVec3f(SHADER_UNIFORM_ENUM eVal, const glm::vec3 v);
		void BindTexture(SHADER_UNIFORM_ENUM eVal, GLuint uTexture);
		void BindTextures(SHADER_UNIFORM_ENUM eVal, GLuint* uTextures, const uint32_t numTexture);
		void BindInt(SHADER_UNIFORM_ENUM eVal, GLint val);
		void BindFloat(SHADER_UNIFORM_ENUM eVal, GLfloat val);

		void Clear();

		void BindProgram();
		void UnbindProgram();

		inline const GLuint GetProgram() const{return m_uProgram;}

	private:
		GLuint m_uProgram = 0;
		std::map<SHADER_UNIFORM_ENUM, UNIFORM_DATA> m_mapShaderUniform;
	};
}

#endif //PROJECT_SHADERPARAM_H
