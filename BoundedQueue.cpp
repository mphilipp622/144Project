#include "BoundedQueue.h"

BoundedQueue::BoundedQueue()
{
	front = nextEmpty = 0;
	
	for(int i = 0; i < maxItems; i++)
		items.push_back(0);
}

BoundedQueue::~BoundedQueue()
{
	
}

bool BoundedQueue::TryInsert(int item)
{
	bool success = false;
	
	lock.lock();
	
	if((nextEmpty - front) < maxItems)
	{
		items.at(nextEmpty % maxItems) = item;
		nextEmpty++;
		
		string message = "Queue has " + to_string(nextEmpty - front) + " Items in it\n";
		cout << message;
		success = true;
	}
	
	lock.unlock();
	
	return success;
}

bool BoundedQueue::TryRemove(int *item)
{
	bool success = false;
	
	lock.lock();
	
	if(front < nextEmpty)
	{
		*item = items.at(front % maxItems);
		front++;
		string message = "Queue has " + to_string(nextEmpty - front) + " Items in it\n";
		cout << message;
		
		success = true;
	}
	
	lock.unlock();
	
	return success;
}