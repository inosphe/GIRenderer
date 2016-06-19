//
// Created by inosphe on 2016. 4. 12..
//

#include "Image.h"
#include <GL/glew.h>
#include <stdlib.h>

Resource::Image::Image() {

}

Resource::Image::Image(BYTE *pData, int w, int h, int comp)
:m_pData(pData), m_iWidth(w), m_iHeight(h), m_iComp(comp)
{

}

int Resource::Image::GetFormat() {
	switch(m_iComp){
		case 4:
			return GL_RGBA;
		case 3:
			return GL_RGB;
		case 1:
			return GL_RED;
	}

	return -1;
}

Resource::Image::~Image() {
	if(m_pData)
		free(m_pData);
}
