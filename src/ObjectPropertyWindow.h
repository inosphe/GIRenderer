//
// Created by inosphe on 2016. 6. 18..
//

#ifndef PROJECT_OBJECTPROPERTYWINDOW_H
#define PROJECT_OBJECTPROPERTYWINDOW_H

#include <nanogui/screen.h>
#include "common_header.h"
#include "GameObject.h"

namespace nanogui{
	class FormHelper;
}

template <class C, typename T>
struct PropertyValue{
	void SetTarget(std::shared_ptr<C> _target){
		target = _target;
	}

	void Set(T v){if(target)setter(target.get(), v);}
	T Get(){if(target)return getter(target.get());else return 0;}

	std::function<void(C*, T)> setter;
	std::function<T(C*)> getter;

	std::shared_ptr<C> target;
	T C::*member;
};

class ObjectPropertyWindow {
public:
	ObjectPropertyWindow(nanogui::Screen* pParent);
	virtual ~ObjectPropertyWindow();

	typedef std::vector<std::shared_ptr<GameObject>> container;

	void Init();
	void SetObjects(container& objects, int i);
	void Update();

	GameObject::PTR GetSelected();

protected:
	void SetObject(std::shared_ptr<GameObject> object);

protected:
	nanogui::Screen* m_pParent = nullptr;
	nanogui::ComboBox* m_pCombobox = nullptr;

	nanogui::FormHelper* m_pGUI = nullptr;

	PropertyValue<GameObject, float> prop_pos_x, prop_pos_y, prop_pos_z;
	PropertyValue<GameObject, float> prop_rot_x, prop_rot_y, prop_rot_z;

	container* m_pObjects = nullptr;
};


#endif //PROJECT_OBJECTPROPERTYWINDOW_H
