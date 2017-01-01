#include "BoundedBuffer.h"

BoundedBuffer::BoundedBuffer(int N){
	//TODO: constructor to initiliaze all the varibales declared in BoundedBuffer.h
	S = N;
	first = 0;
	last = 0;
	count = 0;
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&full, NULL);
	pthread_cond_init(&empty, NULL);
}

void BoundedBuffer::append(int data){
	//TODO: append a data item to the circular buffer
	pthread_mutex_lock(&lock);
	if(count == S)
		pthread_cond_wait(&empty, &lock);	// Wait for remove
	buffer[last] = data;
	last = (last + 1) % S;
	count++;
	pthread_cond_signal(&full);				// Signal append
	pthread_mutex_unlock(&lock);
}

int BoundedBuffer::remove(){
	//TODO: remove and return a data item from the circular buffer
	pthread_mutex_lock(&lock);
	if(count == 0)
		pthread_cond_wait(&full, &lock);	// Wait for append
	int item = buffer[first];
	first = (first + 1) % S;
	count--;
	pthread_cond_signal(&empty);			// Signal remove
	pthread_mutex_unlock(&lock);
	return item;
}

bool BoundedBuffer::isEmpty(){
	//TODO: check is the buffer is empty
	pthread_mutex_lock(&lock);
	bool emp = false;
	if(count == 0)
		emp = true;
	pthread_mutex_unlock(&lock);
	return emp;
}

// Create new method isFull(), did not use though.
bool BoundedBuffer::isFull(){
	//TODO: check is the buffer is full
	pthread_mutex_lock(&lock);
	bool ful = false;
	if(count == S)
		ful = true;
	pthread_mutex_unlock(&lock);
	return ful;
}