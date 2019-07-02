#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "pqueue.h"
#include "pack.h"
#define NODE struct node
#define END 256

//Global arrays to store frequency and nodes of Huffman tree
NODE *nodes[END+1];
int counts[END+1];

//Creates new NODE and assigns parent
//O(1)
static NODE *mknode(int data, NODE *left, NODE *right){
	NODE *np = malloc(sizeof(NODE));
	assert(np != NULL);

	np->count = data;
	if(left != NULL)
		left->parent = np;
	if(right != NULL)
		right->parent = np;

	return np;
}

//Returns the level in which a node is on
//O(logn)
int depth(NODE *target){
	assert(target != NULL);
	int depth = 0;

	while(target->parent != NULL){
		target= target->parent;
		depth++;
	}
	return depth;
}

//Compare method to be passed into Priority Queue
//O(1)
int nodeCompare(NODE *np1, NODE *np2){
	assert(np1 != NULL && np2 != NULL);

	if(np1->count < np2->count)
		return -1;
	if(np1->count == np2->count)
		return 0;
	else
		return 1;
}

int main(int argc, char *argv[]){
	FILE *fp;
	struct pqueue *pq;
	int character = 0;
	int d;
	NODE *left, *right;

	if(argc != 3){		//check input information
		printf("Please input two files");
		exit(EXIT_FAILURE);
	}
	if((fp = fopen(argv[1], "rb")) == NULL){
		printf("Unable to read file\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("Processing...\n");
	
	pq = createQueue(nodeCompare);

	for(int i=0;i<=END+1;i++){	//initializes global arrays
		counts[i] = 0;
		nodes[i] = NULL;
	}

	while((character = getc(fp)) != EOF){	//counts frequences of characters until EOF
		counts[character]++;
	}

	for(int i=0;i<END+1;i++){	//creates leaf nodes
		if(counts[i] > 0){
			nodes[i] = mknode(counts[i], NULL, NULL);
			addEntry(pq, nodes[i]);
		}
	}

	nodes[END] = mknode(0, NULL, NULL);		//assign last node to be the end of file
	addEntry(pq, nodes[END]);


	while(numEntries(pq) > 1){		//build Huffman tree from Priority Queue
		left = removeEntry(pq);
		right = removeEntry(pq);
		addEntry(pq, mknode(left->count + right->count, left, right));
	}

	for(int i=0;i<END+1;i++){
		if(nodes[i] != NULL){
			d = depth(nodes[i]);
		
			if(isprint(i))	//issue with isprint -> leads to segmentation fault
				printf("\'%c\'", i);
			else
				printf("%03o", i);

			printf(": %d x %d bits = %d bits\n", counts[i], d, d*counts[i]);
			}
	}

	pack(argv[1], argv[2], nodes);
}
	
			
