#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

#define EMPTY 0
#define DELETED 2
#define FILLED 1

typedef struct set{
	int count;
	int length;
	char** elts;
	char* flags;
	int (*compare)();
	unsigned (*hash)();
}SET;

SET *sp;

//CREATE SET
//O(n)
//Creates a set by allocating memory and initializing all variables,
//returning the created set

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length= maxElts;
	sp->elts = malloc(sizeof(void*)*maxElts);
	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->elts != NULL);
	assert(sp->flags != NULL);
	sp->compare = compare;
	sp->hash = hash;
	
	for(int i = 0; i<maxElts; i++)
		sp->flags[i] = EMPTY;
	return sp;
}

//DESTROY SET
//O(n)
//Frees allocated memory and destroys set

void destroySet(SET *sp){
	assert(sp != NULL);
	assert(sp->elts != NULL && sp->flags != NULL);
	
	free(sp->flags);
	free(sp->elts);
	free(sp);
}

//NUMBER OF ELEMENTS
//O(1)
//returns number of elements in sp

int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}

//SEARCH
//Expected: O(1)
//Worst Case: O(n)
//returns the index of an element or where it should be inserted
//also checks if element exists in set or was deleted

static int search(SET *sp, void *elt, bool *found){
	assert(sp != NULL);
	assert(elt != NULL);
	*found = false;
	int hfunction;
	int id = -1;
	int probe;

	for(probe = 0; probe < sp->length; probe++){ 
		hfunction = ((*sp->hash)(elt) + probe) % sp->length;
		if(sp->flags[hfunction] == FILLED){
			if((*sp->compare)(sp->elts[hfunction], elt) == 0){
				*found = true;
				return hfunction;
			}
		}
		else if(sp->flags[hfunction] == EMPTY){
			if(id != -1)
				return id;
			else
				return hfunction;
		}
		else if(sp->flags[hfunction] == DELETED){
			if(id == -1)
				id = hfunction;
		}
	}
	return id;
}

//ADD ELEMENT
//Expected: O(1)
//Worst Case: O(n)
//Adds an element to the set, calling search to check
//if element is in the set and find the index the element should be inserted
//changes flag to FILLED

void addElement(SET *sp, void *elt){
	assert(sp !=NULL);
	assert(elt != NULL);
	bool found;
	int index = search(sp, elt, &found);
	if(sp->count == sp->length)
		return;
	if(found)
		return;
	sp->elts[index] = elt;
	sp->flags[index] = FILLED;
	sp->count++;
}

//REMOVE ELEMENT
//Expected: O(1)
//Worst Case: O(n)
//removes element by calling search function and deleting it from the set if it exists
//changes flag to DELETED 

void removeElement(SET *sp, void *elt){
	assert(sp != NULL);
	assert(elt != NULL);
	bool found;
	int index = search(sp, elt, &found);
	if(found){
		sp->flags[index] = DELETED;
		sp->count--;
	}
}

//FIND ELEMENT
//Expected: O(1)
//Worst Case: O(n)
//finds and returns element if found in set

void *findElement(SET *sp, void *elt){
	assert(sp != NULL);
	assert(elt != NULL);
	bool found;
	int index = search(sp, elt, &found);
	if(found)
		return sp->elts[index];
	return NULL;
}

// GET ELEMENTS
// O(n)
// allocates memory for and returns the elements of the SET in a new array

void *getElements(SET *sp){
	void **copy;
	int i,j;
	assert(sp !=NULL);
	copy = malloc(sizeof(void*)*sp->count);
	assert(copy != NULL);
	
	for(i=0, j=0; i<sp->length; i++){
		if(sp->flags[i] == FILLED)
			copy[j++] = sp->elts[i];
	}
	return copy;
}





