//
// Created by inosphe on 2016. 6. 19..
//

#include "Quad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <cstddef>

float interpolate(float v0, float v1, float t){
	return v0 * (1-t) + v1 * t;
}

Quad::Quad(int sx, int sy, int tw, int th, int adjust, bool point) {
// data for a fullscreen quad
	const GLfloat vertexData[] = {
			//  X     Y     Z           U     V
			1.0f, 1.0f, 0.0f,       1.0f, 1.0f, // vertex 0
			-1.0f, 1.0f, 0.0f,       0.0f, 1.0f, // vertex 1
			1.0f, -1.0f, 0.0f,       1.0f, 0.0f, // vertex 2
			-1.0f, 1.0f, 0.0f,       0.0f, 1.0f, // vertex 3
			-1.0f,-1.0f, 0.0f,       0.0f, 0.0f, // vertex 4
			1.0f, -1.0f, 0.0f,       1.0f, 0.0f, // vertex 5
	};
	const GLuint indexData[] = {0, 1, 2, 3, 4, 5};

	int nVertexCount = sx*sy;
	if(!point) nVertexCount *= 6;

	std::vector<QUAD_VERTEX_FORMAT> vertices(nVertexCount);
	std::vector<GLuint> indices;
	for(int x=0; x<sx; ++x){
		for(int y=0; y<sy; ++y){
			float _x = interpolate(-1.0f, 1.0f, float(x)/sx);
			float _y = interpolate(-1.0f, 1.0f, float(y)/sy);
			float _u = interpolate(0.0f, 1.0f, float(x)/sx);
			float _v = interpolate(0.0f, 1.0f, float(y)/sy);

			if(!point){
				for(int i=0; i<6; ++i){
					int idx = 6*(x+sx*y)+i;
					QUAD_VERTEX_FORMAT v;
					v.x = _x + vertexData[i*5+0]/sx + 1.0f/sx;
					v.y = _y + vertexData[i*5+1]/sy + 1.0f/sy;
					v.z = 0.0f;
					v.u = _u + vertexData[i*5+3]/sx + 0.5f/(tw)*adjust;
					v.v = _v + vertexData[i*5+4]/sy + 0.5f/(th)*adjust;
					v.color[0] = 128+127.0f*x/sx;
					v.color[1] = 128+127.0f*y/sy;
					v.color[2] = 0.0f;
					v.color[3] = 0.0f;

					vertices[idx] = v;
					indices.push_back(idx);
				}
			}
			else{
				int idx = x+sx*y;
				QUAD_VERTEX_FORMAT v;
				v.x = _x + 1.0f/sx;
				v.y = _y + 1.0f/sy;
				v.z = 0.0f;

				v.u = _u;
//				v.u += 0.25f/sx;
				v.u += 0.5f/(tw)*adjust;
				v.v = _v;
//				v.v += 0.25f/sy;
				v.v += 0.5f/(th)*adjust;

				v.color[0] = 255.0f*x/sx;
				v.color[1] = 255.0f*y/sy;
				v.color[2] = 0.0f;
				v.color[3] = 0.0f;
				vertices[idx] = v;
				indices.push_back(idx);
			}
		}
	}


	GenerateVAO();
	BindVAO();

	GenerateVertexBuffer();
	BindVertex();

	glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD_VERTEX_FORMAT)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QUAD_VERTEX_FORMAT), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(QUAD_VERTEX_FORMAT), (void*)offsetof(QUAD_VERTEX_FORMAT, u));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GLFW_TRUE, sizeof(QUAD_VERTEX_FORMAT), (void*)offsetof(QUAD_VERTEX_FORMAT, color));

	if(!point){
		GenerateIndexBuffer();
		BindIndex();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices.size(), &indices[0], GL_STATIC_DRAW);
		SetDrawCount(indices.size());
	}
	else{
		GenerateIndexBuffer();
		BindIndex();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices.size(), &indices[0], GL_STATIC_DRAW);
		SetDrawCount(indices.size());
		SetDrawMode(GL_POINTS);
	}
}
