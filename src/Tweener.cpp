//
// Created by inosphe on 2016. 9. 21..
//

#include "Tweener.h"

Tweener::Tweener(glm::vec3 v0, glm::vec3 v1, float time):m_v0(v0), m_v1(v1), m_time(time) {

}

void Tweener::Update(float dt) {
	m_t += dt;
	if(m_t >= m_time)
		m_t -= m_time;
}

glm::vec3 Tweener::GetValue() {
	float t = m_t/m_time;
	return m_v0 + (m_v1-m_v0)*t;
}
