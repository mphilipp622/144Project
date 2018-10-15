#include <iostream>
#include <ctime> // used for timer
#include <cstdlib>
#include <string>
#include "Producer.h"
#include "Consumer.h"
#include "BoundedQueue.h"

int main(int argc, char *argv[])
{
	int producerInterval = 0, consumerInterval = 0;

	srand(time(NULL));

	if(argc > 2)
	{
		// Assign intervals from command line arguments
		producerInterval = stoi(argv[1]);
		consumerInterval = stoi(argv[2]);
	}
	else
	{
		// Throw an error and exit program if program is run incorrectly.
		cout << "Command Line Argument Error: Program requires producer interval and consumer interval be set" << endl;
		return 0;
	}

	BoundedQueue* queue = new BoundedQueue();

	Consumer* consumers[10];
	Producer* producers[10];

	for(int i = 0; i < 10; i++)
	{
		consumers[i] = new Consumer(queue, i, consumerInterval);
		producers[i] = new Producer(queue, i, producerInterval);
	}
	
	consumers[0]->JoinThread();
	producers[0]->JoinThread();

	return 0;
}