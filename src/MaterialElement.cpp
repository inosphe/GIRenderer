//
// Created by inosphe on 2016. 4. 12..
//

#include "MaterialElement.h"
#include "Texture.h"

Render::MaterialElement::MaterialElement() {

}

Render::MaterialElement::~MaterialElement() {
	Clear();
}

void Render::MaterialElement::AddTexture(Resource::Image::PTR pImage) {
	if(pImage != nullptr)
		m_vecTexture.push_back(new Texture(pImage));
}

void Render::MaterialElement::Bind(Render::ShaderParam& shader) const {
	for(int i=0; i<m_vecTexture.size(); ++i){
		m_vecTexture[i]->Bind(shader, i);
	}
}

void Render::MaterialElement::Clear() {
	for(auto p : m_vecTexture){
		SAFE_DELETE(p);
	}
}
