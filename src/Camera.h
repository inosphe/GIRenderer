//
// Created by inosphe on 2016. 4. 5..
//

#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include <glm/vec3.hpp>
#include "GameObject.h"

namespace Render{

	class Camera : public GameObject {
	public:
		Camera();
		virtual ~Camera();

		void Init();

		const glm::mat4 GetViewProj();
		const glm::mat4 GetView();

	private:
	};
}


#endif //PROJECT_CAMERA_H
