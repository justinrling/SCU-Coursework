#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#define AVG_CHAIN_LENGTH 20

//Project 4: Part 2 - Adds on hashing to list.c. Creates set and implements hashing with chaining
//where each address in hash table is a list

struct set{
	int count;
	int length;
	LIST **lists;
	int (*compare)();
	unsigned (*hash)();
};

typedef struct set SET;

//CREATE SET
//Summary: Allocates memory for a new set and instantiates and tests all components of the set
//Creates a list for each address in the hash table
//O(1)

SET *createSet(int maxElts,int (*compare)(), unsigned (*hash)()){
	SET *sp;
	int i;
	sp = malloc(sizeof(SET));

	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts/AVG_CHAIN_LENGTH;
	sp->compare = compare;
	sp->hash = hash;
	sp->lists = malloc(sizeof(LIST*)*sp->length);
	assert(sp->lists != NULL);

	for(i = 0; i<sp->length; i++)
		sp->lists[i] = createList(compare);

	return sp;
}

//DESTROY SET
//Summary: Destroys set by freeing memory of each list within the set
//fress lists memory and then frees the memory of the set
//O(1)

void destroySet(SET *sp){
	assert(sp != NULL);

	int i;
	for(i=0; i<sp->length;i++)
		destroyList(sp->lists[i]);
	free(sp->lists);
	free(sp);
}

//NUMBER ELEMENTS
//Summary: Returns the number of elements in the set
//O(1)

int numElements(SET *sp){
	assert(sp != NULL);

	return sp->count;
}

//ADD ELEMENT
//Summary: Calls upon "list.c" function to add elements into the set or the sets list
//Finds index element is supposed to be inserted in (using hash function)
//calls "findItem" to see if element is in list and adds element to list if not found
//increments count
//O(n)

void addElement(SET *sp, void *elt){
	assert(sp != NULL);
	int index = (*sp->hash)(elt) % sp->length;
	if(findItem(sp->lists[index], elt) == NULL)
		addFirst(sp->lists[index], elt);

	sp->count++;
}

//REMOVE ELEMENT
//Summary: Calls upon "list.c" function to remove elements in the set or set list
//Finds index element is supposed to be in (using hash function)
//calls "findItem" to see if element is in list and removes element from list if found
//decrements count
//O(n)

void removeElement(SET *sp, void *elt){
	assert(sp != NULL && sp->count > 0);
	int index = (*sp->hash)(elt) % sp->length;
	if(findItem(sp->lists[index], elt) != NULL)
		removeItem(sp->lists[index], elt);

	sp->count--;
}

//FIND ELEMENT
//Summary: Returns whether or not an element is in the set or set list
//Finds index element should be in
//Calls and returns "findItem" function from "list.c"
//O(n)

void *findElement(SET *sp, void *elt){
	assert(sp != NULL);
	int index = (*sp->hash)(elt) % sp->length;
	
	return findItem(sp->lists[index], elt);
}

//GET ELEMENTS
//Summary: Returns a copy of all elements in set
//allocates memeory for new array. Using a for-loop, calls getItems to copy each list
//using a second for-loop, copy each list into the array
//O(n^2)

void *getElements(SET *sp){
	assert(sp != NULL);
	void **array;
	array = malloc(sizeof(void*)*sp->count);
	int i, j;
	int copyNum = 0;
	
	for(i = 0; i<sp->length; i++){
		void **copy = getItems(sp->lists[i]);
		for(j=0;j<numItems(sp->lists[i]);j++){
			array[copyNum] = copy[j];
			copyNum++;
		}
	}

	return array;
}

