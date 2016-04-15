//
// Created by inosphe on 2016. 4. 3..
//

#include "GLUtil.h"
#include <fstream>
#include <ios>
#include <vector>
#include <iostream>
#include <cassert>
#include "Logger.h"
#include <OPENGL/glu.h>

// helper to check and display for shader compiler errors
static bool check_shader_compile_status(GLuint obj) {
	GLint status;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetShaderInfoLog(obj, length, &length, &log[0]);
		std::cerr << &log[0];
		return false;
	}
	return true;
}

namespace GLUtil{
	GLuint LoadShader(GLuint uType, const string& strFilepath){
		std::ifstream in(strFilepath, std::ios::ate | std::ios::binary);
		if(!in.is_open()){
			return false;
		}
		in.seekg(0, std::ios_base::end);
		GLint size = in.tellg();

		GLuint uShader = glCreateShader(uType);

		char* szShader = new char[size];
		in.seekg(0, std::ios_base::beg);
		in.read(szShader, size);
		in.close();

		glShaderSource(uShader, 1, &szShader, &size);
		glCompileShader(uShader);

		SAFE_DELETE(szShader);

		if(!check_shader_compile_status(uShader)){
			assert(false);
			glDeleteShader(uShader);
			uShader = 0;
			Logger::Error("compile '"+strFilepath+"' was failed.");
		}

		GLint nLogLength = 0;
		glGetShaderiv(uShader, GL_INFO_LOG_LENGTH, &nLogLength);
		std::string strLog;
		strLog.reserve(nLogLength);
		glGetShaderInfoLog(uShader, nLogLength, NULL, (GLchar*)strLog.c_str());

		Logger::Debug(strLog);

		return uShader;
	}

	void CheckValidGLErrorCode(GLuint code) {

	}

	bool CheckError() {
		// check for errors
		GLenum error = glGetError();
		if(error != GL_NO_ERROR) {
			Logger::Debug(""+error);
			Logger::Error((const char*)gluErrorString(error));
			assert(false);
			return false;
		}

		return true;
	}
}