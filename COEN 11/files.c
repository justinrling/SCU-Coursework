#include "Lab10.h"

void read_file(char *filename, char key){	//parameters: file name ouput: transfers file info into waiting list 
	FILE *fp;
	char name[20];
	int number;
	char *q;
	char buffer[200];

	fp = fopen(filename, "r");
	if(fp == NULL)
		return;
	while(fgets(buffer, 200, fp) != NULL){	//decrypt
		q = buffer;
		while(*q !='\n'){
			*q ^= key;
			q++;
		}
		sscanf(buffer,"%s%d",name, &number);//for function to show encryption just printf the buffer
		insert(name, number);
	}
	fclose(fp);
	return;
}

void save_file(char *filename, char key){	//parameters: file name output: rewrites file after program closes
	FILE *fp;
	NODE *p;
	int i;
	char buffer[200];
	char *q;

	fp = fopen(filename, "w");
	if(fp == NULL)
		return;
	for(i=0;i<4;i++){	//encrypt
		p = x[i].head;
		while(p != NULL){
			sprintf(buffer,"%s\t%d\n",p->name, p->group);
			q = buffer;
			while(*q != '\0'){
				*q ^= key;
				q++;
			}
			fprintf(fp, "%s\n", buffer);
			p = p->next;
		}
	}
	fclose(fp);
	return;
}

void read_binary(void *arg){	//reads binary file and shows user
	FILE *fp;
	int r;
	NODE temp;
  
	pthread_mutex_lock(&mutex);
	fp = fopen(arg, "rb");
    	if(fp == NULL){
			pthread_mutex_unlock(&mutex);
	    	return;
		}
    	while((r = fread(&temp,sizeof(NODE),1,fp)>0))
			printf("%s party of %d\n", temp.name, temp.group);
    fclose(fp);
	pthread_mutex_unlock(&mutex);
    return;
}

void *save_binary(void *arg){	//autosaves list to binary file every 15 seconds
	char *fname = (char*)arg;
	FILE *fp;
	int i;
	NODE *p;

	while(1){
		sleep(15);
		printf("Saving...\n");
		pthread_mutex_lock(&mutex);
		fp = fopen(fname,"wb");
		if(fp == NULL){
			pthread_mutex_unlock(&mutex);
			return NULL;
		}
		for(i = 0; i<4; i++){
			p = x[i].head;
			while( p != NULL){
				fwrite(p, sizeof(NODE), 1, fp);
				p = p->next;
			}
		}
		fclose(fp);
		printf("Done Saving\n");
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

