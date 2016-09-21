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
	virtual void Render(Render::ShaderParam& shader);

	typedef std::vector<GameObject::PTR> CONTAINER;

	inline std::shared_ptr<Render::Camera> GetMainCamera(){return m_pMainCamera;}
	inline CONTAINER& GetObjects(){return m_vecObjects;}
	inline CONTAINER& GetEntities(){return m_vecEntities;}
	inline CONTAINER& GetLights(){return m_vecLights;}

	void AddGameObject(GameObject::PTR pObject);

protected:
	std::shared_ptr<Render::Camera> m_pMainCamera = nullptr;
	Core::Application& m_app;

	CONTAINER m_vecEntities;
	CONTAINER m_vecLights;
	CONTAINER m_vecObjects;
};


#endif //PROJECT_ISCENE_H
