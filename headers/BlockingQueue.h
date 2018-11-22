#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <string>
#include <condition_variable>
#include <fstream>

using namespace std;

class BlockingQueue
{
public:
	BlockingQueue();
	~BlockingQueue();
	
	void Insert(int item, int threadID);
	void Remove(int threadID);
	
	// Returns how full the queue is as a percentage
	float GetPercentageFull();

	static const int maxItems; // Has to be static for proper object-oriented implementation. Change in BlockingQueue.cpp
	
private:
	mutex lock; // c++11 lock
	condition_variable itemAdded; // C++11 CV
	condition_variable itemRemoved; // C++11 CV

    vector<int> items;	// Holds the items that are currently in the queue.

	// Circular array data.
    int front;
    int nextEmpty;
};