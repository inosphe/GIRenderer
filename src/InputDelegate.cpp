//
// Created by inosphe on 2016. 4. 14..
//

#include <string.h>
#include "InputDelegate.h"

namespace Core{
	InputDelegate::InputDelegate() {
		for(int i=(int)INPUT_TYPE::INIT ; i<(int)INPUT_TYPE::COUNT; ++i)
			m_enabled[i] = true;
	}


	InputDelegate::~InputDelegate() {

	}

	void InputDelegate::SetEnable(InputDelegate::INPUT_TYPE type, bool enabled) {
		m_enabled[(int)type] = enabled;
	}
}
