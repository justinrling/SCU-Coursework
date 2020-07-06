// Vineet Joshi
// October 10, 2019
// copy.s
// This is my starter code for Lab3 of COEN 20.

// If you have never encountered void pointers before:
// 		A void pointer is a pointer that has no associated data type with it.
// 		A void pointer can hold address of any type and can be typcasted to any type.
// (Source: "GeeksforGeeks")

		.syntax		unified
		.cpu		cortex-m4
		.text
		
		.global		UseLDRB
		.thumb_func
		// void UseLDRB(void *dst, void *src);
UseLDRB:
		// TODO: Write your Assembly code for the 'UseLDRB' function.
		.rept 512	//Copy 512 bytes, 1 byte at a time
		LDRB R2, [R1], 1	//load register with src and offset by 1
		STRB R2, [R0], 1	//store value into dst and offset by 1
		.endr
			
		BX LR
		
		
		.global		UseLDRH
		.thumb_func
		// void UseLDRH(void *dst, void *src);
UseLDRH:
		// TODO: Write your Assembly code for the 'UseLDRH' function.
		.rept 256	//Copy 512 bytes, 2 bytes at a time
		LDRH R3, [R1], 2	//load register with src and offset by 2
		STRH R3, [R0], 2	//store value into dst and offset by 2
		.endr
			
		BX LR
		
		
		.global		UseLDR
		.thumb_func
		// void UseLDR(void *dst, void *src);
UseLDR:
		// TODO: Write your Assembly code for the 'UseLDR' function.
		.rept 128	//Copy 512 bytes, 4 bytes at a time
		LDR R3, [R1], 4		//load register with src and offset by 4
		STR R3, [R0], 4		//store value into dst and offset by 4
		.endr
			
		BX LR
		
		
		.global		UseLDRD
		.thumb_func
		// void UseLDRD(void *dst, void *src);
UseLDRD:
		// TODO: Write your Assembly code for the 'UseLDRD' function.
		.rept 64	//Copy 512 bytes, 8 bytes at a time
		LDRD R3, R2, [R1], 8	//load register with src and offset by 8
		STRD R3, R2, [R0], 8	//store value into dst and offset by 8
		.endr
			
		BX LR
		
		
		.global		UseLDM
		.thumb_func
		// void UseLDM(void *dst, void *src);
UseLDM:
		// TODO: Write your Assembly code for the 'UseLDM' function.
		PUSH {R4-R9}	//push registers that will be used
		.rept 16	//Copy 512 bytes, 32 bytes at a time
		LDMIA R1!, {R2-R9}	//Copy memory to registers, increments and updates itself
		STMIA R0!, {R2-R9}	//Copy from registers to memory, increments and updates itself
		.endr
		POP {R4-R9}	//pop registers
		BX LR
		.end