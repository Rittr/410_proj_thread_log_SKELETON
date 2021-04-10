/*
 * Logger.cpp
 *
 *  Created on: Mar 29, 2021
 *      Author: keith
 */
#include <iostream>
#include "../includes/Logger.h"
using namespace std;

//class Logger {
	/***
	 * creates a logger object, if lt=FILE then log to the file given by fn
	 * if lt=LOG_CONSOLE the send log info to console via cout
	 * @param lt either LOG_FILE or LOG_CONSOLE
	 * @param fn if above is LOG_FILE then this is where info logged to
	 *           otherwise it is not used
	 */
	Logger::Logger(LOG_TYPE lt, string fn) {  //Logger(LOG_TYPE lt, std::string fn=FILENAME);
		this->lt = lt;
		this->fn = fn;
		this->fs = (lt == LOG_FILE) ? ofstream(fn) : NULL;
//		this->mtx = mutex;
	}


	/***
	 * Information to log, either to a file or to console
	 * @param info to log
	 */
	void Logger::Log(string info) {
		// TODO: log info here
		mtx.lock();
		if (lt == LOG_FILE) {
			fs << info << endl;
		}
		else {
			cout << info << endl;
		}
		mtx.unlock();
	}

	/***
		 * close any open streams
		 */
	Logger::~Logger(){
		mtx.unlock();
		if (fs.is_open()) {
			fs.close();
		}
	}


//	LOG_TYPE lt;
//	//if using LOG_TYPE::LOG_FILE then fn is the file where info is written,
//	//and fs is the stream used to access it.  Otherwise both ignored
//	std::string fn;
//	std::ofstream fs;
//
//	//used to make instance of this class threadsafe
//	std::mutex mtx;
//};
