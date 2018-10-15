#pragma once
#include "Worker.h"

using namespace std;

class Consumer : public Worker
{
public:
    Consumer(BoundedQueue* newQueue, int newID, int newTimeInterval);

private:
    void Update() override; // Executes infinite loop where consumer tries consuming item every iteration
    void ConsumeItem(); // consumer attempts to get item from queue.
};