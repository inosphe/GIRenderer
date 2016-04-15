//
// Created by inosphe on 2016. 4. 3..
//

#include "FBXUtil.h"
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace FBXUtil{
	glm::mat4x4 ToGLU(const FbxAMatrix& matFbx){
#define _mv(i) glm::make_vec4(matFbx.GetColumn(i).Buffer())
		return glm::mat4x4(_mv(0), _mv(1), _mv(2), _mv(3));
	}

	glm::vec4 ToGLU(const FbxVector4 &vecFbx) {
		return glm::make_vec4(vecFbx.Buffer());
	}

	glm::vec2 ToGLU(const FbxVector2 &vecFbx) {
		return glm::make_vec2(vecFbx.Buffer());
	}
}