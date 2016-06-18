//
// Created by inosphe on 2016. 6. 18..
//

#include "ObjectPropertyWindow.h"
#include <nanogui/nanogui.h>
#include <iostream>
#include <map>
#include <Logger.h>

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
	FormHelper *gui = new FormHelper(m_pParent);
	ref<Window> window = gui->addWindow(Eigen::Vector2i(0, 0), "Object property");
	window->setWidth(200);
//	window->setLayout(new GridLayout(Orientation::Horizontal, 2, Alignment::Middle, 0, 20));
//	window->setLayout(new BoxLayout(Orientation::Vertical, Alignment::Middle, 0, 20));

	ComboBox* pCombobox = new ComboBox(window);
	AdvancedGridLayout* layout = gui->layout().get();
	layout->appendRow(0);
	layout->setAnchor(pCombobox, AdvancedGridLayout::Anchor(1, layout->rowCount()-1, 3, 1));
	pCombobox->setChangeCallback([](bool b){
		Logger::Debug("on click");
	});
	pCombobox->setCallback([](bool b){
		Logger::Debug("on changed");
	});

	m_pCombobox = pCombobox;

	gui->addGroup("Basic types");
	bool b = true;
	gui->addVariable("bool", b);
	string str = "test";
	gui->addVariable("string", str);

	gui->addGroup("Validating fields");
	static int i = 1;
	gui->addVariable("int", i);
	static float f = 2.3f;
	gui->addVariable("float", f);
	static double d = 4.9;
	gui->addVariable("double", d);

	gui->addGroup("Complex types");
	static test_enum e = Item1;
	gui->addVariable("Enumeration", e, true)
		->setItems({"Item 1", "Item 2", "Item 3"});

	static nanogui::Color c(0.7f, 0.2f, 0.5f, 1.0f);
	gui->addVariable("Color", c);

	gui->addGroup("Other widgets");
	gui->addButton("A button", [](){ std::cout << "Button pressed." << std::endl; });

	m_pParent->setVisible(true);
	m_pParent->performLayout();
//	window->center();
}

void ObjectPropertyWindow::SetObjects(ObjectPropertyWindow::container &objects) {
	std::vector<string> items;
	for(auto obj: objects){
		items.push_back(obj->GetName());
	}
	m_pCombobox->setItems(items);
	m_pParent->performLayout();
}
