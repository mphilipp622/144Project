#include "../headers/BlockingQueue.h"

BlockingQueue::BlockingQueue()
{
	front = nextEmpty = 0;
	maxItems = 10;
	
	for(int i = 0; i < maxItems; i++)
		items.push_back(0);
}

BlockingQueue::~BlockingQueue()
{
	
}

void BlockingQueue::Insert(int item)
{
	unique_lock<mutex> uniqueLock(lock);
	
	while((nextEmpty - front) == maxItems)
		itemRemoved.wait(uniqueLock);
	
	items.at(nextEmpty % maxItems) = item;
	
	nextEmpty++;
	
	itemAdded.notify_one();
	
	uniqueLock.release();
}

int BlockingQueue::Remove()
{
	int item = 0;
	
	unique_lock<mutex> uniqueLock(lock);
	
	while(front == nextEmpty)
		itemAdded.wait(uniqueLock);
	
	item = items.at(front % maxItems);
	front++;
	
	itemRemoved.notify_one();
	uniqueLock.release();
	
	return item;
}