#include <stdio.h>	//include libraries
#include <stdlib.h>
#include <time.h>

int divide(int a, int b, int c){	//divide function
	int answer;
	       
	printf("\nWhat is %d/%d?",a, b);
	scanf("%d", &answer);
	         
	if(answer == c){
		return 1;
	}
	else
		return 0;
	}

int main(void){
	srand((int)time(NULL));
    int a,b,c,i;
	int counter = 0;
	int q = 0;


	for(i=0;i<9;i++){	//loops questions 10 times
		b = rand()%12 + 1;
		c = rand()%13;
		a = b*c;
		q = divide(a,b,c);	//calls function and tests answer
		if(q == 1){
			printf("\nCorrect");
			counter++;
		}
		else{
			printf("\nIncorrect! The answer is %d",c);
		}
	}
	
	printf("\nYou scored %d out of 10", counter);
	

}




