#include "Lab10.h"

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
				
void insert(char *name, int number){	//parameters:name and size return:none Does: adds groups to end of list
	NODE *p;
	NODE *temp;

	if((temp = (NODE *) malloc (sizeof (NODE))) == NULL){
		printf("no memory\n");
		return;
	}
	
	strcpy(temp->name, name);
	temp->group = number;

	pthread_mutex_lock(&mutex);
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
	pthread_mutex_unlock(&mutex);
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
	pthread_mutex_lock(&mutex);
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
			pthread_mutex_unlock(&mutex);
			return;
		}
		else if(p == x[i].tail){
			printf("%s party of %d has been removed\n", p->name, p->group);
			x[i].tail = q;
			q->next = NULL;
			free(p);
			flag = 1;
			pthread_mutex_unlock(&mutex);
			return;
		}
		else{
			printf("%s party of %d has been removed\n", p->name, p->group);
			q->next = p-> next;
			free(p);
			flag = 1;
			pthread_mutex_unlock(&mutex);
			return;
		}
	}
	pthread_mutex_unlock(&mutex);
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
void clearList(){    //parameters:none return:none Does: calls recursive function to clear list of people
	NODE *p;
	int i;
	
	pthread_mutex_lock(&mutex);	
	for(i=0; i<4; i++){
		p = x[i].head;
		if(p == NULL)
			continue;
		else
			clearlistRecursive(p);
	}
	pthread_mutex_unlock(&mutex);
}

void clearlistRecursive(NODE *p){	//recursive delete function
	if(p == NULL)
		return;
	else{
		clearlistRecursive(p->next);
		printf("deleting %s\n", p->name);
		free(p);
	}
}

void listBack(){	//parameters: none does: calls recursive function (reverse) to display list backwards
	NODE *p;
	int i;
	for(i=0;i<4;i++){
		p = x[i].head;
		if(p == NULL){
			continue;
		}
		else{
			reverseList(p);
		}
	}
}

void namesBack(){	//parameters: none does: calls recursive function (reverse) to display names backwards
	NODE *p;
	int i;

	for(i=0; i<4; i++){
		p = x[i].head;
		if(p == NULL){
			continue;
		}
		else{
			while(p != NULL){
				reverseNames(p->name);
				p = p->next;
				printf("\n");
			}
		}
	}
}

void reverseNames(char *q){	//recursive backward name function Parameters:character of name
	if(*q == '\0')
		return;
	else{
		reverseNames(q+1);
		printf("%c", *q);
	}
}

void reverseList(NODE *p){	//recursive backward list function Parameters:each node of each list
	if(p == NULL)
		return;
	reverseList(p->next);
	printf("%s party of %d\n", p->name, p->group);
}
