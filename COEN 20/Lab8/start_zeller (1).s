		.syntax		unified
		.cpu		cortex-m4
		.text
		
		.global		Zeller1
		.thumb_func
		//                           R0          R1          R2          R3
		// uint32_t Zeller1(uint32_t k, uint32_t m, uint32_t D, uint32_t C);
		// This function can use multiply and divide instructions.
Zeller1:
		ADD R0, R0, R2			//f = k + D
		ADD R0, R0, R2, LSR 2	//f=k+D + D/4
		ADD R0, R0, R3, LSR 2	//f=k+D+(D/4) + C/4
	
		LSL R3, R3, 1			// R3 <- 2C
		SUB R0, R0, R3			// current f - 2C
		LDR R2, =13
		MUL R1, R1, R2			//13m
		LDR R2, =1
		SUB R1, R1, R2			//13m-1
		LDR R2, =5
		UDIV R1, R1, R2			//(13m-1)/5
		ADD R0, R0, R1			//f=(13m-1)/5 + k+D+(D/4)+(C/4)-2C
		
		LDR R3, =7
		SDIV R1, R0, R3			//R1 <- f/7
		MUL R1, R1, R3			//R1 <- R1 * 7
		SUB R1, R0, R1			//R1 <- f - R1
		
		CMP R1, 0
		IT LT
		ADDLT R0, R1, R3
		MOV R0, R1
		BX LR
		
		.global		Zeller2
		.thumb_func
		//                           R0          R1          R2          R3
		// uint32_t Zeller2(uint32_t k, uint32_t m, uint32_t D, uint32_t C);
		// This function CANNOT use divide instructions (SDIV or UDIV).
Zeller2:
		PUSH {R4}
		
		ADD R0, R0, R2			//f = k + D
		ADD R0, R0, R2, LSR 2	//f=k+D + D/4
		ADD R0, R0, R3, LSR 2	//f=k+D+(D/4) + C/4
	
		LSL R3, R3, 1			// R3 <- 2C
		SUB R0, R0, R3			// current f - 2C
		LDR R2, =13
		MUL R1, R1, R2			//13m
		LDR R2, =1
		SUB R1, R1, R2			//13m-1
		
		//2^N/K = 2^32/5 = 858993459.2
		LDR R3, =858993459 
		SMULL R2, R3, R1, R3	//reciprocol multiplication
		
		//R3 is most significant register
		
		ADD R0, R0, R3			//f=(13m-1)/5 + k+D+(D/4)+(C/4)-2C
		
		//2^32/7 = 613566756.571
		LDR R3, =613566756
		SMULL R2, R3, R0, R3	//reciprocol multiplication
		
		//R3 is most significant register
		
		LDR R4, =7
		MUL R3, R3, R4			//temp = temp*7
		SUB R3, R0, R3			//temp = f - temp
		
		CMP R3, 0
		IT LT
		ADDLT R0, R3, R4
		MOV R0, R3
		
		POP {R4}
		BX LR
		
		.global		Zeller3
		.thumb_func
		//                           R0          R1          R2          R3
		// uint32_t Zeller3(uint32_t k, uint32_t m, uint32_t D, uint32_t C);
		// This function CANNOT use multiply instructions (MUL, MLS, etc.).
Zeller3:
		ADD R0, R0, R2			//f = k + D
		ADD R0, R0, R2, LSR 2	//f=k+D + D/4
		ADD R0, R0, R3, LSR 2	//f=k+D+(D/4) + C/4
	
		LSL R3, R3, 1			// R3 <- 2C
		SUB R0, R0, R3			// current f - 2C
		
		ADD R3, R1, R1, LSL 3	//(m << 3) + m
		ADD R3, R3, R1, LSL 2	//above + (m << 2)
		LDR R2, =1
		SUB R3, R3, R2			//13m - 1
		
		LDR R2, =5
		UDIV R1, R3, R2			//(13m-1)/5
		ADD R0, R0, R1			//f=(13m-1)/5 + k+D+(D/4)+(C/4)-2C
		
		LDR R3, =7
		SDIV R1, R0, R3			//R1 <- f/7
		
		RSB R1, R1, R1, LSL 3	//R1 <- (R1<<3) - R1

		SUB R1, R0, R1			//R1 <- f - R1
		
		CMP R1, 0
		IT LT
		ADDLT R0, R1, R3
		MOV R0, R1
		BX LR
		.end