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

struct list{
	NODE *head;	//declare head and tail
	NODE *tail;	
};

struct list x[4] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};

void insert();	//functions declared
void delete();
void list();
void clearList();
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
				clearList();
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
	int i;

	for(i=0; i<4; i++){
		p = x[i].head;
		while(p != NULL){
			if(strcmp(groupName, p->name) == 0)
				flag = 1;
			p = p->next;
		}
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

	if(number <=2 && number >=1){
		p = x[0].head;
		while(p != NULL){
			p = p->next;
		}
		if(x[0].head == NULL){
			temp->next = NULL;
			x[0].head = temp;
			x[0].tail = temp;
		}
		else{
			temp->next = NULL;
			x[0].tail->next = temp;
			x[0].tail = temp;
		}
	}
	else if(number <=4 && number >=3){
		p = x[1].head;
		while(p != NULL){
			p = p->next;
		}
		if(x[1].head == NULL){
			temp->next = NULL;
			x[1].head = temp;
			x[1].tail = temp;
		}
		else{
			temp->next = NULL;
			x[1].tail->next = temp;
			x[1].tail = temp;
		}
	}
	else if(number <=6 && number >= 5){
		p = x[2].head;
		while(p != NULL){
			p = p->next;
		}
		if(x[2].head == NULL){
			temp->next = NULL;
			x[2].head = temp;
			x[2].tail = temp;
		}
		else{
			temp->next = NULL;
			x[2].tail->next = temp;
			x[2].tail = temp;
		}
	}
	else if(number > 6){
		p = x[3].head;
		while(p != NULL){
			p = p->next;
		}
		if(x[3].head == NULL){
			temp->next = NULL;
			x[3].head = temp;
			x[3].tail = temp;
		}
		else{
			temp->next = NULL;
			x[3].tail->next = temp;
			x[3].tail = temp;
		}
	}
}


void delete(){	//parameters:none return:none Does:removes party size(if any)
	NODE *p, *q;
	int removed, i, j, flag;

	printf("What size of group did you want to remove?\n");
	scanf("%d", &removed);

	if(removed > 6)
		j = 3;
	else if(removed >= 5 && removed <= 6)
		j = 2;
	else if(removed >= 3 && removed <= 4)
		j = 1;
	else if(removed >=1 && removed <=2)
		j = 0;

	flag = 0;
	for(i = 0; i <= j ; i++){	
		p = q = x[i].head;
		while(p != NULL && p->group > removed){
			q = p;
			p = p->next;
		}
		if(p == NULL){
			continue;
		}
		if(p == x[i].head){	//first node of list
			printf("%s party of %d has been removed\n", p->name, p->group);
			x[i].head = p->next;
			free(p);
			flag = 1;
			return;
		}
		else if(p == x[i].tail){
			printf("%s party of %d has been removed\n", p->name, p->group);
			x[i].tail = q;
			q->next = NULL;
			free(p);
			flag = 1;
			return;
		}
		else{
			printf("%s party of %d has been removed\n", p->name, p->group);
			q->next = p-> next;
			free(p);
			flag = 1;
			return;
		}
	}
	if(flag == 0){
		printf("Sorry your size was not found\n");
	}
}
			

void list(){	//parameters:none return:none Does: lists people
	NODE *p;
	int i;
	
	for(i=0; i<4; i++){
		p = x[i].head;
		while(p != NULL){
			printf("%s party of %d\n", p->name, p->group);
			p = p->next;
		}
	}
}	

void search_size(){		//parameters:none return:none Does: searches for sizes less than and equal to the number scanned
	NODE *p, *q;
	int searchSize, i, j;

	printf("What group size are you looking for?\n");
	scanf("%d", &searchSize);

	if(searchSize > 6)
		j = 3;
	else if(searchSize >=5 && searchSize <=6)
		j = 2;
	else if(searchSize >=3 && searchSize <=4)
		j = 1;
	else if(searchSize >=1 && searchSize <=2)
		j = 0;

	for(i=0;i<=j;i++){
		p = x[i].head;
		while(p != NULL){
			printf("%s party of %d\n", p->name, p->group);
			p = p->next;
		}
	}
}
void clearList(){    //parameters:none return:none Does: clears list of people
	NODE *p, *q;
	int i;
	 
	for(i=0; i<4; i++){
		p = q = x[i].head;
		while(p != NULL){
			q = p;
			p = p->next;
			free(q);
		}
	}
}
