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
	void ShaderParam::AddShaderUnfiorm(SHADER_UNIFORM_ENUM val, std::string varName, int index) {
		UNIFORM_DATA data;
		data.varName = varName;
		data.loc = -1;
		data.index = index;

		m_mapShaderUniform.insert(std::make_pair(val, data));
	}

	void ShaderParam::BindViewProj(SHADER_UNIFORM_ENUM eVal, const Camera &camera) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			glm::mat4 matViewProj = camera.GetViewProj();
			GLint loc = itr->second.loc;
			if(loc>=0)
				glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(matViewProj));
		}
	}

	void ShaderParam::BindVec3f(SHADER_UNIFORM_ENUM eVal, const glm::vec3 v) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			glm::vec3 _v = glm::normalize(v);
			GLint loc = itr->second.loc;
			if(loc>=0)
				glUniform3fv(loc, 1, value_ptr(_v));
		}
	}

	void ShaderParam::BindTexture(SHADER_UNIFORM_ENUM eVal, GLuint uTexture) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			auto& data = itr->second;
			GLint loc = data.loc;
			if(loc >= 0){
				glActiveTexture(GL_TEXTURE0+data.index);
				glBindTexture(GL_TEXTURE_2D, uTexture);
				glUniform1i(loc, data.index);
			}
		}
	}

	void ShaderParam::Init() {
		for(auto& i : m_mapShaderUniform){
			const std::string& str = i.second.varName;
			GLint loc = glGetUniformLocation(m_uProgram, str.c_str());
			i.second.loc = loc;
		}
	}

	void ShaderParam::BindMat4x4const(SHADER_UNIFORM_ENUM eVal, glm::mat4x4 &matTransform) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			GLint loc = itr->second.loc;
			if(loc >= 0){
				glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matTransform));
			}
		}
	}
}