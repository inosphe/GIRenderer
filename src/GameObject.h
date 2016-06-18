//
// Created by inosphe on 2016. 6. 18..
//

#ifndef PROJECT_GAMEOBJECT_H
#define PROJECT_GAMEOBJECT_H

#include "common_header.h"
#include "IMovableObject.h"

namespace Render{
	class IModel;
	class RenderingParameters;
}

class GameObject : public IMovableObject{
public:
	GameObject();
	GameObject(Render::IModel* pModel);
	virtual ~GameObject();

	void SetName(const string& strName);
	const string& GetName(){return m_strName;}

	void Render(Render::RenderingParameters& rp);
	void Update(int ms);

protected:
	Render::IModel* m_pModel = nullptr;
	string m_strName;

public:
	static int Counter;
};


#endif //PROJECT_GAMEOBJECT_H
