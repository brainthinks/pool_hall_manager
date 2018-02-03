/*
		THIS MODULE DISPLAYS THE RUNNING CLOCK
*/


/*************** PRINT RUNNING CLOCK ***********************************/
prt_time()
{
int row,col,x;
char hour[]  = {'0','\7','0','\7',':','\7'};
char ampm[]   = {'A','\7','M','\7'};

char min[]   = {'0','\7','0','\7',':','\7'};
char sec[]   = { '0','\7','0','\7' };
int extern mono;
_asm\
	{
		cli
		push ax
		push bx
		push cx
		mov ah,03h         /* store current cursor pos. */
		mov bh,0
		int 10h
		mov row,dh
		mov col,dl
		retry:
		mov ah,02h        /* set cursor for date location */
		mov bh,0
		mov dh,1h
		mov dl,40h
		int 10h
								/* get clock */
		mov ah,2ch
		int 21h

		 mov ampm[0],'A'                          /* print hour */
		cmp ch,12
		jne bp1
		mov ampm[0],'P'
	bp1:
		mov hour[0],'0'
		cmp ch,13               /* compare hr > 12 */
		jb lp1
		mov ampm[0],'P'         /* yes make pm */
		sub ch,12              /* subtract 12 from hr */
	lp1:
		cmp ch,9
		ja lp2
		cmp ch,0
		jne bp2
		cmp hour[0],49
		je bp2
		mov ch,12
		jmp lp1
	bp2:
		add ch,48
		mov hour[2],ch
		jmp lp3
	lp2:
		sub ch,10
		mov hour[0],'1'
		jmp lp1
							/* print minutes */
	lp3:

		mov  min[0],'0'
		mov x,'0'
	lp4:
		cmp cl,9
		ja lp5
		add cl,48
		mov min[2],cl
		jmp lp6
	lp5:
		inc x
		mov al,x
		mov min[0],al
		sub cl,10
		jmp lp4
								/* print seconds */
	lp6:
		mov  sec[0],'0'
		mov x,'0'
	lp7:
		cmp dh,9
		ja lp8
		add dh,48
		mov sec[2],dh
		jmp lp9
	lp8:
		inc x
		mov al,x
		mov sec[0],al
		sub dh,10
		jmp lp7
	lp9:
		pop cx
		pop bx
		pop ax
	}
		if (mono)
		{
		memcpy( 0xb0000084, &hour,6);
		memcpy( 0xb000008a, &min,6);
		memcpy( 0xb0000090, &sec,4);
		memcpy( 0xb0000096, &ampm,4);
		}
		else
		{
		memcpy( 0xb8000084, &hour,6);
		memcpy( 0xb800008a, &min,6);
		memcpy( 0xb8000090, &sec,4);
		memcpy( 0xb8000096, &ampm,4);
		}
	_asm\
	{
		push ax
		push bx
		push cx
		mov al,0
		mov ah,01h       /* key in buffer ? */
		int 16h
		jnz lpx
		jmp retry         /* no loop */
lpx:
/*        cmp al,0
		jne  end_t
		jmp retry       */
end_t:
		mov ah,02h       /* restore cursor pos. */
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

