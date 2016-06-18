//
// Created by inosphe on 2016. 4. 6..
//

#ifndef PROJECT_ISCENE_H
#define PROJECT_ISCENE_H

#include <memory>
#include "Application.h"
#include "GameObject.h"

namespace Render{
	class Camera;
	class RenderingParameters;
}

class IScene {
public:
	IScene(Core::Application& app);
	virtual void Init(){}
	virtual void Update(int ms);
	virtual void Render(Render::RenderingParameters& rp);

	typedef std::vector<std::shared_ptr<GameObject>> container;

	inline std::shared_ptr<Render::Camera> GetMainCamera(){return m_pMainCamera;}
	inline container& GetObjects(){return m_gameObjects;}

protected:
	std::shared_ptr<Render::Camera> m_pMainCamera = nullptr;
	Core::Application& m_app;
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;
};


#endif //PROJECT_ISCENE_H
