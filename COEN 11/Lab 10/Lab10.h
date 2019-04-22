#include <stdio.h>	//including libraries
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 10	//size and length of arrays
#define LENGTH 20
#define NODE struct node

struct node{	//declare node
	char name[20];
	int group;
	NODE *next;
};

struct list{
	NODE *head;	//declare head and tail
	NODE *tail;	
};

extern struct list x[4];

void insert(char *name, int number);	//functions declared
void delete();
void list();
void clearList();
void search_size();
int check_duplicate(char *groupName);
void read_file(char *filename, char key);
void save_file(char *filename, char key);
extern int option;
void listBack();
void namesBack();
void reverseList(NODE *p);
void reverseNames(char *q);
void clearlistRecursive(NODE *p);
void *save_binary(void *arg);
void read_binary(void *arg);

extern pthread_mutex_t mutex;	//thread global variables
extern pthread_t thread;


