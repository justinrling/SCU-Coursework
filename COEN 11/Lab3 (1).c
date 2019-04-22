#include <stdio.h>	//including libraries
#include <stdlib.h>
#include <string.h>

#define SIZE 10	//size and length of arrays
#define LENGTH 20

typedef struct entry{	//structure
	char names[LENGTH];
	int groupSize;
}ENTRY;

void insert();	//functions declared
void delete();
void list();
void search_size();
int check_duplicate(char *groupName);

ENTRY waitingList[10];
int counter = 0;
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
		}
	}
}
int check_duplicate(char *groupName){	//parameters: pointer groupName return: 1 if duplicate, 0 if not Does: checks structure array for duplicates
	int i;
	ENTRY *p = waitingList;

	for(i=0;i<10;i++,p++){
		if(strcmp(groupName,p->names) == 0)
		 	return 1;
	}
	return 0;
}
				
void insert(){	//parameters:none return:none Does: checks if list is full and adds groups to list
	int i,j, number;
	char name[LENGTH];

	if(counter == SIZE)
		printf("Sorry, the list is full!\n");
	else{
		printf("What is your name?\n");
		scanf("%s", name);

		if(check_duplicate(name) == 1){
			printf("Sorry that name is already in use\n");
			return;
		}
		else{
			printf("How many are in your group?\n");
			scanf("%d", &number);
		}
		strcpy(waitingList[counter].names, name);
		waitingList[counter].groupSize = number;

		counter++;
	}
}

void delete(){	//parameters:none return:none Does:removes party size(if any) and shifts both arrays up
	int removed, i, j;
	int flag = 0;

	if(counter == 0)
		printf("Sorry there are no parties to remove\n");
	else{
		printf("What size group did you want to remove?\n");
		scanf("%d", &removed);

		for(i=0;i<10;i++){
			if(waitingList[i].groupSize == removed){
				printf("%s for %d has been removed\n",waitingList[i].names,waitingList[i].groupSize);
				for(j=i;j<SIZE+1;j++){
					waitingList[j].groupSize = waitingList[j+1].groupSize;
					strcpy(waitingList[j].names, waitingList[j+1].names);
				}
			counter--;
			flag = 1;
			break;
			}			
		}
		if(flag == 0)
			printf("Unable to find a party of that size\n");
	}
}

void list(){	//parameters:none return:none Does: lists people
	int i;
	ENTRY *p = waitingList;
	
	for(i=0;i<counter;i++,p++){
		printf("%s for party of %d\n",p->names,p->groupSize);
	}
}

void search_size(){		//parameters:none return:none Does: searches for sizes less than and equal to the number scanned
	int i;
	ENTRY *p = waitingList;
	int sizeSearch;

	if(counter == 0){
		printf("Sorry there are no groups on the waiting list\n");
		return;
	}
	else{
		printf("What group size are you looking for?\n");
		scanf("%d", &sizeSearch);
	
		for(i=0;i<counter;i++,p++){
			if(p->groupSize <= sizeSearch)
				printf("%s for party of %d\n", p->names, p->groupSize);
		}
	}
}
