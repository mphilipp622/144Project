/*
Mark Philipp
CSCI 144
11/22/18
*/

#include <iostream>
#include <ctime> // used for timer
#include <cstdlib>
#include <string>
#include "headers/Producer.h"
#include "headers/Consumer.h"
#include "headers/BlockingQueue.h"

int main(int argc, char *argv[])
{
	int producerInterval = 0, consumerInterval = 0;

	srand(time(NULL));

	cout << "PROGRAM START" << endl;

	if(argc > 2)
	{
		// Assign intervals from command line arguments
		producerInterval = stoi(argv[1]);
		consumerInterval = stoi(argv[2]);

		if(producerInterval < 0 || consumerInterval < 0)
		{
			cout << "Producer and Consumer intervals must be 0 or larger";
			return 0;
		}
	}
	else
	{
		// Throw an error and exit program if program is run without parameters
		cout << "Command Line Argument Error: Program requires producer interval and consumer interval be set" << endl;
		return 0;
	}

	// Create shared blocking queue
	BlockingQueue* queue = new BlockingQueue();

	// Create consumers and producers
	Consumer* consumers[10];
	Producer* producers[10];

	for(int i = 0; i < 10; i++)
	{
		// initialize all the consumer and producer threads. ID's are i + 1 (1 to 10)
		consumers[i] = new Consumer(queue, i + 1, consumerInterval);
		producers[i] = new Producer(queue, i + 1, producerInterval);
	}
	
	// Waiting for a single join() will keep execution running forever so main doesn't quit
	consumers[0]->JoinThread();

	return 0;
}