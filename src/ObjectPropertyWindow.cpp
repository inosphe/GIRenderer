//
// Created by inosphe on 2016. 6. 18..
//

#include "ObjectPropertyWindow.h"
#include <nanogui/nanogui.h>
#include <iostream>
#include <map>
#include <Logger.h>
#include <functional>

using namespace nanogui;


enum test_enum {
	Item1 = 0,
	Item2,
	Item3
};


ObjectPropertyWindow::ObjectPropertyWindow(nanogui::Screen* pParent):m_pParent(pParent) {
	Init();
}

ObjectPropertyWindow::~ObjectPropertyWindow() {

}

void ObjectPropertyWindow::Init() {
	m_pGUI = new FormHelper(m_pParent);
	ref<Window> window = m_pGUI->addWindow(Eigen::Vector2i(0, 0), "Object property");
	window->setWidth(200);
	window->setHeight(400);
//	window->setLayout(new GridLayout(Orientation::Horizontal, 2, Alignment::Middle, 0, 20));
//	window->setLayout(new BoxLayout(Orientation::Vertical, Alignment::Middle, 0, 20));
	m_pGUI->setFixedSize(Eigen::Vector2i(80, 0));


	ComboBox* pCombobox = new ComboBox(window);
	AdvancedGridLayout* layout = m_pGUI->layout().get();
	layout->appendRow(0);
	layout->setAnchor(pCombobox, AdvancedGridLayout::Anchor(1, layout->rowCount()-1, 3, 1));
	pCombobox->setChangeCallback([](bool b){
	});
	pCombobox->setCallback([this](int i){
		SetObject((*m_pObjects)[i]);
		m_pGUI->refresh();
	});

	m_pCombobox = pCombobox;

	m_pGUI->addGroup("Position");
	prop_pos_x.setter = [](GameObject* p, float t){p->SetPositionElement(0, t);};
	prop_pos_x.getter = [](GameObject* p)->float{return p->GetPosition()[0];};
	m_pGUI->addVariable<float>("x"
			, std::bind(&PropertyValue<GameObject, float>::Set, std::ref(prop_pos_x), std::placeholders::_1)
			, std::bind(&PropertyValue<GameObject, float>::Get, &prop_pos_x)
			, true);
	prop_pos_y.setter = [](GameObject* p, float t){p->SetPositionElement(1, t);};
	prop_pos_y.getter = [](GameObject* p)->float{return p->GetPosition()[1];};
	m_pGUI->addVariable<float>("y"
			, std::bind(&PropertyValue<GameObject, float>::Set, std::ref(prop_pos_y), std::placeholders::_1)
			, std::bind(&PropertyValue<GameObject, float>::Get, &prop_pos_y)
			, true);
	prop_pos_z.setter = [](GameObject* p, float t){p->SetPositionElement(2, t);};
	prop_pos_z.getter = [](GameObject* p)->float{return p->GetPosition()[2];};
	m_pGUI->addVariable<float>("z"
			, std::bind(&PropertyValue<GameObject, float>::Set, std::ref(prop_pos_z), std::placeholders::_1)
			, std::bind(&PropertyValue<GameObject, float>::Get, &prop_pos_z)
			, true);

	m_pGUI->addGroup("Rotation");
	prop_rot_x.setter = [](GameObject* p, float t){p->SetEulerElement(0, t);};
	prop_rot_x.getter = [](GameObject* p)->float{return p->GetEuler()[0];};
	m_pGUI->addVariable<float>("x"
			, std::bind(&PropertyValue<GameObject, float>::Set, std::ref(prop_rot_x), std::placeholders::_1)
			, std::bind(&PropertyValue<GameObject, float>::Get, &prop_rot_x)
			, true);
	prop_rot_y.setter = [](GameObject* p, float t){p->SetEulerElement(1, t);};
	prop_rot_y.getter = [](GameObject* p)->float{return p->GetEuler()[1];};
	m_pGUI->addVariable<float>("y"
			, std::bind(&PropertyValue<GameObject, float>::Set, std::ref(prop_rot_y), std::placeholders::_1)
			, std::bind(&PropertyValue<GameObject, float>::Get, &prop_rot_y)
			, true);
	prop_rot_z.setter = [](GameObject* p, float t){p->SetEulerElement(2, t);};
	prop_rot_z.getter = [](GameObject* p)->float{return p->GetEuler()[2];};
	m_pGUI->addVariable<float>("z"
			, std::bind(&PropertyValue<GameObject, float>::Set, std::ref(prop_rot_z), std::placeholders::_1)
			, std::bind(&PropertyValue<GameObject, float>::Get, &prop_rot_z)
			, true);

//	m_pGUI->addGroup("Validating fields");
//	static int i = 1;
//	m_pGUI->addVariable("int", i);
//	static float f = 2.3f;
//	m_pGUI->addVariable("float", f);
//	static double d = 4.9;
//	m_pGUI->addVariable("double", d);
//
//	m_pGUI->addGroup("Complex types");
//	static test_enum e = Item1;
//	m_pGUI->addVariable("Enumeration", e, true)
//		->setItems({"Item 1", "Item 2", "Item 3"});
//
//	static nanogui::Color c(0.7f, 0.2f, 0.5f, 1.0f);
//	m_pGUI->addVariable("Color", c);
//
//	m_pGUI->addGroup("Other widgets");
//	m_pGUI->addButton("A button", [](){ std::cout << "Button pressed." << std::endl; });

	m_pParent->setVisible(true);
	m_pParent->performLayout();

//	window->center();
}

void ObjectPropertyWindow::SetObjects(ObjectPropertyWindow::container &objects, int i) {
	m_pObjects = &objects;

	std::vector<string> items;
	for(auto obj: (*m_pObjects)){
		items.push_back(obj->GetName());
	}
	m_pCombobox->setItems(items);
	m_pCombobox->setSelectedIndex(i);
	m_pParent->performLayout();

	i = m_pCombobox->selectedIndex();
	SetObject((*m_pObjects)[i]);
}

void ObjectPropertyWindow::Update() {
	m_pGUI->refresh();
}

void ObjectPropertyWindow::SetObject(std::shared_ptr<GameObject> object) {
	prop_pos_x.SetTarget(object);
	prop_pos_y.SetTarget(object);
	prop_pos_z.SetTarget(object);
	prop_rot_x.SetTarget(object);
	prop_rot_y.SetTarget(object);
	prop_rot_z.SetTarget(object);
}

GameObject::PTR ObjectPropertyWindow::GetSelected() {
	return (*m_pObjects)[m_pCombobox->selectedIndex()];
}
