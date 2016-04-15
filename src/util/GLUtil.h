//
// Created by inosphe on 2016. 4. 3..
//

#ifndef PROJECT_GLUTIL_H
#define PROJECT_GLUTIL_H

#include <GLFW/glfw3.h>
#include "common_header.h"

namespace GLUtil{
	GLuint LoadShader(GLuint uType, const string& strFilepath);
	void CheckValidGLErrorCode(GLuint code);
	bool CheckError();
}

#endif //PROJECT_GLUTIL_H
