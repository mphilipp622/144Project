#include "../headers/BlockingQueue.h"

const int BlockingQueue::maxItems = 100; // Change this for different queue sizes

BlockingQueue::BlockingQueue()
{
	front = nextEmpty = 0;
	
	// initialize the vector with 0's.	
	for(int i = 0; i < maxItems; i++)
		items.push_back(0);
}

BlockingQueue::BlockingQueue(int consumerInterval, int producerInterval) : BlockingQueue()
{
	output.open("data/" + to_string(maxItems) + "_" + to_string(producerInterval) + "_" + to_string(consumerInterval) + ".csv");
	output << ",capacity,countFull,countEmpty\n";
	output << to_string(0) + "," + to_string(GetPercentageFull() * 100) + "," + to_string(countFull) + "," + to_string(countEmpty) + "\n";


	startTime = chrono::system_clock::now();

	writeThread = thread(&BlockingQueue::WriteDataToCSV, this);
}

BlockingQueue::~BlockingQueue()
{
	output.close();	
}

void BlockingQueue::Insert(int item, int threadID)
{
	// acquire lock
	unique_lock<mutex> uniqueLock(lock);
	
	// If queue is full, have producer wait for consumer to remove something
	while((nextEmpty - front) == maxItems)
	{
		countFull++;
		string message = "Producer " + to_string(threadID) + " Waiting to Produce\n\n";
		cout << message;

		itemRemoved.wait(uniqueLock);
	}
	
	// Add the item to the queue
	items.at(nextEmpty % maxItems) = item;
	
	// Increment next index
	nextEmpty++;

	string message = to_string(item) + " produced by producer " + to_string(threadID) + "\n\n";
		
	cout << message; // print success message
	
	// release lock
	uniqueLock.unlock();

	// According to C++ std::condition_variable documentation:
	// Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again

	// Notify waiting consumers
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
		countEmpty++;
		string message = "Consumer " + to_string(threadID) + " Waiting to Consume\n\n";
		cout << message;

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
    return (nextEmpty - front) / (float) maxItems; // returns how full the queue is as a percentage
}

void BlockingQueue::WriteDataToCSV()
{
	chrono::time_point<std::chrono::system_clock> previousSecond = chrono::system_clock::now();
	while(true)
	{
		auto end = chrono::system_clock::now();
		chrono::duration<double> elapsed = end - startTime; // get total time elapsed elapsed = end - startTime;
		chrono::duration<double> elapsedSecond = end - previousSecond;

		int oneSecond = elapsedSecond.count();

		if(oneSecond >= 1)
		{
			output << to_string((int)elapsed.count()) + "," + to_string(GetPercentageFull() * 100) + "," + to_string(countFull) + "," + to_string(countEmpty) + "\n";
			previousSecond = end;
		}

		if(elapsed.count() >= 60)
		{
			output.close();
			exit(0);
		}

		// this_thread::sleep_for(chrono::seconds(1)); // sleep for a second and collect data again.
	}
}