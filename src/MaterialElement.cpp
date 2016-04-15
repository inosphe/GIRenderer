//
// Created by inosphe on 2016. 4. 12..
//

#include "MaterialElement.h"
#include "Texture.h"
#include "RenderingParameters.h"

Render::MaterialElement::MaterialElement() {

}

Render::MaterialElement::~MaterialElement() {
	Clear();
}

void Render::MaterialElement::AddTexture(Resource::Image::PTR pImage) {
	if(pImage != nullptr)
		m_vecTexture.push_back(new Texture(m_vecTexture.size(), pImage));
}

void Render::MaterialElement::Bind(Render::RenderingParameters& rp) const {
	for(auto tex : m_vecTexture){
		tex->Bind(rp);
	}
}

void Render::MaterialElement::Clear() {
	for(auto p : m_vecTexture){
		SAFE_DELETE(p);
	}
}
