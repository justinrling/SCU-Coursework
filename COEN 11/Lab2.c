#include <stdio.h>	//including libraries
#include <stdlib.h>
#include <string.h>

#define SIZE 10	//size and length of arrays
#define LENGTH 20

void insert();	//functions declared
void delete();
void list();

int groupSize[SIZE];	//global variables and arrays
char names[SIZE][LENGTH];
int counter = 0;
int option;

int main(void){	//parameters:void return:nothing Does:switch case option list

	printf("Restaraunt Commands: \n");
	printf("Press \"1\" to add your name and group size to the list \n");
	printf("Press \"2\" to remove the oldest entry of the size of the opening \n");
	printf("Press \"3\" to show the list \n");
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
			case 0:
				return 1;
		}
	}
}

void insert(){	//parameters:none return:none Does: checks if list is full and adds groups to list
	int i,j, number;
	char name[LENGTH];

	if(counter == SIZE)
		printf("Sorry, the list is full!\n");
	else{
		printf("What is your name?\n");
		scanf("%s", name);
		printf("How many are in your group?\n");
		scanf("%d", &number);

		strcpy(names[counter], name);
		groupSize[counter] = number;

		counter++;
	}
}

void delete(){	//parameters:none return:none Does:removes party size(if any) and shifts both arrays up
	int removed, i, j;
	
	if(counter == 0)
		printf("Sorry there are no parties to remove\n");
	else{
		printf("What size group did you want to remove?\n");
		scanf("%d", &removed);

		for(i=0;i<SIZE;i++){
			if(groupSize[i] == removed){
				printf("%s for %d has been removed\n",names[i],groupSize[i]);
				for(j=i;j<SIZE+1;j++){
					groupSize[j] = groupSize[j+1];
					strcpy(names[j], names[j+1]);
				}
			counter--;
			break;
			}
			else
				printf("Unable to find a party with that size\n");
				break;			
		}
	}
}

void list(){	//paramneters:none return:none Does: lists people
	int i;
	
	for(i=0;i<counter;i++){
		printf("%s for party of %d\n",names[i],groupSize[i]);
	}
}

