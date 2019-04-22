#include <stdio.h>	//including libraries
#include <stdlib.h>
#include <string.h>

#define SIZE 10	//size and length of arrays
#define LENGTH 20
#define NODE struct node

struct node{	//declare node
	char name[20];
	int group;
	NODE *next;
};


NODE *head = NULL;	//declare head and tail
NODE *tail = NULL;

void insert();	//functions declared
void delete();
void list();
void search_size();
int check_duplicate(char *groupName);

int option;

int main(){	//parameters:void return:nothing Does:switch case option list

	printf("Restaraunt Commands: \n");
	printf("Press \"1\" to add your name and group size to the list \n");
	printf("Press \"2\" to remove the oldest entry of the size of the opening \n");
	printf("Press \"3\" to show the list \n");
	printf("Pres \"4\" to search for group size\n");
	printf("Press \"0\" to quit \n");
	
	while(1){
		scanf("%d", &option);
		
		switch(option){
			case 1:
				insert();
				break;
			case 2:
				delete();
				break;
			case 3:
				list();
				break;
			case 4:
				search_size();
				break;
			case 0:
				return 1;
			default:
				printf("invalid option\n");
				break;
		}
	}
}
int check_duplicate(char *groupName){	//parameters: pointer groupName return: 1 if duplicate, 0 if not Does: checks linked list for duplicate name
	
	NODE *p;
	int flag = 0;

	while(p != NULL){
		if(strcmp(groupName, p->name) == 0)
			flag = 1;
			p = p->next;
	}
	if(flag == 1)
		return 1;
	else
		return 0;
}
				
void insert(){	//parameters:none return:none Does: adds groups to end of list
	NODE *p;
	NODE *temp;
	char name[20];
	int number;

	if((temp = (NODE *) malloc (sizeof (NODE))) == NULL){
			printf("no memory\n");
			return;
	}

	printf("What is your name?\n");
	scanf("%s", name);
	if(check_duplicate(name) == 1){
		printf("Sorry that name is already in use\n");
		return;
	}
	printf("How many people are in your party?\n");
	scanf("%d", &number);
	
	strcpy(temp->name, name);
	temp->group = number;
	
	if(head == NULL){
		head = temp;
		tail = temp;
		temp->next = NULL;
	}
	else{
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
}

void delete(){	//parameters:none return:none Does:removes party size(if any)
	NODE *p, *q;
	int removed;

	p = q = head;
	if(head == NULL){
		printf("Sorry the list is empty\n");
		return;
	}
	
	printf("What size of group did you want to remove?\n");
	scanf("%d", &removed);
	
	while(p != NULL && p->group != removed){
		q = p;
		p = p->next;
	}
	if(p == NULL || p->group != removed){
		printf("Party of \"%d\" is not in the list\n", removed);
		return;
	}
	if(p == head){
		printf("%s party of %d has been removed\n", p->name, p->group);
		head = p->next;
	}
	else{
		printf("%s party of %d has been removed\n", p->name, p->group);
		q->next = p->next;
	}
	free(p);
	return;
}

void list(){	//parameters:none return:none Does: lists people
	NODE *p;

	p = head;
	if(p == NULL){
		printf("The list is empty\n");
		return;
	}
	while(p != NULL){
		printf("%s party of %d\n", p->name, p->group);
		p = p->next;
	}
}

void search_size(){		//parameters:none return:none Does: searches for sizes less than and equal to the number scanned
	NODE *p, *q;
	int sizeSearch;

	p = q = head;
	if(p == NULL){
		printf("Sorry there are no groups on the waiting list\n");
		return;
	}
	printf("What group size are you looking for?\n");
	scanf("%d", &sizeSearch);

	while(p != NULL){
		q = p;
		if(p->group <= sizeSearch)
			printf("%s for party of %d\n", p->name, p->group);
		p = p->next;	
	}
}
