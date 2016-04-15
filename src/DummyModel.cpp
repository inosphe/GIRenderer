//
// Created by inosphe on 2016. 4. 2..
//

#include "DummyModel.h"
#include <GLFW/glfw3.h>

DummyModel::DummyModel() {

}

void DummyModel::Init() {
	IModel::Init();

	// data for a fullscreen quad
	const GLfloat vertexData[] = {
		//  X     Y     Z           R     G     B
		1.0f, 1.0f, 0.0f,       1.0f, 0.0f, 0.0f, // vertex 0
		-1.0f, 1.0f, 0.0f,       0.0f, 1.0f, 0.0f, // vertex 1
		1.0f,-1.0f, 0.0f,       0.0f, 0.0f, 1.0f, // vertex 2
		1.0f, 1.0f, 0.0f,       0.0f, 0.0f, 1.0f, // vertex 3
		-1.0f, 1.0f, 0.0f,       0.0f, 1.0f, 0.0f, // vertex 4
		-1.0f,-1.0f, 0.0f,       1.0f, 0.0f, 0.0f, // vertex 5
	}; // 6 vertices with 6 components (floats) each

	GenerateVAO();
	BindVAO();

	GenerateVertexBuffer();
	BindVertex();

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*6, vertexData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	SetDrawCount(6);
}
