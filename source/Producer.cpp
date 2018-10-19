#include "../headers/Producer.h"

Producer::Producer(BoundedQueue* newQueue, int newID, int newTimeInterval)
{
    // Assign variables
    queue = newQueue;
    threadID = newID;
    maxTimeInterval = newTimeInterval;
    successes = 0;

     currentTimeInterval = rand() % (maxTimeInterval + 1); // setup sleep time. (0 - maxTime)

    item = rand() % 1000; // item is a random number between 0 and 999

    // Creation message
    string message = "Producer " + to_string(threadID) + " created holding item " + to_string(item) +
                     " with sleep time " + to_string(currentTimeInterval) + "\n\n";

    // output message
    cout << message;

    // begin thread execution. Have to use "this" to call a member function.
    execThread = thread(&Producer::Update, this);
}

void Producer::ProduceItem()
{
    // Try and insert item into the bbq
	if(queue->TryInsert(item)) 
	{
        string message = to_string(item) + " produced by producer " + to_string(threadID) + "\n\n";
		
        cout << message; // print success message

        if(++successes >= 2) // increment successes. If consecutive successes, change sleep time.
            currentTimeInterval = rand() % (maxTimeInterval + 1);

		this_thread::sleep_for(chrono::seconds(currentTimeInterval)); // sleep the thread after it produces
	}
    else
        successes = 0; // we're only looking for consecutive successes. reset current value if we don't produce
}

void Producer::Update()
{
    // This function loops a producer forever.

    while(true)
	{
		if (rand() % 2 == 1)
			// coin flip. If producer comes up with 1, we try producing
			ProduceItem(); 
	}
}