#include "Consumer.h"

Consumer::Consumer()
{
    // default ctor
}

Consumer::Consumer(BoundedQueue* newQueue, int newID, int newTimeInterval)
{
    queue = newQueue;
    threadID = newID;
    maxTimeInterval = newTimeInterval;
    currentTimeInterval = 0;
    successes = 0;

    // begin thread execution
    execThread = thread(&Consumer::Update, this);
}

Consumer::~Consumer()
{

}

void Consumer::ConsumeItem()
{
	int item;
	
	if(queue->TryRemove(&item))
	{
		string message = "Item ID " + to_string(item) + " consumed by consumer " + to_string(threadID) + "\n";

        cout << message;

        if(++successes >= 2) // increment successes
        {
            currentTimeInterval = rand() % maxTimeInterval + 1;
            // currentTimeInterval = rand() % maxTimeInterval; // randomize new wait time between 0 and t
        }

		this_thread::sleep_for(chrono::seconds(currentTimeInterval)); // sleep the thread after it produces
	}
    else
        successes = 0; // reset successes to interrupt consecutive count.

}

void Consumer::Update()
{
    while(true)
		ConsumeItem();
}