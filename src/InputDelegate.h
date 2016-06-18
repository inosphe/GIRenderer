//
// Created by inosphe on 2016. 4. 14..
//

#ifndef PROJECT_INPUTDELEGATE_H
#define PROJECT_INPUTDELEGATE_H

namespace Core{

	class InputDelegate {
	public:
		InputDelegate();
		virtual ~InputDelegate();

		enum INPUT_TYPE{
			INIT = 0
			, MOUSE_POS = INIT
			, MOUSE_BUTTON
			, KEY_PRESS
			, KEY_REPEAT
			, KEY_RELEASE
			, SCROLL
			, COUNT
		};
	public:
		virtual bool OnMousePos(int x, int y){return false;}
		virtual bool OnMouseButton(int button, int action, int modifier){return false;}
		virtual bool OnKeyPress(int key, int scancode, int mods){return false;}
		virtual bool OnKeyRepeat(int key, int scancode, int mods){return false;}
		virtual bool OnKeyRelease(int key, int scancode, int mods){return false;}
		virtual bool OnScroll(double x, double y){return false;}

		void SetEnable(INPUT_TYPE type, bool enabled);
		inline bool IsEnabled(INPUT_TYPE type){return m_enabled[(int)type];}

	private:
		bool m_enabled[INPUT_TYPE::COUNT];
	};
}

#endif //PROJECT_INPUTDELEGATE_H
