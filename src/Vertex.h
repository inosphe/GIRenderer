//
// Created by inosphe on 2016. 4. 5..
//

#ifndef PROJECT_VERTEX_H
#define PROJECT_VERTEX_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Render{
	struct Vertex {
		glm::vec4 pos;
		glm::vec2 uv;
		glm::vec3 norm;
	};
}


#endif //PROJECT_VERTEX_H
