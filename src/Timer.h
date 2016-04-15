//
// Created by inosphe on 2016. 4. 13..
//

#ifndef PROJECT_TIMER_H
#define PROJECT_TIMER_H

#include <chrono>

namespace Core{
	class Timer {
	public:
		void Init();
		void Update();
		int GetDelta();

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_time[2];
	};
}



#endif //PROJECT_TIMER_H
