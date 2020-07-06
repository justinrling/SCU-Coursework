#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1
#define DUM_CHAR 'A'

double copier(FILE *s_file, FILE *d_file){ //copy function
	char buff;
	
	buff = fgetc(s_file);	//instantiate buffer with source file
	while(buff != EOF){		//traverse file and copy to destination file
		fputc(buff, d_file);
		buff = fgetc(s_file);
	}

	printf("Copied.\n");

	fclose(s_file);	//close files
	fclose(d_file);

	return 0;
}

int main(int argc, char *argv[]){
	int option;
	int file_size, step_size;
	int current_size = 0;
	clock_t start, end;
	double cpu_time_used;
	FILE *source, *dest;

	if (argc < 3){	//make sure two files are given
		printf("The name of the files are missing!\n");
		return 0;
	}

	printf("Options:\n");
	printf("Enter '1' to copy a file\n");
	printf("Enter '2' to measure the performance to file copy\n");
	scanf("%d", &option);

	if(option == 1){	//File copy
		source = fopen(argv[1], "r");
		dest = fopen(argv[2], "w");

		copier(source, dest);
		printf("Copied.\n");
	}
	else if(option == 2){	//File copy with performance measurement

		printf("What is the maximum file size?\n");
		scanf("%d", &file_size);
		printf("What is the step size?\n");
		scanf("%d", &step_size);
		
		int i = 0;
		while(current_size < file_size){	//loops through until file is completely copied
			source = fopen(argv[1], "w");	//create files
			current_size+=step_size;
			start = clock();
			for(i=0; i<current_size; i++){	//fills file for size amount
				fputc('a', source);
			}
			fclose(source);
			source = fopen(argv[1], "r");
			dest = fopen(argv[2], "w");
			copier(source, dest);	//call copy function
			end = clock();
			cpu_time_used = ((double)(end-start));	//calculate cpu time
			printf("It took %d long to copy this file.\n", end-start);
		}	
	}
	else{
		printf("Invalid option!");
		return 0;
	}

	return 0;
}
