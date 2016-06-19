//
// Created by inosphe on 2016. 6. 19..
//

#include "Quad.h"
#include <GLFW/glfw3.h>

Quad::Quad() {
// data for a fullscreen quad
	const GLfloat vertexData[] = {
			//  X     Y     Z           U     V
			1.0f, 1.0f, 0.0f,       1.0f, 1.0f, // vertex 0
			-1.0f, 1.0f, 0.0f,       0.0f, 1.0f, // vertex 1
			1.0f, -1.0f, 0.0f,       1.0f, 0.0f, // vertex 2
			-1.0f, 1.0f, 0.0f,       0.0f, 1.0f, // vertex 3
			-1.0f,-1.0f, 0.0f,       0.0f, 0.0f, // vertex 5
			1.0f, -1.0f, 0.0f,       1.0f, 0.0f, // vertex 4
	};

	const GLuint indices[] = {0, 1, 2, 3, 4, 5};

	GenerateVAO();
	BindVAO();

	GenerateVertexBuffer();
	BindVertex();

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*5, vertexData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	GenerateIndexBuffer();
	BindIndex();

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*6, indices, GL_STATIC_DRAW);
	SetDrawCount(6);
}
