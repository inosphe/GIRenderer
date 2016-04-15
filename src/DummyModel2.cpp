//
// Created by inosphe on 2016. 4. 6..
//

#include "DummyModel2.h"
#include <cmath>
#include <chrono>

void DummyModel2::Init() {
	IModel::Init();

	// data for a cube
	GLfloat vertexData[] = {
		//  X     Y     Z           R     G     B
		// face 0:
		1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f, // vertex 0
		-1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 0.0f, // vertex 1
		1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f, // vertex 2
		-1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 0.0f, // vertex 3

		// face 1:
		1.0f, 1.0f, 1.0f,       0.0f, 1.0f, 0.0f, // vertex 0
		1.0f,-1.0f, 1.0f,       0.0f, 1.0f, 0.0f, // vertex 1
		1.0f, 1.0f,-1.0f,       0.0f, 1.0f, 0.0f, // vertex 2
		1.0f,-1.0f,-1.0f,       0.0f, 1.0f, 0.0f, // vertex 3

		// face 2:
		1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 1.0f, // vertex 0
		1.0f, 1.0f,-1.0f,       0.0f, 0.0f, 1.0f, // vertex 1
		-1.0f, 1.0f, 1.0f,       0.0f, 0.0f, 1.0f, // vertex 2
		-1.0f, 1.0f,-1.0f,       0.0f, 0.0f, 1.0f, // vertex 3

		// face 3:
		1.0f, 1.0f,-1.0f,       1.0f, 1.0f, 0.0f, // vertex 0
		1.0f,-1.0f,-1.0f,       1.0f, 1.0f, 0.0f, // vertex 1
		-1.0f, 1.0f,-1.0f,       1.0f, 1.0f, 0.0f, // vertex 2
		-1.0f,-1.0f,-1.0f,       1.0f, 1.0f, 0.0f, // vertex 3

		// face 4:
		-1.0f, 1.0f, 1.0f,       0.0f, 1.0f, 1.0f, // vertex 0
		-1.0f, 1.0f,-1.0f,       0.0f, 1.0f, 1.0f, // vertex 1
		-1.0f,-1.0f, 1.0f,       0.0f, 1.0f, 1.0f, // vertex 2
		-1.0f,-1.0f,-1.0f,       0.0f, 1.0f, 1.0f, // vertex 3

		// face 5:
		1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 1.0f, // vertex 0
		-1.0f,-1.0f, 1.0f,       1.0f, 0.0f, 1.0f, // vertex 1
		1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 1.0f, // vertex 2
		-1.0f,-1.0f,-1.0f,       1.0f, 0.0f, 1.0f, // vertex 3
	}; // 6 faces with 4 vertices with 6 components (floats)

	GenerateVAO();
	BindVAO();

	GenerateVertexBuffer();
	BindVertex();

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*4*6, vertexData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	GenerateIndexBuffer();
	BindIndex();


	GLuint indexData[] = {
		// face 0:
		0,1,2,      // first triangle
		2,1,3,      // second triangle
		// face 1:
		4,5,6,      // first triangle
		6,5,7,      // second triangle
		// face 2:
		8,9,10,     // first triangle
		10,9,11,    // second triangle
		// face 3:
		12,13,14,   // first triangle
		14,13,15,   // second triangle
		// face 4:
		16,17,18,   // first triangle
		18,17,19,   // second triangle
		// face 5:
		20,21,22,   // first triangle
		22,21,23,   // second triangle
	};

	// fill with data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*6*2*3, indexData, GL_STATIC_DRAW);
	SetDrawCount(36);
}

void DummyModel2::Update(int ms) {
	auto now = std::chrono::system_clock::now();
//	auto time_t = std::chrono::system_clock::to_time_t(now);
//	auto ms = std::chrono::duration_cast<std::chrono::microseconds>(now);
	auto duration = now.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	float t = (millis%1000)/1000.0f;
	SetPosition(glm::vec3(1.0f*std::sin(2*M_PI*t), 0.0f, 0.0f));
}
