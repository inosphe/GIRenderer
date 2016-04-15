//
// Created by inosphe on 2016. 4. 14..
//

#include "NanoGUIImplementation.h"
#include <nanogui/nanogui.h>
#include <iostream>
#include <map>

using std::cout;
using std::cerr;
using std::endl;
using namespace nanogui;

static std::map<GLFWwindow*, NanoGUIImplementation*> mapCallbackDelegate;

NanoGUIImplementation::NanoGUIImplementation()
: nanogui::Screen()
{

}

NanoGUIImplementation::~NanoGUIImplementation() {

}

void NanoGUIImplementation::Init(GLFWwindow* pWindow) {
	mapCallbackDelegate[pWindow] = this;
	initialize(pWindow, true);
	InitCallbacks(pWindow);
//	InitLayout();
	InitLayout2();
}

void NanoGUIImplementation::InitLayout() {
	Window *window = new Window(this, "Button demo");
	window->setPosition(Vector2i(15, 15));
	window->setLayout(new GroupLayout());

	/* No need to store a pointer, the data structure will be automatically
	   freed when the parent window is deleted */
	new Label(window, "Push buttons", "sans-bold");

	Button *b = new Button(window, "Plain button");
	b->setCallback([] { cout << "pushed!" << endl; });
	b = new Button(window, "Styled", ENTYPO_ICON_ROCKET);
	b->setBackgroundColor(Color(0, 0, 255, 25));
	b->setCallback([] { cout << "pushed!" << endl; });

	new Label(window, "Toggle buttons", "sans-bold");
	b = new Button(window, "Toggle me");
	b->setFlags(Button::ToggleButton);
	b->setChangeCallback([](bool state) { cout << "Toggle button state: " << state << endl; });

	new Label(window, "Radio buttons", "sans-bold");
	b = new Button(window, "Radio button 1");
	b->setFlags(Button::RadioButton);
	b = new Button(window, "Radio button 2");
	b->setFlags(Button::RadioButton);

	new Label(window, "A tool palette", "sans-bold");
	Widget *tools = new Widget(window);
	tools->setLayout(new BoxLayout(Orientation::Horizontal,
	                               Alignment::Middle, 0, 6));

	b = new ToolButton(tools, ENTYPO_ICON_CLOUD);
	b = new ToolButton(tools, ENTYPO_ICON_FF);
	b = new ToolButton(tools, ENTYPO_ICON_COMPASS);
	b = new ToolButton(tools, ENTYPO_ICON_INSTALL);

	new Label(window, "Popup buttons", "sans-bold");
	PopupButton *popupBtn = new PopupButton(window, "Popup", ENTYPO_ICON_EXPORT);
	Popup *popup = popupBtn->popup();
	popup->setLayout(new GroupLayout());
	new Label(popup, "Arbitrary widgets can be placed here");
	new CheckBox(popup, "A check box");
	popupBtn = new PopupButton(popup, "Recursive popup", ENTYPO_ICON_FLASH);
	popup = popupBtn->popup();
	popup->setLayout(new GroupLayout());
	new CheckBox(popup, "Another check box");

	window = new Window(this, "Basic widgets");
	window->setPosition(Vector2i(200, 15));
	window->setLayout(new GroupLayout());

	new Label(window, "Message dialog", "sans-bold");
	tools = new Widget(window);
	tools->setLayout(new BoxLayout(Orientation::Horizontal,
	                               Alignment::Middle, 0, 6));
	b = new Button(tools, "Info");
	b->setCallback([&] {
		auto dlg = new MessageDialog(this, MessageDialog::Type::Information, "Title", "This is an information message");
		dlg->setCallback([](int result) { cout << "Dialog result: " << result << endl; });
	});
	b = new Button(tools, "Warn");
	b->setCallback([&] {
		auto dlg = new MessageDialog(this, MessageDialog::Type::Warning, "Title", "This is a warning message");
		dlg->setCallback([](int result) { cout << "Dialog result: " << result << endl; });
	});
	b = new Button(tools, "Ask");
	b->setCallback([&] {
		auto dlg = new MessageDialog(this, MessageDialog::Type::Warning, "Title", "This is a question message", "Yes", "No", true);
		dlg->setCallback([](int result) { cout << "Dialog result: " << result << endl; });
	});

	std::vector<std::pair<int, std::string>>
			icons = loadImageDirectory(mNVGContext, "resources/icons");

	new Label(window, "Image panel & scroll panel", "sans-bold");
	PopupButton *imagePanelBtn = new PopupButton(window, "Image Panel");
	imagePanelBtn->setIcon(ENTYPO_ICON_FOLDER);
	popup = imagePanelBtn->popup();
	VScrollPanel *vscroll = new VScrollPanel(popup);
	ImagePanel *imgPanel = new ImagePanel(vscroll);
	imgPanel->setImages(icons);
	popup->setFixedSize(Vector2i(245, 150));

	auto img_window = new Window(this, "Selected image");
	img_window->setPosition(Vector2i(675, 15));
	img_window->setLayout(new GroupLayout());

	auto img = new ImageView(img_window);
	img->setPolicy(ImageView::SizePolicy::Expand);
	img->setFixedSize(Vector2i(300, 300));
	img->setImage(icons[0].first);
	imgPanel->setCallback([&, img, imgPanel, imagePanelBtn](int i) {
		img->setImage(imgPanel->images()[i].first); cout << "Selected item " << i << endl;
	});
	auto img_cb = new CheckBox(img_window, "Expand",
	                           [img](bool state) { if (state) img->setPolicy(ImageView::SizePolicy::Expand);
	                           else       img->setPolicy(ImageView::SizePolicy::Fixed); });
	img_cb->setChecked(true);

	new Label(window, "File dialog", "sans-bold");
	tools = new Widget(window);
	tools->setLayout(new BoxLayout(Orientation::Horizontal,
	                               Alignment::Middle, 0, 6));
	b = new Button(tools, "Open");
	b->setCallback([&] {
		cout << "File dialog result: " << file_dialog(
				{ {"png", "Portable Network Graphics"}, {"txt", "Text file"} }, false) << endl;
	});
	b = new Button(tools, "Save");
	b->setCallback([&] {
		cout << "File dialog result: " << file_dialog(
				{ {"png", "Portable Network Graphics"}, {"txt", "Text file"} }, true) << endl;
	});

	new Label(window, "Combo box", "sans-bold");
	new ComboBox(window, { "Combo box item 1", "Combo box item 2", "Combo box item 3"});
	new Label(window, "Check box", "sans-bold");
	CheckBox *cb = new CheckBox(window, "Flag 1",
	                            [](bool state) { cout << "Check box 1 state: " << state << endl; }
	);
	cb->setChecked(true);
	cb = new CheckBox(window, "Flag 2",
	                  [](bool state) { cout << "Check box 2 state: " << state << endl; }
	);
	new Label(window, "Progress bar", "sans-bold");
	auto mProgress = new ProgressBar(window);

	new Label(window, "Slider and text box", "sans-bold");

	Widget *panel = new Widget(window);
	panel->setLayout(new BoxLayout(Orientation::Horizontal,
	                               Alignment::Middle, 0, 20));

	Slider *slider = new Slider(panel);
	slider->setValue(0.5f);
	slider->setFixedWidth(80);

	TextBox *textBox = new TextBox(panel);
	textBox->setFixedSize(Vector2i(60, 25));
	textBox->setValue("50");
	textBox->setUnits("%");
	slider->setCallback([textBox](float value) {
		textBox->setValue(std::to_string((int) (value * 100)));
	});
	slider->setFinalCallback([&](float value) {
		cout << "Final slider value: " << (int) (value * 100) << endl;
	});
	textBox->setFixedSize(Vector2i(60,25));
	textBox->setFontSize(20);
	textBox->setAlignment(TextBox::Alignment::Right);

	window = new Window(this,"Misc. widgets");
	window->setPosition(Vector2i(425,15));
	window->setLayout(new GroupLayout());
	new Label(window,"Color wheel","sans-bold");
	new ColorWheel(window);
	new Label(window, "Function graph", "sans-bold");
	Graph *graph = new Graph(window, "Some function");
	graph->setHeader("E = 2.35e-3");
	graph->setFooter("Iteration 89");
	VectorXf &func = graph->values();
	func.resize(100);
	for (int i = 0; i < 100; ++i)
		func[i] = 0.5f * (0.5f * std::sin(i / 10.f) +
		                  0.5f * std::cos(i / 23.f) + 1);

	window = new Window(this, "Grid of small widgets");
	window->setPosition(Vector2i(425, 288));
	GridLayout *layout =
			new GridLayout(Orientation::Horizontal, 2,
			               Alignment::Middle, 15, 5);
	layout->setColAlignment(
			{ Alignment::Maximum, Alignment::Fill });
	layout->setSpacing(0, 10);
	window->setLayout(layout);

	{
		new Label(window, "Floating point :", "sans-bold");
		textBox = new TextBox(window);
		textBox->setEditable(true);
		textBox->setFixedSize(Vector2i(100, 20));
		textBox->setValue("50");
		textBox->setUnits("GiB");
		textBox->setDefaultValue("0.0");
		textBox->setFontSize(16);
		textBox->setFormat("[-]?[0-9]*\\.?[0-9]+");
	}

	{
		new Label(window, "Positive integer :", "sans-bold");
		textBox = new TextBox(window);
		textBox->setEditable(true);
		textBox->setFixedSize(Vector2i(100, 20));
		textBox->setValue("50");
		textBox->setUnits("Mhz");
		textBox->setDefaultValue("0.0");
		textBox->setFontSize(16);
		textBox->setFormat("[1-9][0-9]*");
	}

	{
		new Label(window, "Checkbox :", "sans-bold");

		cb = new CheckBox(window, "Check me");
		cb->setFontSize(16);
		cb->setChecked(true);
	}

	new Label(window, "Combo box :", "sans-bold");
	ComboBox *cobo =
			new ComboBox(window, { "Item 1", "Item 2", "Item 3" });
	cobo->setFontSize(16);
	cobo->setFixedSize(Vector2i(100,20));

	new Label(window, "Color button :", "sans-bold");
	popupBtn = new PopupButton(window, "", 0);
	popupBtn->setBackgroundColor(Color(255, 120, 0, 255));
	popupBtn->setFontSize(16);
	popupBtn->setFixedSize(Vector2i(100, 20));
	popup = popupBtn->popup();
	popup->setLayout(new GroupLayout());

	ColorWheel *colorwheel = new ColorWheel(popup);
	colorwheel->setColor(popupBtn->backgroundColor());

	Button *colorBtn = new Button(popup, "Pick");
	colorBtn->setFixedSize(Vector2i(100, 25));
	Color c = colorwheel->color();
	colorBtn->setBackgroundColor(c);

	colorwheel->setCallback([colorBtn](const Color &value) {
		colorBtn->setBackgroundColor(value);
	});

	colorBtn->setChangeCallback([colorBtn, popupBtn](bool pushed) {
		if (pushed) {
			popupBtn->setBackgroundColor(colorBtn->backgroundColor());
			popupBtn->setPushed(false);
		}
	});

	performLayout(mNVGContext);
}

void NanoGUIImplementation::InitCallbacks(GLFWwindow *pWindow) {
//	glfwSetCharCallback(pWindow, &NanoGUIImplementation::OnCharCallback);
	glfwSetDropCallback(pWindow, &NanoGUIImplementation::OnDropCallback);

	/* React to framebuffer size events -- includes window
	   size events and also catches things like dragging
	   a window from a Retina-capable screen to a normal
	   screen on Mac OS X */
	glfwSetFramebufferSizeCallback(mGLFWWindow, &NanoGUIImplementation::OnFrameBufferSizeCallback);
}

void NanoGUIImplementation::OnCharCallback(GLFWwindow *w, unsigned int codepoint) {
	mapCallbackDelegate[w]->charCallbackEvent(codepoint);
}

void NanoGUIImplementation::OnDropCallback(GLFWwindow *w, int count, const char **filenames) {
	mapCallbackDelegate[w]->dropCallbackEvent(count, filenames);
}


void NanoGUIImplementation::OnFrameBufferSizeCallback(GLFWwindow *w, int width, int height) {
	mapCallbackDelegate[w]->resizeCallbackEvent(width, height);
}

enum test_enum {
	Item1 = 0,
	Item2,
	Item3
};

void NanoGUIImplementation::InitLayout2() {
	FormHelper *gui = new FormHelper(this);
	ref<Window> window = gui->addWindow(Eigen::Vector2i(0, 0), "Form helper example");
	window->setWidth(200);

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

	this->setVisible(true);
	this->performLayout();
//	window->center();
}
