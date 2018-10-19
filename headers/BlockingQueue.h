#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

class BlockingQueue
{
public:
	BlockingQueue();
	~BlockingQueue();
	
	void Insert(int item);
	int Remove();
	
private:
	mutex lock;
	condition_variable itemAdded;
	condition_variable itemRemoved;
	
	vector<int> items;
	
	int front;
	int nextEmpty;
	int maxItems;
};