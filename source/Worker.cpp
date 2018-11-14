#include "../headers/Worker.h"

void Worker::JoinThread()
{
    execThread.join();
}

int Worker::GetRandomNumber(int min, int max)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range

    return distr(eng);
}