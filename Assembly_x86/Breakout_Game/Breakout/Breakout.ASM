	.model tiny
	.code

start:
	
;;Clear screen

	mov ax, 0b800h
	mov es, ax
	mov al,0
	mov di,903fh


blank:	sub di,2	;;iterates through screen and changes color to all black
	mov[es:di],al
	cmp di,1
	jnz blank	

	mov ax,cs
	mov ds,ax

	mov ax,0b800h
	mov es,ax

iterateoverblock:	;;creates blocks up top 
	mov di, 0h
	mov bl, 0
	mov cl, 160	
	mov ax, 7	
	mul cl	
	add di, 1
	add di, ax	
	add di, 22	
	mov dh, 69h		
	jmp iterateblock

iterateblock:	;;creates moving block
	cmp bl, 20
	jz main
	mov [es:di], dh	
	add di,6
	add bl,1 
	jmp iterateblock

main:

	cmp bally, 10
	jge noCollisionTop
	mov balldy, 160
	jmp noYCollision

noCollisionTop:

	mov bx, paddley
	sub bx, 160

	cmp bally, bx
	jne noYCollidion
	mov ycollide, 1

noYCollision:

	cmp ballx, 1
	jg noCollisionRight
	mov balldx, 2

noCollisionRight:

	cmp ballx, 159
	jl noCollidionLeft
	mov balldx, 0fffeh

noCollisionLeft:

	cmp bally, 3700
	jl default
	mov bally, 0
	mov ballx, 81
	mov balldx, 0
	jmp noCollisionX

default:

	mov bx, paddlex
	cmp ballx, bx
	je collisionX
	mov bx, paddlex
	add bx, 2
	cmp ballx, bx
	je collisionX
	mov bx, paddlex
	add bx, 4
	cmp ballx, bx
	je collisionX
	mov bx, paddlex
	sub bx, 2
	cmp ballx, bx
	je collisionX
	mov bx, paddlex
	sub bx, 4

	cmp ballx, bx
	je collisionX

	jmp noCollisionX

collisionX:
	cmp ycollide, 1
	jne noCollisionX
	mov balldy, 0ff60h
	mov bx, paddlex
	add bx, 2
	cmp ballx, bx
	jge xRight
	mov bx, paddlex
	sub bx, 2
	mov balldx, 0
	cmp ballx, bx
	jle xLeft
	mov bx, balldy
	add bally, bx

	jmp noCollisionX

xRight:
	mov balldx, 2
	jmp noCollisionX

xLeft:
	mov balldx, 0fffeh
	jmp noCollisionX


noCollisionX:

	mov ycollide, 0

	mov di, paddlex
	add di, paddley

	mov al, 55h
	mov [es:di],al

	mov bx, paddlex
	add bx, 2

	mov di,  bx
	add di, paddley

	mov al, 55h
	mov [es:di],al

	mov bx, paddlex
	add bx, 4

	mov di,  bx
	add di, paddley

	mov al, 55h
	mov [es:di],al

	mov bx, paddlex
	sub bx, 2

	mov di,  bx
	add di, paddley

	mov al, 55h
	mov [es:di],al

	mov bx, paddlex
	sub bx, 4

	mov di,  bx
	add di, paddley

	mov al, 55h
	mov [es:di],al



	mov di, ballx
	add di, bally

	mov al, 21h
	mov [es:di],al
	mov cx, 3000h
	delay:    
	sub cx,1
	jnz delay

	mov di, paddlex
	add di, paddley

	mov al, 0
	mov [es:di],al

	mov bx, paddlex
	add bx, 2

	mov di,  bx
	add di, paddley

	mov al, 0
	mov [es:di],al

	mov bx, paddlex
	add bx, 4

	mov di,  bx
	add di, paddley

	mov al, 0
	mov [es:di],al

	mov bx, paddlex
	sub bx, 2

	mov di,  bx
	add di, paddley

	mov al, 0
	mov [es:di],al

	mov bx, paddlex
	sub bx, 4

	mov di,  bx
	add di, paddley

	mov al, 0
	mov [es:di],al
	mov di, ballx
	add di, bally

	mov al, 0
	mov [es:di],al
	in al, 60h
	cmp al, 4bh
	jz moveLeft
	cmp al, 4dh
	jz moveRight

keys:
	mov bx, balldy
	add bally, bx
	mov bx, balldx
	add ballx, bx
	jmp main

moveLeft:
	cmp paddlex, 8
	jle keys
	sub paddlex, 4
	jmp keys

moveRight:
	cmp paddlex, 151
	jge keys
	add paddlex, 4
	jmp keys

	.data
	bally dw 1600
	ballx dw 81
	ycollide dw 0
	paddley dw 3680
	paddlex dw 81
	balldy dw 160
	balldx dw 0    
	mov ah,0
	int 21h
	end