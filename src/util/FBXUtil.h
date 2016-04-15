//
// Created by inosphe on 2016. 4. 3..
//

#ifndef PROJECT_FBXUTIL_H
#define PROJECT_FBXUTIL_H

#include <fbxsdk.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace FBXUtil{
	glm::mat4x4 ToGLU(const FbxAMatrix& matFbx);
	glm::vec4 ToGLU(const FbxVector4& vecFbx);
	glm::vec2 ToGLU(const FbxVector2& vecFbx);
}

#endif //PROJECT_FBXUTIL_H
