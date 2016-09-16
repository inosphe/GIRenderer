//
// Created by inosphe on 2016. 4. 12..
//

#include "Texture.h"

Render::Texture::Texture(Resource::Image::PTR pImage){
	InitTexture(pImage);
}

Render::Texture::Texture() {

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

void Render::Texture::Bind(Render::ShaderParam& shader, int i) const {
	int base = static_cast<int>(SHADER_UNIFORM_ENUM::TEX0);
	shader.BindTexture(static_cast<SHADER_UNIFORM_ENUM>(base+i), GetID());
}

void Render::Texture::Clear() {
	glDeleteTextures(1, &m_uTexture);
}

