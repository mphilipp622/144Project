#pragma once
#include "Worker.h"

using namespace std;

// Inherits from worker
class Producer : public Worker
{
public:
    // The bounded queue in main will be passed to this ctor
    Producer(BoundedQueue* newQueue, int newID, int newTimeInterval);

private:
    void Update() override; // Thread's execution loop
    void ProduceItem();  // attempts to put an item into bbq

    int item; // the item this producer publishes
};