//
// Created by inosphe on 2016. 6. 19..
//

#ifndef PROJECT_QUAD_H
#define PROJECT_QUAD_H

#include "IModel.h"

struct QUAD_VERTEX_FORMAT{
	QUAD_VERTEX_FORMAT():x(0), y(0), z(0), u(0), v(0){color[0]=color[1]=color[2]=color[3]=0.0f;}

	float x, y, z;
	float u, v;
	uint8_t color[4];
};

class Quad : public Render::IModel{
public:
	Quad(int sx, int sy, int tw, int th, int adjust, bool point);
};


#endif //PROJECT_QUAD_H
