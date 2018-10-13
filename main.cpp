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

	BoundedQueue* queue;

	Consumer* consumers[10];
	Producer* producers[10];
	
	queue = new BoundedQueue();

	for(int i = 0; i < 10; i++)
	{
		consumers[i] = new Consumer(queue, i, consumerInterval);
		producers[i] = new Producer(queue, i, producerInterval);

		// producers[i]->GetThread() = thread(ExecProducer, producers[i]);
		// consumers[i]->GetThread() = thread(ExecConsumer, consumers[i]);
		// producers[i] = thread(ExecProducer, queue, i, producerInterval);
		// consumers[i] = thread(ExecConsumer, queue, i, consumerInterval);
	}
	
	consumers[0]->JoinThread();
	producers[0]->JoinThread();
	// Call join on a consumer and producer to stop program from closing
	// producers[0]->GetThread().join();
	// consumers[0]->GetThread().join();	

	return 0;
}