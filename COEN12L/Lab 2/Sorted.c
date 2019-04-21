#include <stdio.h>  //including libraries
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

typedef struct set{		//create struct set
	char **data;
	int length;
	int count;
}SET;

SET *sp;

static int search(SET *sp, char *elt, bool *found);	//initialize functions	
SET *createSet(int maxElts);
void destroySet(SET *sp);
int numElements(SET *sp);
void addElement(SET *sp, char *elt);
void removeElement(SET *sp, char *elt);
char *findElement(SET *sp, char *elt);
char **getElements(SET *sp);

SET *createSet(int maxElts){	//parameters: max elements does: creates a set, initializes set variable	O(1)
	SET *sp = malloc(sizeof(SET)); //allocate memory
	assert(sp != NULL);	//test memory allocation

	sp->length = maxElts;	//initializing set variables
	sp->count = 0;
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);

	return sp;
}

void destroySet(SET *sp){	//parameters: set does: free all memory 	O(n)
	int i;
	assert(sp != NULL);	//test memory allocation
	
	for(i=0; i<sp->length;i++)	//freeing memory starting from elements in sp->data moving to sp
		free(sp->data[i]);
	free(sp->data);
	free(sp);
}

int numElements(SET *sp){	//parameters: set does:returns number of elements in data	O(1)
	assert(sp != NULL);	//test memory allocation

	return sp->count;
}

void addElement(SET *sp, char *elt){	//parameters: set and specific element does: checks if set is full and calls search function, then adds element to set	O(logn)
	assert(sp != NULL);	//test memory allocation
	int i;
	bool found = true;	//set found to true

	if(sp->count == sp->length){	//tests if set is full
		return; //error
	}
	int index = search(sp, elt, &found);	//sets index to where element should be added
	if(found == true)	//tests if element already found
		return; //error

	for(i=sp->count; i>index; i--)	//shift elements from index DOWN one slot - starts from end
		sp->data[i] = sp->data[i-1];
	sp->data[index] = strdup(elt);
	sp->count++;
}

static int search(SET *sp, char *elt, bool *found){	//paramters: set, specific element, and boolean found does: returns index of element if found	O(logn)
	int lo, hi, mid;
	lo = 0;
	hi = sp->count - 1;
	char *midElt;

	while(lo<=hi){
		mid = (lo+hi)/2;
		midElt = sp->data[mid];	//element at mid

		if(strcmp(elt, midElt) < 0)	//string compare to order strings
			hi = mid-1;
		else if(strcmp(elt, midElt) > 0)
			lo = mid+1;
		else{
			*found = true;	//sets found pointer to true if found and returns mid as index
			return mid;
		}
	}
	*found = false;	//sets found pointer to false otherwise
	return lo;	//returns index element should be added to
}

void removeElement(SET *sp, char *elt){	//parameters: set and specific element does: calls search function then removes specific element	O(logn)
	int i;
	bool found = false;	//found initially false
	assert(sp != NULL);	//test memory allocation
	int index = search(sp, elt, &found);	//sets index to where element is if found
	char* temp = sp->data[index];	//temp element that's going to be removed

	if(found == false)	//unable to find element
		return; //error

	for(i=index+1;i<sp->count;i++)	//shifts elements from index UP one slot starting from beginning
		sp->data[i-1] = sp->data[i];
	free(temp);
	sp->count--;
}

char *findElement(SET *sp, char *elt){	//parameters: set and specific element does: calls search function and returns element if found	O(logn)
	assert(sp != NULL);	//test memory allocation
	bool found = false;	
	int index = search(sp, elt, &found);
	if(found == false)	//checks if element is in set
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
