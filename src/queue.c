#include <stdlib.h>

#include "queue.h"

Queue *create_queue(int length) {
	Queue *queue = (Queue *) malloc(sizeof(Queue));
	queue->values = (int *) malloc(length * sizeof(int));
	queue->length = length;
	queue->start = 0;
	queue->end = 0;
	return queue;
}

void enqueue(Queue *queue, int value) {
	queue->values[queue->end++] = value;
	if (queue->end >= queue->length) {
		queue->end = 0;
	}
}

int dequeue(Queue *queue) {
	int value = queue->values[queue->start++];
	if (queue->start >= queue->length ) {
		queue->start = 0;
	}
	return value;
}

int is_queue_empty(Queue *queue) {
	return queue->start == queue->end;
}

void free_queue(Queue *queue) {
	if (queue == NULL) return;

	free(queue->values);
	free(queue);
}
