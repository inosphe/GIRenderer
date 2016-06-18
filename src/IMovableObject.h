//
// Created by inosphe on 2016. 4. 5..
//

#ifndef PROJECT_IMOVABLEOBJECT_H
#define PROJECT_IMOVABLEOBJECT_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

class IMovableObject {
public:
	IMovableObject();
	virtual ~IMovableObject();

	virtual void Move(const glm::vec3& move);

	virtual void Up();
	virtual void Down();
	virtual void Left();
	virtual void Right();
	virtual void Stop();

	glm::vec3 Dir();

	virtual void Rotate(float tx, float ty);
	virtual void Update(int ms);

	void SetPosition(const glm::vec3& pos);
	void SetDirection(const glm::vec3& dir);
	glm::mat4x4 GetTransform();

protected:
	glm::vec3 m_vPosition;
	glm::quat m_qRotation;
	glm::vec3 m_vScale;
	glm::vec3 m_vVelocity;
};


#endif //PROJECT_IMOVABLEOBJECT_H
