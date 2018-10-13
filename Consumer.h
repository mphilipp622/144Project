#pragma once
#include "Worker.h"

using namespace std;

class Consumer : public Worker
{
public:
    Consumer();
    Consumer(BoundedQueue* newQueue, int newID, int newTimeInterval);
    ~Consumer();

private:
    void Update() override;
    void ConsumeItem();
};