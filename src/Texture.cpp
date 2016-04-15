//
// Created by inosphe on 2016. 4. 12..
//

#include "Texture.h"
#include "RenderingParameters.h"

Render::Texture::Texture(int iOffset, Resource::Image::PTR pImage)
:m_iTexOffset(iOffset)
{
	InitTexture(pImage);
}

Render::Texture::~Texture() {
	Clear();
}

void Render::Texture::InitTexture(Resource::Image::PTR pImage) {
	glGenTextures(1, &m_uTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GetID());
	glTexImage2D(GL_TEXTURE_2D, 0
			, GL_RGBA
			, pImage->GetWidth()
			, pImage->GetHeight()
			, 0
			, GL_RGBA
			, GL_UNSIGNED_BYTE
			, pImage->GetData());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void Render::Texture::Bind(Render::RenderingParameters &rp) const {
	glBindTexture(GL_TEXTURE_2D, GetID());
	rp.BindTexture(0, GetTexOffset());
}

void Render::Texture::Clear() {
	glDeleteTextures(1, &m_uTexture);
}
