//
// Created by inosphe on 2016. 9. 14..
//

#include "DummyGradientTexture.h"

Render::DummyGradientTexture::DummyGradientTexture(int type) {
	const int size_x = 64;
	const int size_y = 64;
	const int size_z = 64;

	uint8_t* data = new uint8_t(size_x*size_y*size_z);
	for(int x=0; x<size_x; ++x){
		for(int y=0; y<size_y; ++y){
			for(int z=0; z<size_z; ++z){
				data[x + size_x*y + size_x*size_y*z] = type==0?x:type==1?y:z;
			}
		}
	}

	glGenTextures(1, &m_uTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GetID());
	glTexImage2D(GL_TEXTURE_2D, 0
		, GL_RGBA
		, size_x
		, size_y*size_z
		, 0
		, GL_RGBA
		, GL_UNSIGNED_BYTE
		, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
