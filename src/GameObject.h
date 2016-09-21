//
// Created by inosphe on 2016. 6. 18..
//

#ifndef PROJECT_GAMEOBJECT_H
#define PROJECT_GAMEOBJECT_H

#include "common_header.h"
#include "IMovableObject.h"

namespace Render{
	class IModel;
	class ShaderParam;
}

class GameObject : public IMovableObject{
public:
	enum Type{
		Camera = 0
		, Light
		, Entity
	};
	typedef std::shared_ptr<GameObject> PTR;

public:
	GameObject();
	GameObject(Type type);
	GameObject(Type type, Render::IModel* pModel);
	virtual ~GameObject();

	void SetName(const string& strName);
	const string& GetName(){return m_strName;}

	void Render(Render::ShaderParam& shader);
	void Update(int ms);

	inline void SetType(Type type){m_eType = type;}
	inline Type GetType(){return m_eType;}

	const glm::mat4 GetViewProj() const;

public:
	const unsigned int m_ID = 0;

protected:
	Render::IModel* m_pModel = nullptr;
	string m_strName;
	Type m_eType;

public:
	static int Counter;
};


#endif //PROJECT_GAMEOBJECT_H
