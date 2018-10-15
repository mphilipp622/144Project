#include "Producer.h"

Producer::Producer(BoundedQueue* newQueue, int newID, int newTimeInterval)
{
    queue = newQueue;
    threadID = newID;
    maxTimeInterval = newTimeInterval;
    currentTimeInterval = rand() % maxTimeInterval + 1; // setup sleep time
    successes = 0;

    item = rand() % 1000;

    string message = "Producer " + to_string(threadID) + " Created Holding Item " + to_string(item) +
                     " with sleep time " + to_string(currentTimeInterval) + "\n\n";

    cout << message;

    // begin thread execution
    execThread = thread(&Producer::Update, this);
}

void Producer::ProduceItem()
{
    // int newVal = intRand(1, 1000); // random value between 1 and 1000

	if(queue->TryInsert(item)) 
	{
        string message = "Item ID " + to_string(item) + " produced by producer " + to_string(threadID) + "\n\n";
		
        cout << message;

        if(++successes >= 2) // increment successes
        {
            currentTimeInterval = rand() % maxTimeInterval + 1;
            // currentTimeInterval = rand() % maxTimeInterval; // randomize new wait time between 0 and t
        }

		this_thread::sleep_for(chrono::seconds(currentTimeInterval)); // sleep the thread after it produces
	}
    else
        successes = 0; // we're only looking for consecutive successes. reset current value if we don't produce
}

void Producer::Update()
{
    // This function loops a producer forever. Producer will attempt a coin flip and try producing item if coin flip is successful.

    while(true)
	{
		if (rand() % 2 == 1)
			// coin flip. If producer comes up with 1, we try producing
			ProduceItem(); 
	}
}