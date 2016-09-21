//
// Created by inosphe on 2016. 6. 18..
//

#include "Light.h"

Light::Light():GameObject(GameObject::Type::Light) {
	string name = "Light";
	name += m_ID;
	SetName(name);
}

Light::~Light() {

}
