#include "Worker.h"

void Worker::JoinThread()
{
    execThread.join();
}