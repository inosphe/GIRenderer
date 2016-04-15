//
// Created by inosphe on 2016. 4. 3..
//

#ifndef PROJECT_EXCEPTION_H
#define PROJECT_EXCEPTION_H

#include "common_header.h"

namespace Core{
	struct Exception{
		Exception(const string& _message):message(_message){}

		string message;
	};
}

#endif //PROJECT_EXCEPTION_H
