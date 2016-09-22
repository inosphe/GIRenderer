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

	void ShaderParam::BindViewProj(SHADER_UNIFORM_ENUM eVal, const GameObject &camera) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			glm::mat4 matViewProj = camera.GetViewProj();
			GLint loc = itr->second.loc;
			if(loc>=0)
				glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(matViewProj));
		}
	}

	void ShaderParam::BindVec3f(SHADER_UNIFORM_ENUM eVal, const glm::vec3 v, bool bNormalize) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			GLint loc = itr->second.loc;
			glm::vec3 _v = bNormalize?normalize(v):v;
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

	void ShaderParam::BindTextures(SHADER_UNIFORM_ENUM eVal, GLuint *uTextures, const uint32_t numTexture) {
		GLuint __textures[16];

		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			auto& data = itr->second;
			GLint loc = data.loc;
			if(loc >= 0){
				for(int i=0; i<numTexture; ++i){
					glActiveTexture(GL_TEXTURE0+data.index+i);
					glBindTexture(GL_TEXTURE_2D, uTextures[i]);
					__textures[i] = data.index+i;
				}
				glUniform1iv(loc, (GLsizei)numTexture, (GLint*)__textures);
			}
		}
	}

	void ShaderParam::InitVariables() {
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

	void ShaderParam::Clear() {
		if(m_uProgram)
			glDeleteProgram(m_uProgram);
		m_uProgram = 0;
	}

	void ShaderParam::InitProgram() {
		m_uProgram = glCreateProgram();
	}

	void ShaderParam::BindInt(SHADER_UNIFORM_ENUM eVal, GLint val) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			GLint loc = itr->second.loc;
			if(loc >= 0){
				glUniform1i(loc, val);
			}
		}
	}

	void ShaderParam::BindFloat(SHADER_UNIFORM_ENUM eVal, GLfloat val) {
		auto itr = m_mapShaderUniform.find(eVal);
		if(itr != m_mapShaderUniform.end()){
			GLint loc = itr->second.loc;
			if(loc >= 0){
				glUniform1f(loc, val);
			}
		}
	}

	void ShaderParam::BindProgram() {
		glUseProgram(GetProgram());
	}

	void ShaderParam::UnbindProgram() {
		glUseProgram(0);
	}
}
