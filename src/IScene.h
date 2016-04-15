//
// Created by inosphe on 2016. 4. 6..
//

#ifndef PROJECT_ISCENE_H
#define PROJECT_ISCENE_H

#include <memory>
#include "Application.h"


namespace Render{
	class Camera;
	class RenderingParameters;
}

class IScene {
public:
	IScene(Core::Application& app);
	virtual void Init(){}
	virtual void Update(int ms) = 0;
	virtual void Render(Render::RenderingParameters& rp) = 0;

	inline std::shared_ptr<Render::Camera> GetMainCamera(){return m_pMainCamera;}

protected:
	std::shared_ptr<Render::Camera> m_pMainCamera = nullptr;
	Core::Application& m_app;
};


#endif //PROJECT_ISCENE_H
