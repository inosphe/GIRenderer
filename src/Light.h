//
// Created by inosphe on 2016. 6. 18..
//

#ifndef PROJECT_LIGHT_H
#define PROJECT_LIGHT_H

#include "GameObject.h"

class Light : public GameObject{
public:
	Light();
	virtual ~Light();

	inline void SetIntensity(float v){m_fIntensity = v;}
	inline float GetIntensity(){return m_fIntensity;}

protected:
	float m_fIntensity = 1.0;
};


#endif //PROJECT_LIGHT_H
