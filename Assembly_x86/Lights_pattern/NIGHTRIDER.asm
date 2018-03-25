START:	   MVI L,01

	   MVI B,01

	   MVI C,80

	   MVI D,FF

	   MVI H,01


WHILELOOP1:	   MOV A,L
	   MOV A,H
	   CMP C
	   JZ WHILELOOP2
	   RLC	
	   OUT 00
	   MOV H,A	
                       	   MOV A,D
	   JMP DELAY1


DELAY1:	   
	   SUI 01	
	   CPI 00	
	   JNZ DELAY1
	   JZ WHILELOOP1


WHILELOOP2:	   MOV A,L
	   MOV A,H
	   CMP C
	   JZ DONE
	   RLC	
	   OUT 00
	   MOV H,A	
                       	   MOV A,D
	   JMP DELAY2

DELAY2:	   
	   SUI 01
	   CPI 00
	   JNZ DELAY2
	   JZ WHILELOOP2

DONE:	   JMP START
