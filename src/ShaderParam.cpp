//
// Created by inosphe on 2016. 9. 14..
//

#include "ShaderParam.h"
#include <GLFW/glfw3.h>
#include <util/GLUtil.h>
#include "Exception.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>


namespace Render{
	void ShaderParam::AddShaderUnfiorm(SHADER_UNIFORM_ENUM val, std::string varName) {
		m_mapShaderUniform.insert(std::make_pair(val, std::make_pair(varName, static_cast<GLint>(-1))));
	}

	void ShaderParam::BindViewProj(SHADER_UNIFORM_ENUM eVal, const Camera &camera) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			glm::mat4 matViewProj = camera.GetViewProj();
			GLint loc = itr->second.second;
			if(loc>=0)
				glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(matViewProj));
		}
	}

	void ShaderParam::BindVec3f(SHADER_UNIFORM_ENUM eVal, const glm::vec3 v) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			glm::vec3 _v = glm::normalize(v);
			GLint loc = itr->second.second;
			if(loc>=0)
				glUniform3fv(loc, 1, value_ptr(_v));
		}
	}

	void ShaderParam::BindTexture(SHADER_UNIFORM_ENUM eVal, int index, GLuint uTexture) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			GLint loc = itr->second.second;
			if(loc >= 0){
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, uTexture);
				glUniform1i(loc, 0);
			}
		}
	}

	void ShaderParam::Init() {
		for(auto& i : m_mapShaderUniform){
			i.second.second = glGetUniformLocation(m_uProgram, i.second.first.c_str());
		}
	}

	void ShaderParam::BindMat4x4const(SHADER_UNIFORM_ENUM eVal, glm::mat4x4 &matTransform) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			GLint loc = itr->second.second;
			if(loc >= 0){
				glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matTransform));
			}
		}
	}
}
