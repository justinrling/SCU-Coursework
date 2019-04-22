#include "Lab10.h"

struct list x[4] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};

int option;
pthread_mutex_t mutex;   //thread global variables
pthread_t thread;

int main(int argc, char *argv[]){	//parameters:file return:nothing Does:switch case option list
	char name[20];
	int number;
	int key = atoi(argv[3]);

	if(argc < 4){
		printf("The name of the files are missing!\n");
		return 1;
	}
	read_file(argv[1], (char)key);

	printf("Restaraunt Commands: \n");
	printf("Press \"1\" to add your name and group size to the list \n");
	printf("Press \"2\" to remove the oldest entry of the size of the opening \n");
	printf("Press \"3\" to show the list \n");
	printf("Press \"4\" to search for group size\n");
	printf("Press \"5\" to display the list backwards\n");
	printf("Press \"6\" to display each name backwards\n");
	printf("Press \"7\" to read the binary file\n");
	printf("Press \"0\" to quit \n");
	
	pthread_mutex_init(&mutex, NULL);	//init and create thread
	pthread_create(&thread, NULL, save_binary, (void*)argv[2]);

	while(1){
		scanf("%d", &option);
		
		switch(option){
			case 1:
				printf("What is your name?\n");
				scanf("%s", name);
					if(check_duplicate(name) == 1){
						printf("Sorry that name is already in use\n");
						return 1;
					  }
				printf("How many people are in your party?\n");
				scanf("%d", &number);
				
				insert(name, number);
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
			case 5:
				listBack();
				break;
			case 6:
				namesBack();
				break;
			case 7:
				read_binary(argv[2]);
				break;
			case 0:	//copy list to text file
				pthread_mutex_lock(&mutex);
				pthread_cancel(thread);
				pthread_mutex_unlock(&mutex);
				save_file(argv[1], (char)key);
				clearList();
				return 1;
			default:
				printf("invalid option\n");
				break;
		}
	}
}
