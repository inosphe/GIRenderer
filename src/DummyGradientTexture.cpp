//
// Created by inosphe on 2016. 9. 14..
//

#include <GL/glew.h>
#include "DummyGradientTexture.h"

Render::DummyGradientTexture::DummyGradientTexture(int size, int type) {
	const int size_x = size;
	const int size_y = size;
	const int size_z = size;

	m_pData = new uint8_t[size_x*size_y*size_z];
	int i;
	for(int x=0; x<size_x; ++x){
		for(int y=0; y<size_y; ++y){
			for(int z=0; z<size_z; ++z){
				i = x + size_x*y + size_x*size_y*z;
				m_pData[i] = type==0?x:type==1?y:z;
				m_pData[i] *= 4;
			}
		}
	}

	glGenTextures(1, &m_uTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GetID());
//	glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8, size_x, size_y*size_z);
//	glTexSubImage2D(GL_TEXTURE_2D, 0
//		, 0
//	    , 0
//		, size_x
//		, size_y*size_z
//		, GL_RED
//		, GL_UNSIGNED_BYTE
//		, m_pData);

	glTexImage2D(GL_TEXTURE_2D, 0
        , GL_R8
		, size_x
		, size_y*size_z
        , 0
		, GL_RED
		, GL_UNSIGNED_BYTE
		, m_pData);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

Render::DummyGradientTexture::~DummyGradientTexture() {
	if(m_pData){
		SAFE_DELETE_ARRAY(m_pData);
		m_pData = nullptr;
	}
}
