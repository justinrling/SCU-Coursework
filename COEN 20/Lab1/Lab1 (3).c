#include <stdio.h>
#include <math.h>

int32_t Bits2Signed(int8_t bits[8]) ; // Convert array of bits to signed int.
uint32_t Bits2Unsigned(int8_t bits[8]) ; // Convert array of bits to unsigned int
void Increment(int8_t bits[8]) ; // Add 1 to value represented by bit pattern
void Unsigned2Bits(uint32_t n, int8_t bits[8]) ; // Opposite of Bits2Unsigned

uint32_t Bits2Unsigned(int8_t bits[8]){		// Convert array of bits to unsigned int
	int i;
	int num = 0;
	
	for(i=7; i>=0; i--){		//traverse each bit position from left to right
		num = (2*num+bits[i]);	//compute integer value of binary
	}
	return num;
}

int32_t Bits2Signed(int8_t bits[8]){		// Convert array of bits to signed int.
	int num = Bits2Unsigned(bits);		//call Bits2Unsigned for integer value
	
	if(num > 127){		//if integer is greater than 127, it is then negative
		num -= 256;		//subtract 255 from value to obtain negative value
	}
	
	return num;
}

void Unsigned2Bits(uint32_t n, int8_t bits[8]){		// Opposite of Bits2Unsigned
	int r, i;
	int q = n;
	
	for(i=0; i<8; i++){		//divides integer by two 8 times and places remainder in 
		r = q%2;			//correct bit position (from right to left)
		q = q/2;			//quotient divides down to zero
		bits[i] = r;
	}
}

void Increment(int8_t bits[8]){			// Add 1 to value represented by bit pattern
	int i;
	
	for(i=0; i<8; i++){		//travers 8 bit value for first 0 and changes it to a 1
		if(bits[i] == 0){
			bits[i] = 1;
			break;		//breaks for loop when 0 is found
		}
	}
	
	for(i=(i-1); i>=0; i--){	//traverses all the "1's" passed before hitting a 0
		bits[i] = 0;			//and changes them to "0's"
	}
}

