			.syntax		unified
			.cpu		cortex-m4
			.text		
			.global		GetNibble
			.thumb_func
			// uint32_t GetNibble(void *nibbles, uint32_t which);
GetNibble:
			LSRS R1, R1, 1		//index = index/2 with remainder in the carry flag
			LDRB R3, [R0, R1]	//load byte in array incremented by R1 into R3
			
			ITE CS
			LSRCS R3, 4			//if carry flag is 1, R3 is divided by 16
			ANDCC R3, R3, 0b00001111	//if carry flag is 0, clear the most significant nibble
			
			MOV R0, R3			//copy R3 to R0
			
			BX LR		
	
			.global		PutNibble
			.thumb_func
			// void PutNibble(void *nibbles, uint32_t which, uint32_t value);
PutNibble:
			LSRS R1, R1, 1		//index = index/2 with remainder in the carry flag
			LDRB R3, [R0, R1]	//R3 is byte with desired nibble R0 incremented by the R1 offset
			
			ITTE CS
			ANDCS R3, R3, 0b00001111		//if carry flag is 1, clear MSnibble
			LSLCS R2, R2, 4					//move nibble data to most signifcant nibble by multiplying by 16
			ANDCC R3, R3, 0b11110000		//if carry flag is 0, clear the least significant nibble
			
			ORR R2, R2, R3
			STRB R2, [R0, R1]				//R0 array incremented by R1 = R2 
			
			BX LR
			.end