#include "../headers/BlockingQueue.h"

const int BlockingQueue::maxItems = 25; // Change this for different queue sizes

BlockingQueue::BlockingQueue()
{
	front = nextEmpty = 0;
	
	// initialize the vector with 0's.	
	for(int i = 0; i < maxItems; i++)
		items.push_back(0);
}

BlockingQueue::~BlockingQueue()
{
}

void BlockingQueue::Insert(int item, int threadID)
{
	// acquire lock
	unique_lock<mutex> uniqueLock(lock);
	
	// If queue is full, have producer wait for consumer to remove something
	while((nextEmpty - front) == maxItems)
	{
		// Print waiting message
		string message = "Producer " + to_string(threadID) + " Waiting to Produce\n\n";
		cout << message;

		// Force this thread to wait for another thread to notify it
		itemRemoved.wait(uniqueLock);
	}
	
	// Add the item to the queue
	items.at(nextEmpty % maxItems) = item;
	
	// Increment next index
	nextEmpty++;

	// print success message
	string message = to_string(item) + " produced by producer " + to_string(threadID) + "\n\n";
	cout << message; 
	
	// release lock
	uniqueLock.unlock();

	// According to C++ std::condition_variable documentation:
	// Manual unlocking is done before notifying, to avoid an edge case where
	// Thsi thread wakes up and blocks again instantly

	// Notify a waiting consumer
	itemAdded.notify_one();
}

void BlockingQueue::Remove(int threadID)
{
	int item = 0; // this will be given a value and returned
	
	// Acquire lock
	unique_lock<mutex> uniqueLock(lock);
	
	// If there is nothing in the queue, tell consumer to wait for producer to add something
	while(front == nextEmpty)
	{
		// Print waiting message
		string message = "Consumer " + to_string(threadID) + " Waiting to Consume\n\n";
		cout << message;

		// force this thread to wait for a notification from another thread
		itemAdded.wait(uniqueLock);
	}
	
	// Get item from queue
	item = items.at(front % maxItems);

	// free up a spot in the queue
	front++;

	string message = to_string(item) + " consumed by consumer " + to_string(threadID) + "\n\n";
	cout << message; // output success message

	// release lock
	uniqueLock.unlock();

	// According to C++ std::condition_variable documentation:
	// Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again

	// Notify any waiting producers that there's a space free in the queue.
	itemRemoved.notify_one();
	
	// Return the item
}

float BlockingQueue::GetPercentageFull()
{
	// returns how full the queue is as a float between 0 - 1.0. Multiply by 100 to get percentage
    return (nextEmpty - front) / (float) maxItems; 
}