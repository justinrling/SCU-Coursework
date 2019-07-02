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
}SET;

SET *sp;

//CREATE SET
//O(n)
//Creates a set by allocating memory and initializing all variables

SET *createSet(int maxElts){
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length= maxElts;
	sp->elts = malloc(sizeof(char*)*maxElts);
	sp->flags = malloc(sizeof(char)*maxElts);
	assert(sp->elts != NULL);
	assert(sp->flags != NULL);
	
	for(int i = 0; i<maxElts; i++)
		sp->flags[i] = EMPTY;
	return sp;
}

//DESTROY SET
//O(n)
//Frees all allocated memory and destroys the set

void destroySet(SET *sp){
	assert(sp != NULL);
	assert(sp->elts != NULL && sp->flags != NULL);
	
	for(int i = 0;i < sp->length; i++){
		if(sp->flags[i] == FILLED)
			free(sp->elts[i]);
	}
	free(sp->flags);
	free(sp->elts);
	free(sp);
}

//NUMBER OF ELEMENTS
//O(1)
//returns the number of elements in the set

int numElements(SET *sp){
	assert(sp != NULL);
	return sp->count;
}

unsigned strhash(char *s){
	unsigned hash = 0;
	while(*s != '\0')
		hash = 31 * hash + *s ++;
	return hash;
}

//SEARCH
//Expected: O(1)
//Worst Case: O(n)
//returns index of an element or where it should be inserted
//checks whether element is in the set or not or if it had been deleted

static int search(SET *sp, char *elt, bool *found){
	assert(sp != NULL);
	assert(elt != NULL);
	*found = false;
	int hfunction;
	int id = -1;
	int probe;

	for(probe = 0; probe < sp->length; probe++){ 
		hfunction = (strhash(elt) + probe) % sp->length;
		if(sp->flags[hfunction] == FILLED){
			if(strcmp(sp->elts[hfunction], elt) == 0){
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
//Adds element to set if not already in set
//Calls search function to determine where to insert element (maintain sorted)

void addElement(SET *sp, char *elt){
	assert(sp !=NULL);
	assert(elt != NULL);
	bool found;
	int index = search(sp, elt, &found);
	if(sp->count == sp->length)
		return;
	if(found)
		return;
	sp->elts[index] = strdup(elt);
	sp->flags[index] = FILLED;
	sp->count++;
}

//REMOVE ELEMENT
//Expected: O(1)
//Worst Case: O(n)
//Removes element from set if in set
//Calls search function to return index that should be deleted

void removeElement(SET *sp, char *elt){
	assert(sp != NULL);
	assert(elt != NULL);
	bool found;
	int index = search(sp, elt, &found);
	if(found){
		free(sp->elts[index]);
		sp->flags[index] = DELETED;
		sp->count--;
	}
}

//FIND ELEMENT
//Expected: O(1)
//Worst Case: O(n)
//calls search function and returns element if found in set

char *findElement(SET *sp, char *elt){
	assert(sp != NULL);
	assert(elt != NULL);
	bool found;
	int index = search(sp, elt, &found);
	if(found)
		return sp->elts[index];
	return NULL;
}

//GET ELEMENTS
//O(n)
//Returns the elements of the SET in a newly allocated array

char **getElements(SET *sp){
	char **copy;
	int i,j;
	assert(sp !=NULL);
	copy = malloc(sizeof(char*)*sp->count);
	assert(copy != NULL);
	
	for(i=0, j=0; i<sp->length; i++){
		if(sp->flags[i] == FILLED)
			copy[j++] = sp->elts[i];
	}
	return copy;
}





