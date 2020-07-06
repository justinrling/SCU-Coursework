				.syntax		unified
				.cpu		cortex-m4
				.text		
				.global		Discriminant
				.thumb_func
				// float Discriminant(float a, float b, float c);
Discriminant:
				VMOV S3, 4.0
				VMUL.F32 S0, S0, S2	// AC -> S0
				VMUL.F32 S0, S0, S3
				VNEG.F32 S0, S0
				VMLA.F32 S0, S1, S1 //B^2 -> S1
				
				BX LR
			
				.global		Quadratic
				.thumb_func
				// float Quadratic(float x, float a, float b, float c);
Quadratic:
				VMUL.F32 S4, S0, S0	//X^2
				VMUL.F32 S1, S1, S4	//AX^2
				VMUL.F32 S2, S2, S0
				VADD.F32 S1, S1, S2
				VADD.F32 S0, S1, S3
				
				BX LR
			
				.global		Root1
				.thumb_func
				// float Root1(float a, float b, float c);
Root1:
				PUSH {LR}
				VPUSH {S4, S5}
				VMOV S6, 2.0
				VMUL.F32 S4, S0, S6	//2A -> S4
				VNEG.F32 S5, S1	//-B -> S5
				BL Discriminant
				
				VSQRT.F32 S0, S0	//Square Root of Discriminant
				VADD.F32 S0, S0, S5	//add -B
				VDIV.F32 S0, S0, S4
				VPOP {S4, S5}
				
				POP {PC}
				
				.global		Root2
				.thumb_func
				// float Root2(float a, float b, float c);
Root2:
				PUSH {LR}
				VPUSH {S4, S5}
				VMOV S6, 2.0
				VMUL.F32 S4, S0, S6	//2A -> S4
				VNEG.F32 S5, S1	//-B -> S5
				BL Discriminant
				
				VSQRT.F32 S0, S0	//Square Root of Discriminant
				VSUB.F32 S0, S5, S0	//add -B
				VDIV.F32 S0, S0, S4
				VPOP {S4, S5}
				
				POP {PC}	
				.end
				