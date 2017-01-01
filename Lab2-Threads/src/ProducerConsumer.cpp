#include "ProducerConsumer.h"
#include <unistd.h> // sleep

//TODO: add BoundedBuffer, locks and any global variables here 
int p, c, psleep, csleep, items, count, x, y;
BoundedBuffer* buffer;
pthread_mutex_t lock;
time_t start;
FILE *f;

void InitProducerConsumer(int p1, int c1, int psleep1, int csleep1, int items1){
	//TODO: constructor to initialize variables declared
	//also see instruction for implementation
	p = p1;
	c = c1;
	psleep = psleep1;
	csleep = csleep1;
	items = items1;
	count = 0;
	buffer = new BoundedBuffer(items1);
	pthread_mutex_init(&lock, NULL);
	pthread_t pthreads[p];
	pthread_t cthreads[c];
	srand(time(NULL)); // Random # Gen
	start = clock(); // Clock start
	f = fopen("output.txt", "w"); // Open file

	int ip[p]; // Create pthreads, use ip[p] to pass integer.
	for(int i = 0; i < p; i++){
		ip[i] = i;
		pthread_create(&pthreads[i], NULL, producer, (void*)(ip + i));
	}

	int ic[c]; // Create cthreads, use ic[c] to pass integer.
	for(int i = 0; i < c; i++){
		ic[i] = i;
		pthread_create(&cthreads[i], NULL, consumer, (void*)(ic + i));
	}

	// Do not let main thread die
	for(int i = 0; i < p+c; i++){
		if(i<p)
			pthread_join(pthreads[i], 0);
		if(i<c)
			pthread_join(cthreads[i], 0);
	}

	// Close file
	fclose(f);
}

void *producer(void* threadID){
	//TODO: producer thread, see instruction for implementation
	int* i = (int*)threadID; // i # from loop above
	while(true){
		usleep(psleep);
		pthread_mutex_lock(&lock);
		bool run = (x < items);			// test if finished producing
		if(run) x++;
		pthread_mutex_unlock(&lock);
		if(run){
			int foo = rand() % 20;
			buffer->append(foo);
			time_t end = clock();
			double time_spent = (double)(end-start)/CLOCKS_PER_SEC;		// Clock calc
			pthread_mutex_lock(&lock);
			count++;
			fprintf(f,"Producer #%d, time = %f, producing data item #%d, item value=%d\n", *i+1, time_spent, count, foo);
			pthread_mutex_unlock(&lock);
		}else{
			break;
		}
	}
	pthread_exit(NULL);
}

void *consumer(void* threadID){
	//TODO: consumer thread, see instruction for implementation
	int* k = (int*)threadID; // i # from loop above
	while(true){
		usleep(csleep);
		pthread_mutex_lock(&lock);
		bool run = (y < count);			// test if more produced items than consumed
		bool dun = (y >= items);		// test if thread (program) is done
		if(run) y++;
		pthread_mutex_unlock(&lock);
		if(run){
			int foo = buffer->remove();
			time_t end = clock();
			double time_spent = (double)(end-start)/CLOCKS_PER_SEC;		// Clock calc
			pthread_mutex_lock(&lock);
			fprintf(f,"Consumer #%d, time = %f, consuming data item with value=%d\n", *k+1, time_spent, foo);
			pthread_mutex_unlock(&lock);
		}else if(dun){
			break;
		}
	}
	pthread_exit(NULL);
}