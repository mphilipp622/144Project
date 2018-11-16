#pragma once
#include "Worker.h"
#include <typeinfo>

using namespace std;

// Inherits from worker
class Producer : public Worker
{
public:
    // The bounded queue in main will be passed to this ctor
    Producer(BlockingQueue* newQueue, int newID, int newTimeInterval);

private:
    void Update() override; // Thread's execution loop
    void ProduceItem();  // attempts to put an item into bbq
    void ChangeProductionSpeed();

    int item; // the item this producer publishes
};