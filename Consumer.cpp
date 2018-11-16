#include "Consumer.h"

Consumer::Consumer(BlockingQueue* newQueue, int newID, int newTimeInterval)
{
    // initialize variables
    queue = newQueue;
    threadID = newID;
    maxTimeInterval = newTimeInterval;
    successes = 0;

    currentTimeInterval = rand() % (maxTimeInterval + 1); // setup sleep time. (1 - maxTime)

    string message = "Consumer " + to_string(threadID) + " created with sleep time " + 
                     to_string(currentTimeInterval) + "\n\n";

    cout << message; // output initialization message

    // begin thread execution
    execThread = thread(&Consumer::Update, this);
}

void Consumer::ConsumeItem()
{
	
    // Get an item from the bbq
    queue->Remove(threadID);

    if(++successes >= 2) // increment successes. Looking for consecutive success
    {
        currentTimeInterval = rand() % (maxTimeInterval + 1);
        successes = 0;
    }

    this_thread::sleep_for(chrono::seconds(currentTimeInterval)); // sleep the thread after it produces
}

void Consumer::Update()
{
    // Loop the thread infinitely

    while(true)
		ConsumeItem();
}