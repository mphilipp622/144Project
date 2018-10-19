#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class BoundedQueue
{
public:
	BoundedQueue();
	~BoundedQueue();
	
	bool TryInsert(int item);
	bool TryRemove(int *item);
	
private:
	mutex lock; // C++11 lock
	
	vector<int> items;
	
	int front;
	int nextEmpty;
	const int maxItems = 100; // Change this value for different queue sizes
};