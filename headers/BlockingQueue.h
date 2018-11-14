#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <string>
#include <condition_variable>

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
	
private:
	mutex lock; // c++11 lock
	condition_variable itemAdded; // C++11 CV
	condition_variable itemRemoved; // C++11 CV

    vector<int> items;

    int front;
    int nextEmpty;
	const int maxItems = 25; // Change this value for different queue sizes
};