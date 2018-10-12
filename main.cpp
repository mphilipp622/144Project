#include <iostream>
#include <thread>
#include "BlockingQueue.h"

void PutSome(BlockingQueue* queue)
{
	for(int i = 0; i < 50; i++)
		queue->Insert(i);
}

void TestRemoval(BlockingQueue* queue)
{
	int item;
	
	for(int i = 0; i < 20; i++)
	{
		if(queue->Remove())
			cout << "Removed " << item << endl;
		else
			cout << "Nothing there.\n";
	}
}

int main()
{
	BlockingQueue* queues[3];
	thread workers[3];
	
	for(int i = 0; i < 3; i++)
	{
		queues[i] = new BlockingQueue();
		workers[i] = thread(PutSome, queues[i]);
	}
	
	workers[0].join();
	
	for(int i = 0; i < 3; i++)
	{
		cout << "Queue " << i << endl;
		TestRemoval(queues[i]);
	}
	
	workers[1].join();
	workers[2].join();
	
	return 0;
}