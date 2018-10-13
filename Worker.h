#pragma once
#include <thread>
#include <cstdlib> // used for rand()
#include <iostream>
#include <string>
#include "BoundedQueue.h"
#include <random>

using namespace std;

// Base class for consumers and producers
class Worker
{
public:
    void JoinThread(); // used for main thread to pause program execution if necessary

protected:
    int maxTimeInterval;
    int currentTimeInterval;
    int threadID;

    short successes; // tracks how many successes this worker has had. Should never be larger than 2.

    thread execThread;

    BoundedQueue* queue;

    virtual void Update() = 0; // pure abstract function

    int intRand(const int & min, const int & max);
};