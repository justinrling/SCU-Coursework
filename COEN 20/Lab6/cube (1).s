		.syntax		unified
		.cpu		cortex-m4
		.text
		.global		MatrixMultiply
		.thumb_func
		// void MatrixMultiply(int32_t a[3][3], int32_t b[3][3], int32_t c[3][3]);
MatrixMultiply: 
			PUSH {R4-R10, LR}
			
			MOV R4, R0		//copy a[][] to R4
			MOV R5, R1		//copy b[][] to R5
			MOV R6, R2		//copy c[][] to R6
			
			MOV R7, 0		//set row to 0
Top1:		CMP R7, 3
			BGE End
			
			MOV R8, 0		//set col to 0
Top2:		CMP R8, 3
			BGE Btm1
			
			MOV R3, 3
			MLA R3, R3, R7, R8	//3*row+col
			MOV R1, 0		//set R1 to constant 0
			STR R1,[R4, R3, LSL 2]		//setting A[][] to 0
			
			MOV R9,0		//set k to 0
			
Top3:		CMP R9, 3
			BGE Btm2
			
			MOV R3, 3
			MLA R3, R3, R7, R8		//(3*row) + col
			LDR R0, [R4, R3, LSL 2]	//storing A[][] incremented by offset to R0
			
			MOV R3, 3
			MLA R3, R7, R3, R9 		//R1 = (3*row) + k
			LDR R1, [R5, R3, LSL 2]	//storing B[][] incremented by offset to R1
			
			MOV R3, 3
			MLA R3, R9, R3, R8		//R2 = (3*row) + col
			LDR R2, [R6, R3, LSL 2]	//Storing C[][] incremented by offset to R2
			
			BL MultAndAdd			//call MultAndAdd function with R0, R1, R2
			
			MOV R3, 3
			MLA R3, R3, R7, R8		//(3*row) + col
			STR R0, [R4, R3, LSL 2]	//store answer in A[][] incremented by offset stored in R10
			
			ADD R9, R9, 1			//increment k
			BL Top3					//repeat until k > 3

Btm1:		ADD R7, R7, 1			//increment row
			B Top1
			
Btm2:		Add R8, R8, 1			//increment col
			B Top2
			
End:		POP {R4-R10,PC}	
		.end