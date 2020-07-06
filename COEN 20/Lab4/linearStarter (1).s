		.syntax		unified
		.cpu		cortex-m4
		.text
		.global		MxPlusB
		.thumb_func
		// int32_t MxPlusB(int32_t x, int32_t mtop, int32_t mbtm, int32_t b);
		// Equation: y = mx + b, where m = mtop / mbtm.
		// Compute the value of y, and return it.
		// HINT: To compute value of m, use the equation at the bottom of the lab PDF!		
MxPlusB:
		PUSH {R4, R5}
		
		MUL R1, R0, R1			//x times mtop = dividend
		SMULL R5, R4, R1, R2 	//dividend times divisor
		ASR R4, R4, 31			//sign extension of above
		MUL R4, R4, R2 			//above times divisor
		LSL R4, R4, 1			//shift left 1
		ADDS R4, R4, R2			//add divisor
		LDR R5, =2				//load 2 into R5
		
		SDIV R4, R4, R5			//divide by 2 to round
		ADDS R4, R4, R1			//dividend + rounded
		SDIV R4, R4, R2			//above divided by divisor (mx)	
		ADDS R0, R4, R3			//mx + b
		
		POP {R4, R5}
		BX LR	
		.end