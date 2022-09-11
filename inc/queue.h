#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct {
	int *values;
	int length;
	int start;
	int end;
} Queue;

Queue *create_queue(int length);
void enqueue(Queue *, int);
int dequeue(Queue *);
int is_queue_empty(Queue *);
void free_queue(Queue *);

#endif
