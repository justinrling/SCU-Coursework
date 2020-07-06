		.syntax		unified
		.cpu		cortex-m4
		.text
		
		.global		WritePixel
		.thumb_func
		// void WritePixel(int x, int y, uint8_t colorIndex, uint8_t frameBuffer[256][240]);
WritePixel:
		// TODO: Write your Assembly code for the 'WritePixel' function.
		PUSH {R4}
		LDR R4, =240		//constant to be multiplied by (for frame buffer)
		MUL R1, R1, R4		//y*240
		ADD R1, R1, R0		//add x
		ADD R1, R1, R3		//add frameBuffer
		STR R2, [R1]
		POP {R4}
		BX LR
		
		.global		BitmapAddress
		.thumb_func
		// uint8_t *BitmapAddress(char ascii, uint8_t *fontTable, int height, int width);
BitmapAddress:
		// TODO: Write your Assembly code for the 'BitmapAddress' function.
		ADD R3, R3, 7		//add Y to width
		LSR R3, R3, 3 		//multiply by 8
		SUB R0, R0, ' '		//remove first space
		MUL R2, R3, R2		//height times width
		MLA R0, R2, R0, R1	//(height*width) * ascii + *fontTable
		BX LR
		
		.global		GetBitmapRow
		.thumb_func
		// uint32_t GetBitmapRow(uint8_t *rowAdrs);
GetBitmapRow:
		// TODO: Write your Assembly code for the 'GetBitmapRow' function.
		LDR R0, [R0]		//load value of rowAdrs into R0
		REV R0, R0
		BX LR
		
		.end