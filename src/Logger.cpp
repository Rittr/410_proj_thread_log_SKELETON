/*
 * Logger.cpp
 *
 *  Created on: Mar 29, 2021
 *      Author: keith & Chris Ritter
 */
#include <iostream>
#include "../includes/Logger.h"
using namespace std;

Logger::Logger(LOG_TYPE lt, string fn) {
		lock_guard<mutex> lock(mtx);
		this->lt = lt;
		this->fn = fn;
		if (lt == LOG_FILE){
			fs = ofstream(fn);
		}
	}

void Logger::Log(string info) {
		lock_guard<mutex> lock(mtx);
		if (lt == LOG_FILE) {
			fs << info << endl;
		}
		else {
			cout << info << endl;
		}
	}

Logger::~Logger(){
		if (fs.is_open()) {
			fs.close();
		}
	}
