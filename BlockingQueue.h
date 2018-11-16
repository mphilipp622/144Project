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
	BlockingQueue(int consumerInterval, int producerInterval);
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
	const int maxItems = 50; // Change this value for different queue sizes

	ofstream output; // outputs data to csv file for easy graphing.
	int countFull, countEmpty;

	chrono::time_point<std::chrono::system_clock> startTime;

	void WriteDataToCSV();
};