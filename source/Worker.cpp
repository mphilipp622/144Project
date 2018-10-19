#include "../headers/Worker.h"

void Worker::JoinThread()
{
    execThread.join();
}