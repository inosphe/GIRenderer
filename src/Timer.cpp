//
// Created by inosphe on 2016. 4. 13..
//

#include "Timer.h"

namespace Core{
	void Timer::Init() {
		m_time[0] = m_time[1] = std::chrono::high_resolution_clock::now();
	}

	void Timer::Update() {
		m_time[0] = m_time[1];
		m_time[1] = std::chrono::high_resolution_clock::now();
	}

	int Timer::GetDelta() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_time[1] - m_time[0]).count();
	}
}
