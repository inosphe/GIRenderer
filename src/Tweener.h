//
// Created by inosphe on 2016. 9. 21..
//

#ifndef PROJECT_TWEENER_H
#define PROJECT_TWEENER_H


#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

class Tweener {
public:
	Tweener(glm::vec3 v0, glm::vec3 v1, float time);

	void Update(float dt);
	glm::vec3 GetValue();

	glm::vec3 m_v0, m_v1;
	float m_time;
	float m_t = 0.0f;
};


#endif //PROJECT_TWEENER_H
