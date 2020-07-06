// functions.s
// This is my starter code for Lab2a of COEN 20.
		.syntax		unified
		.cpu		cortex-m4
		.text
	
		// int32_t Add(int32_t a, int32_t b);
		.global		Add
		.thumb_func
	Add:
		// TODO: Write your Assembly code for the 'Add' function.
		ADD R0, R1, R0	//Add R0 and R1 - store value in R0
		BX LR	//return
		// int32_t Less1(int32_t a);
		.global		Less1
		.thumb_func
	Less1:
		// TODO: Write your Assembly code for the 'Less1' function.
		SUB R0, R0, 1 //subtract constant value "1" from R0 and store in R0
		BX LR	//return
		// int32_t Square2x(int32_t x);
		.global		Square2x
		.thumb_func
	Square2x:
		// TODO: Write your Assembly code for the 'Square2x' function.
		ADD R0, R0, R0	//Add R0 to R0
		B Square	//Branch jump to square function
		// int32_t Last(int32_t x);
		.global		Last
		.thumb_func
	Last:
		// TODO: Write your Assembly code for the 'Last' function.
		PUSH {R4, LR}	//preserve R4
		MOV R4, R0	//keep x safe in R4
		BL SquareRoot	//Branch Link square root function
		ADD R0, R0, R4	//Add x to answer
		POP {R4, PC}	//Restore R4
		.end