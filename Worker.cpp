#include "Worker.h"

void Worker::JoinThread()
{
    execThread.join();
}

int Worker::intRand(const int &min, const int &max)
{
    static thread_local std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}