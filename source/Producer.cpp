#include "../headers/Producer.h"

Producer::Producer(BlockingQueue* newQueue, int newID, int newTimeInterval)
{
    // Assign variables
    queue = newQueue;
    threadID = newID;
    maxTimeInterval = newTimeInterval;
    successes = 0;

    currentTimeInterval = 1000 * GetRandomNumber(0, maxTimeInterval + 1); // setup sleep time. (0 - maxTime)

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
    queue->Insert(item, threadID);

    // if(++successes >= 2) // increment successes. If consecutive successes, change sleep time.
    // {
        ChangeProductionSpeed();
        // successes = 0;
    // }

	this_thread::sleep_for(chrono::milliseconds(currentTimeInterval)); // sleep the thread after it produces

}

void Producer::Update()
{
    // This function loops a producer forever.

    while(true)
		ProduceItem();
}

void Producer::ChangeProductionSpeed()
{
    float capacity = queue->GetPercentageFull();
    string message;

    if(capacity >= 0.75)
    {
        // Modify time by the capacity percentage of the queue. If the capacity is high, time interval will approach max time interval.
        // If capacity is low, time interval will approach 0
        int newTP = 1000 * (maxTimeInterval + (capacity * maxTimeInterval));

        currentTimeInterval = GetRandomNumber(0, newTP + 1); 
        message = "Producer " + to_string(threadID) + " SLOWING DOWN TO " + to_string(currentTimeInterval) + "\n\n";
    }
    else if(capacity <= 0.25)
    {
        float twiceSpeed = (maxTimeInterval / 2.0); // 2 times the original interval value
        int newTP = 1000 * (maxTimeInterval - ((1.0 - capacity) * twiceSpeed)); // multiple the two times speed by a value between 1 and 0.75 based on queue size.

        currentTimeInterval = GetRandomNumber(0, newTP + 1);
        message = "Producer " + to_string(threadID) + " SPEEDING UP TO " + to_string(currentTimeInterval) + "\n\n";
    }
    else
        currentTimeInterval = GetRandomNumber(0, maxTimeInterval + 1) * 1000; // random between 1 and maxInterval
    
    
    cout << message;
}