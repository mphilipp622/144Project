#include "../headers/Consumer.h"

Consumer::Consumer(BoundedQueue* newQueue, int newID, int newTimeInterval)
{
    // initialize variables
    queue = newQueue;
    threadID = newID;
    maxTimeInterval = newTimeInterval;
    successes = 0;

    currentTimeInterval = rand() % (maxTimeInterval + 1); // setup sleep time. (0 - maxTime)

    string message = "Consumer " + to_string(threadID) + " created with sleep time " + 
                     to_string(currentTimeInterval) + "\n\n";

    cout << message; // output initialization message

    // begin thread execution
    execThread = thread(&Consumer::Update, this);
}

void Consumer::ConsumeItem()
{
	int item;
	
    // Try to get an item from the bbq
	if(queue->TryRemove(&item))
	{
		string message = to_string(item) + " consumed by consumer " + to_string(threadID) + "\n\n";

        cout << message; // output success message

        if(++successes >= 2) // increment successes. Looking for consecutive success
            currentTimeInterval = rand() % (maxTimeInterval + 1);

		this_thread::sleep_for(chrono::seconds(currentTimeInterval)); // sleep the thread after it produces
	}
    else
        successes = 0; // reset successes to interrupt consecutive count.
}

void Consumer::Update()
{
    // Loop the thread inifinitely

    while(true)
		ConsumeItem();
}