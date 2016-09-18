//
// Created by inosphe on 2016. 6. 19..
//

#ifndef PROJECT_QUAD_H
#define PROJECT_QUAD_H

#include "IModel.h"

struct QUAD_VERTEX_FORMAT{
	float x, y, z;
	float u, v;
	uint8_t color[4];
};

class Quad : public Render::IModel{
public:
	Quad(int sx=1, int sy=1);
};


#endif //PROJECT_QUAD_H
