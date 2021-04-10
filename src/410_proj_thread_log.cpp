//============================================================================
// Name        : 410_proj_thread_log.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <thread>
#include <iostream>
#include <vector>
#include "../includes/constants.h"
#include "../includes/Logger.h"

using namespace std;

//NOTE: you should have no mutexes in this file
//TODO linker errors?  Did you include the pthread library?   And set the proper dialect?
//TODO declare globals

Logger fileLogger(LOG_FILE); // console
Logger consoleLogger(LOG_CONSOLE); // file

int numThreads = thread::hardware_concurrency();
vector<thread> threadVector;

/***
 * TODO log info to both file and console You can do this with 2 Logger objects
 *            Note:  These logger objects cannot be local variables, they must be shared
 *            amongst the threads. (why?)
 * TODO this function should run until main (or another thread) asks it to quit
 * @param info  to log
 * returns void
 */
void fun(string info){
	fileLogger.Log(info);
	consoleLogger.Log(info);
}
int main() {
	
	//TODO start as many threads as you have cores (see std::thread::hardware_concurrency())
	//TODO save these threads in a vector

	for (int i=0; i<numThreads; i++){
		// start thread
		// add thread to vector
		threadVector.push_back(thread(fun,i));
	}


	//TODO let threads run a bit (5 seconds)
	this_thread::sleep_for(chrono::milliseconds(5000));
	
	//TODO ask them all to stop
	

	//TODO wait for all threads to finish
	for (int i=0; i<numThreads; i++){
			// stop thread
			threadVector[i].join();
		}
	
	return 0;
}
