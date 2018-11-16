#pragma once
#include <thread>
#include <cstdlib> // used for rand()
#include <iostream>
#include <string>
#include <random>
#include "BlockingQueue.h"

using namespace std;

// Base abstract class for consumers and producers
class Worker
{
public:
    void JoinThread(); // Allows main thread to call join() on this thread

protected:
    int maxTimeInterval; // max sleep time of the thread in ms
    int currentTimeInterval; // current sleep time of the thread
    int threadID; // id to track thread

    short successes; // tracks how many successes this worker has had. Should never be larger than 2.

    thread execThread; // c++11 thread

    BlockingQueue* queue; // pointer to a bounded queue that this worker is accessing

    virtual void Update() = 0; // pure abstract function. Implemented in Producer and Consumer.
    int GetRandomNumber(int min, int max); // helper function for generating more accurate random numbers than rand()
};