#pragma once
#include "Worker.h"

using namespace std;

// Inherits from worker. Only need constructors
class Producer : public Worker
{
public:
    Producer(BoundedQueue* newQueue, int newID, int newTimeInterval);

private:
    void Update() override;
    void ProduceItem();

    int item; // the item this producer publishes
};