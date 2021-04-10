//============================================================================
// Name        : 410_proj_thread_log.cpp
// Author      : Chris Ritter
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : example of threadsafe logging
//============================================================================
#include <thread>
#include <iostream>
#include <vector>
#include "../includes/constants.h"
#include "../includes/Logger.h"

using namespace std;

//NOTE: you should have no mutexes in this file
//linker errors?  Did you include the pthread library?   And set the proper dialect?
//declare globals

Logger fileLogger(LOG_FILE); // console
Logger consoleLogger(LOG_CONSOLE); // file

bool run = true;

int numThreads = thread::hardware_concurrency();
vector<thread> threadVector;

/***
 * log info to both file and console You can do this with 2 Logger objects
 *            Note:  These logger objects cannot be local variables, they must be shared
 *            amongst the threads. (why?)
 * this function runs until main asks it to quit
 * @param info  to log
 * returns void
 */
void fun(string info){
	while (run) {
		fileLogger.Log(info);
		consoleLogger.Log(info);
	}
}
int main() {
	
	//start as many threads as you have cores (see std::thread::hardware_concurrency())
	//save these threads in a vector

	for (int i=0; i<numThreads; i++){
		char threadInfo = 'a'+i;
		threadVector.push_back(thread(fun, string(5, threadInfo)));
	}


	//let threads run a bit (5 seconds)
	this_thread::sleep_for(chrono::milliseconds(5000));
	
	//ask them all to stop
	run = false;

	//wait for all threads to finish
	for (int i=0; i<numThreads; i++){
			threadVector[i].join();
		}
	
	return 0;
}
