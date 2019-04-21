#include <stdio.h>  //including libraries
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "set.h"

typedef struct set{		//create struct set
	char **data;
	int length;
	int count;
}SET;

SET *sp;

static int search(SET *sp, char *elt);	//initialize functions
SET *createSet(int maxElts);
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, char *elt);
void removeElement(SET *sp, char *elt);
char *findElement(SET *sp, char *elt);
char **getElements(SET *sp);

SET *createSet(int maxElts){	//parameters: max elements does: creates a set, initializes set variable	O(1)
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);	//test memory allocation

	sp->length = maxElts;	//initialize set variables
	sp->count = 0;
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);	//test memory allocation

	return sp;
}

void destroySet(SET *sp){	//parameters: set does: free all memory	O(n)
	int i;
	assert(sp != NULL);	//test memory allocation
	
	for(i=0; i<sp->length;i++)	//frees memory starting from data and moving to sp
		free(sp->data[i]);
	free(sp->data);
	free(sp);
}

int numElements(SET *sp){	//parameters: set does:returns number of elements in data	O(1)
	assert(sp != NULL);	//tests memory allocation

	return sp->count;
}

void addElement(SET *sp, char *elt){	//parameters: set and specific element does: checks if set is full and calls search function, then adds element to set	O(n)
	assert(sp != NULL);	//test memory allocation
	
	if(sp->count == sp->length){	//check if set is full
		return; //error
	}
	int index = search(sp, elt);	//sets index to position element should be inserted, returns -1 if already in set
	if(index != -1)	//checks if element already in set
		return; //error

	sp->data[sp->count] = strdup(elt);	//makes duplicate of elt allocate memory and point to elt
	sp->count++;
}

static int search(SET *sp, char *elt){	//paramters: set and specific element does: returns index of element if found, -1 otherwise	O(n)
	int i;

	for(i=0; i<sp->count;i++){	//traverses set looking for element
		if(strcmp(elt, sp->data[i]) == 0)
			return i;
	}
	return -1;
}

void removeElement(SET *sp, char *elt){	//parameters: set and specific element does: calls search function then removes specific element	O(n)
	int i;
	assert(sp != NULL);	//test memory allocation
	int index = search(sp, elt);	//set index to position that will be removed
	if(index == -1)	//element is not in set
		return; //error
	free(sp->data[index]);	//free pointer
	sp->data[index] = sp->data[sp->count-1];	//point to last element in the count
	sp->count--;
}

char *findElement(SET *sp, char *elt){	//parameters: set and specific element does: calls search function and returns element if found	O(n)
	assert(sp != NULL);
	int index = search(sp, elt);
	if(index == -1)	//element not found
		return NULL; //error
	return sp->data[index];
}

char **getElements(SET *sp){	//parameters: set does: allocates memory and returns copy of set	O(1)
	assert(sp != NULL);	
	char **temp = malloc(sizeof(char*)*sp->count);
	memcpy(temp, sp->data, sizeof(char*) * sp->count);
	assert(temp != NULL);
	return temp;
}
	
		


