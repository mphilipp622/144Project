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
	
	lock.lock(); // C++11 lock
	
	if((nextEmpty - front) < maxItems)
	{
		items.at(nextEmpty % maxItems) = item;
		nextEmpty++;

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
		
		success = true;
	}
	
	lock.unlock();
	
	return success;
}