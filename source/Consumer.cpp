#include "../headers/Consumer.h"

Consumer::Consumer(BlockingQueue* newQueue, int newID, int newTimeInterval)
{
    // initialize variables
    queue = newQueue;
    threadID = newID;
    maxTimeInterval = newTimeInterval;
    successes = 0;

    currentTimeInterval = rand() % (maxTimeInterval + 1); // setup sleep time. (0 to maxTime)

    // output initialization message
    string message = "Consumer " + to_string(threadID) + " created\n\n";
    cout << message; 

    // begin thread execution
    execThread = thread(&Consumer::Update, this);
}

void Consumer::ConsumeItem()
{
    // Get an item from the bbq
    queue->Remove(threadID);

    if(++successes >= 2) // increment successes. Looking for consecutive success
    {
        // Consecutive success means the consumer changes its sleep time
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