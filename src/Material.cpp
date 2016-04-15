//
// Created by inosphe on 2016. 4. 12..
//

#include "Material.h"
#include "MaterialElement.h"

Render::Material::~Material() {
	Clear();
}

Render::MaterialElement &Render::Material::AddElement() {
	MaterialElement* pElement = new MaterialElement();
	m_vecElements.push_back(pElement);
	return *pElement;
}

void Render::Material::Bind(Render::RenderingParameters& rp) const{
	for(const auto e : m_vecElements){
		e->Bind(rp);
	}
}

void Render::Material::Clear() {
	for(auto p : m_vecElements){
		SAFE_DELETE(p);
	}
}
