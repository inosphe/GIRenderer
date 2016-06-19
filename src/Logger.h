//
// Created by inosphe on 2016. 4. 1..
//

#ifndef PROJECT_LOGGER_H
#define PROJECT_LOGGER_H

#include "common_header.h"

class Logger {
public:
	static void Debug(const char* szMessage);
	static void Debug(const string& str);
	static void Error(const char* szMessage);
	static void Error(const string& str);
};


#endif //PROJECT_LOGGER_H
