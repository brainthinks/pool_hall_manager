
/*       THIS MODULE DISPLAYS THE RUNNING CLOCK
*/
#include<conio.h>
#pragma inline

/*************** PRINT RUNNING CLOCK ***********************************/
prt_time()
{
char row,col,x;

	char hour[]  = {'0','0',':','\0'};
	char min[]   = {'0','0',':','\0'};
	char sec[]   = { '0','0',' ','\0'};
	char ampm[]   = {'A','M','\0'};

int extern f_lcyan;

asm	{
		cli
		push ax
		push bx
		push cx
		mov ah,03h         /* store current cursor pos. */
		mov bh,0
		int 10h
		mov row,dh
		mov col,dl
	}
	retry:
	asm{	mov ah,02h        /* set cursor for date location */
		mov bh,0
		mov dh,1h
		mov dl,40h
		int 10h
								/* get clock */
		mov ah,2ch
		int 21h

		mov  byte ptr ampm[0],'A'                          /* print hour */
		cmp ch,12
		jne bp1
		mov byte ptr ampm[0],'P'
	}
	bp1:
	asm{	mov byte ptr   hour[0],'0'
		cmp ch,13               /* compare hr > 12 */
		jb lp1
		mov byte ptr ampm[0],'P'         /* yes make pm */
		sub ch,12              /* subtract 12 from hr */
	}
	lp1:
	asm{	cmp ch,9
		ja lp2
		cmp ch,0
		jne bp2
		cmp byte ptr hour[0],49
		je bp2
		mov byte ptr ch,12
		jmp lp1
	}
	bp2:
	asm{	add ch,48
		mov byte ptr  hour[1],ch
		jmp lp3
	}
	lp2:
	asm{	sub ch,10
		mov byte ptr  hour[0],'1'
		jmp lp1
							/* print minutes */
	}
	lp3:
	asm{	mov byte ptr   min[0],'0'
		mov byte ptr  x,'0'
	}
	lp4:
	asm{	cmp cl,9
		ja lp5
		add cl,48
		mov byte ptr  min[1],cl
		jmp lp6
	}
	lp5:
	asm{   inc word ptr	x
		mov al,x
		mov byte ptr   min[0],al
		sub cl,10
		jmp lp4
								/* print seconds */
	}
	lp6:
	asm{	mov byte ptr   sec[0],'0'
		mov byte ptr x,'0'
	}
	lp7:
	asm{	cmp dh,9
		ja lp8
		add dh,48
		mov byte ptr  sec[1],dh
		jmp lp9
	}
	lp8:
	asm{	inc word ptr x
		mov al,x
		mov byte ptr  sec[0],al
		sub dh,10
		jmp lp7
	}
	lp9:
	asm{	pop cx
		pop bx
		pop ax
	}
// ************ PRINT TIME
	gotoxy(68,5);
	textcolor(f_lcyan);
	cputs(hour);
	cputs(min);
	cputs(sec);
	cputs(ampm);


asm	{
		push ax
		push bx
		push cx
		mov al,0
		mov ah,01h       /* key in buffer ? */
		int 16h
		jnz lpx
		jmp retry         /* no loop */
}
lpx:

/*        cmp al,0
		jne  end_t
		jmp retry       */
end_t:
asm{		mov ah,02h       /* restore cursor pos. */
		mov bh,0
		mov dh,row
		mov dl,col
		int 10h
		pop cx
		pop bx
		pop ax
		sti
	}

return(0);
}

