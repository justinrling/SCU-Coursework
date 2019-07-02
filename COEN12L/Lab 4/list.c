#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

//Project 4: Creating a deque (doubly linked circular list with a dummy node)

struct list{
	int count;
	struct node *head;
	int (*compare)();
};

typedef struct list LIST;

struct node{
	void *data;
	struct node *next;
	struct node *prev;
};

typedef struct node NODE;

//CREATE LIST
//Summary: This function allocates memory for a list and points head of list to dummy node
//O(!)

LIST *createList(int (*compare)()){
	LIST *lp;
	NODE *dummy;
	lp = malloc(sizeof(LIST));
	dummy = malloc(sizeof(NODE));
	assert(lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = dummy;
	dummy->next = dummy;
	dummy->prev = dummy;
	
	return lp;
}

//DESTROY LIST
//Summary: This function destroys the list starting at the first node (next of dummy) 
//and ending when it traverses back to the head
//O(n)

void destroyList(LIST *lp){
	NODE *np, *next;

	assert(lp != NULL);
	np = lp->head;

	do{
		next = np->next;
		free(np);
		np = next;
	}
	while(np != lp->head);
	free(lp);
}

//NUMBER ITEMS
//Summary: Returns the number of items within the list
//O(1)

int numItems(LIST *lp){
	assert(lp != NULL);

	return lp->count;
}

//ADD FIRST
//Summary: Allocates memory for a new node and adds it to the front of the list
//while maintaining connections throughout the list
//O(1)

void addFirst(LIST *lp, void *item){
	assert(lp != NULL);

	NODE *head = lp->head;
	NODE *pNew = malloc(sizeof(NODE));
	assert(pNew != NULL);
	
	pNew->data = item;
	pNew->next = head->next;
	pNew->prev = head;
	head->next = pNew;	
	pNew->next->prev = pNew;

	lp->count++;
}

//ADD LAST
//Summary: Allocates memory for a new node and adds it to the end of the list
//while maintaining connections throughout the list
//O(1)
 
void addLast(LIST *lp, void *item){
	assert(lp != NULL);
	
	NODE *head = lp->head;
	NODE *pNew = malloc(sizeof(NODE));
	assert(pNew != NULL);
	
	pNew->data = item;
	pNew->next = head;
	pNew->prev = head->prev;
	head->prev->next = pNew;
	head->prev = pNew;

	lp->count++;
}

//REMOVE FIRST
//Summary: Removes the first element in the list and returns its data.
//assigns pDel to node after the head, rewires connections as if pDel were deleted
//returns pDel data and then frees
//O(1)

void *removeFirst(LIST *lp){
	assert(lp != NULL && lp->count > 0);
	
	NODE *head = lp->head;
	NODE *pDel = lp->head->next;

	head->next = pDel->next;
	pDel->next->prev = head;

	void *data = pDel->data;
	free(pDel);
	lp->count--;
	return data;
}

//REMOVE LAST
//Summary: Removes the last element in the list and returns its data
//assigns pDel to node before head, rewires connections as if pDel were deleted
//returns pDel data and then frees
//O(1)

void *removeLast(LIST *lp){
	assert(lp != NULL && lp->count > 0);

	NODE *head = lp->head;
	NODE *pDel = lp->head->prev;

	pDel->prev->next = head;
	head->prev = pDel->prev;
	
	void *data = pDel->data;
	free(pDel);
	lp->count--;
	return data;
}

//GET FIRST
//Summary: returns the first node (node after head)
//O(1)

void *getFirst(LIST *lp){
	assert(lp != NULL && lp->count > 0);
	NODE *head = lp->head;

	return head->next->data;
}

//GET LAST
//Summary: returns the last node (node before head)
//O(1)

void *getLast(LIST *lp){
	assert(lp != NULL && lp->count > 0);
	NODE *head = lp->head;

	return head->prev->data;
}

//REMOVE ITEM
//Summary: removes a specific node from a given list and data
//traverses list until node with corresponding data is found
//if found, rewires connections and deletes node from the list
//O(n)

void removeItem(LIST *lp, void *item){
	assert(lp != NULL && lp->compare != NULL && lp->count > 0);
	int i;
	NODE *pDel = lp->head->next;

	for(i=0;i<lp->count;i++){
		if(lp->compare(pDel->data,item)==0){
			pDel->next->prev = pDel->prev;
			pDel->prev->next = pDel->next;
			free(pDel);
			lp->count--;
			break;
		}
		else{
			pDel = pDel->next;
		}
	}
}

//FIND ITEM
//Summary: Traverses the given list looking for given item
//If found, return data. If not found, returns NULL
//O(n)

void *findItem(LIST *lp, void *item){
	assert(lp != NULL && lp->compare != NULL);
	int i;
	NODE *pNode = lp->head->next;

	for(i=0;i<lp->count;i++){
		if(lp->compare(pNode->data,item)==0){
			return pNode->data;
		}
		else{
			pNode = pNode->next;
		}
	}
	return NULL;
}

//GET ITEMS
//Summary: allocates memory for a new array that will hold all of the items in the list
//Travers entire linked list until all data is in the array
//O(n)

void *getItems(LIST *lp){
	assert(lp != NULL);
	void **array;
	array = malloc(sizeof(void*)*lp->count);
	int i;
	NODE *pNode = lp->head->next;

	for(i=0;i<lp->count;i++){
		array[i] = pNode->data;
		pNode = pNode->next;
	}

	return array;
}

