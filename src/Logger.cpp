//
// Created by inosphe on 2016. 4. 1..
//

#include "Logger.h"
#include <iostream>

void Logger::Debug(const string& str){
	std::cout << str << std::endl;
}

void Logger::Debug(const char* szMessage){
	std::cout << szMessage << std::endl;
}

void Logger::Error(const string &str) {
	std::cerr << str << std::endl;
}

void Logger::Error(const char *szMessage) {
	std::cerr << szMessage << std::endl;
}
