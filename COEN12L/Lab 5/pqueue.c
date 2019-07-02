#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pqueue.h"

#define PARENT(i)	((i-1)/2)
#define RIGHT(i) 	((i*2)+2)
#define LEFT(i)		((i*2)+1)

struct pqueue{
	int count;
	int length;
	void **data;
	int(*compare)();
};

//Create Queue: allocates memory for a queue and initializes variables
//O(1)
PQ *createQueue(int (*compare)()){
	PQ *pq;
	pq = malloc(sizeof(PQ));
	assert(pq != NULL);

	pq->count = 0;
	pq->length = 10;
	pq->compare = compare;
	pq->data = malloc(sizeof(void*)*10);
	assert(pq->data != NULL);

	return pq;
}

//Destroy Queue: frees allocated memory
//O(1)
void destroyQueue(PQ *pq){
	assert(pq != NULL);
	
	free(pq->data);
	free(pq);
}

//Returns number of entries in queue
//O(1)
int numEntries(PQ *pq){
	assert(pq != NULL);

	return pq->count;
}

//Add Entry: checks and reallocates double the memory if queue is full
//moves up the "tree" comparing the values and swapping to prioritize (bring to top) the smallest value
//O(logn)
void addEntry(PQ *pq, void *entry){
	assert(pq != NULL && entry != NULL);
	void *temp;
	int i;

	if(pq->count == pq->length){
		pq->data = realloc(pq->data, sizeof(void*) * pq->length * 2);
		pq->length *= 2;
	}
	
	i = pq->count;
	pq->data[i] = entry;
	
	while(PARENT(i) != i){	//moves up tree comparing values
		if((*pq->compare)(pq->data[PARENT(i)], pq->data[i]) > 0){	//parent is bigger than child
			temp = pq->data[i];
			pq->data[i] = pq->data[PARENT(i)];
			pq->data[PARENT(i)] = temp;
			i = PARENT(i);
		}
		else{
			break;
		}
	}
	pq->count++;
}

//Removes priority node value and adjusts "tree" to prioritize smallest values
//O(logn)
void *removeEntry(PQ *pq){
	assert(pq != NULL && pq->count > 0);
	int root = 0;
	void *min;
	min = pq->data[root];

	void *temp;
	pq->data[root] = pq->data[pq->count-1];

	pq->count--;

	while(LEFT(root) < pq->count){	//while new root has a child (LEFT is (root*2)+1)
		if(RIGHT(root) < pq->count){	//root has two children
			if((*pq->compare)(pq->data[LEFT(root)], pq->data[RIGHT(root)]) < 0){ //if LEFT is smaller than right
				if((*pq->compare)(pq->data[root], pq->data[LEFT(root)]) > 0){	//if new root is greater than LEFT: swap
					temp = pq->data[root];
					pq->data[root] = pq->data[LEFT(root)];
					pq->data[LEFT(root)] = temp;
					root = LEFT(root);
				}
				else{
					break;
				}
			}
			else{
				if((*pq->compare)(pq->data[root], pq->data[RIGHT(root)]) >0){	//if new root is greater than RIGHT: swap
					temp = pq->data[root];
					pq->data[root] = pq->data[RIGHT(root)];
					pq->data[RIGHT(root)] = temp;
					root = RIGHT(root);
				}
				else{
					break;
				}
			}
		}
		else{	//root has one child
			if((*pq->compare)(pq->data[root], pq->data[LEFT(root)]) > 0){	//swap with left child if root is greater
				temp = pq->data[root];
				pq->data[root] = pq->data[LEFT(root)];
				pq->data[LEFT(root)] = temp;
				root = LEFT(root);
			}
			else{
				break;
			}
		}
	}
	return min;
}

