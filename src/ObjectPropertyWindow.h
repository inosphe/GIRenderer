//
// Created by inosphe on 2016. 6. 18..
//

#ifndef PROJECT_OBJECTPROPERTYWINDOW_H
#define PROJECT_OBJECTPROPERTYWINDOW_H

#include <nanogui/screen.h>
#include "common_header.h"
#include "GameObject.h"

class ObjectPropertyWindow {
public:
	ObjectPropertyWindow(nanogui::Screen* pParent);
	virtual ~ObjectPropertyWindow();

	typedef std::vector<std::shared_ptr<GameObject>> container;

	void Init();
	void SetObjects(container& objects);

protected:
	nanogui::Screen* m_pParent = nullptr;
	nanogui::ComboBox* m_pCombobox = nullptr;
};


#endif //PROJECT_OBJECTPROPERTYWINDOW_H
