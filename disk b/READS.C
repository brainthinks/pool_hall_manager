
//  PRIMARY SOURCE COPY REVISED 8/26/91
/*      	THIS MODULE READS VARIABLE STRINGS FROM THE KEYBOARD
*/

#include<conio.h>

/*
void main(void)
{
char bufr[80];
char holdc,char_read;
gotoxy(1,1);
strcpy(bufr,"\0");
clrscr();
reads(10,bufr,0,1,1,0,1);
}
*/

/*************** read char string into buffer *************************/
reads(int field_size,char *buf, int ctl,int echo,int upper,int numeric,int no_rtr)
					/*
					field_size = field size,
					buffer for data read,
					ctl = 1 - if control keys are to be returned,
					echo = 1 - echo char's.
					upper = 1 - convert to upper case
					numeric = 1 = accept numeric (float only)
                    no_rtr = 1 auto return on last pos of field
					*/
{
		struct rccoord
{
	short row;
	short col;
}oldpos;

	int next_space =0,z=1,old_col=1,i=0,dec_sw=0,tot_chars=0;
	char char_read=' ',d[2];

	/*   next_space = points to next available space in input buf */
	oldpos.row =wherey();
    oldpos.col =wherex();

	d[1]='\0';
	while(kbhit()) getch();     /* flush keyboard buffer */
	if(buf[0]!=0)              /* check first pos of buf for null */
	{                          /* if not null */
		z=field_size+1;
		old_col=oldpos.col + next_space;
		gotoxy(old_col,oldpos.row); /*set cursor*/
        for(next_space=0;isprint(buf[next_space])&&field_size>next_space;++tot_chars,next_space++);
        next_space=0;
	}

    while(char_read!='\r')
	{
		if(upper)
			char_read = toupper(getch());       /* read character from keyboard */
		else
			char_read=getch();
		if(iscntrl(char_read))     /* Control character(escape sequence)  */
		{
			if(char_read=='\0')     /* if null (function or cursor key  */
			{
				(char_read) = getch() ;    /* read again from buffer */
				/****** test for and return control keys  *************/
				if (ctl == 1)     /* if requested return control keys */
				{
					if(char_read!= 'M' && char_read != 'K' && char_read!='S')      /* if not cur_right or     */
						return (char_read);               /*    cur left return(key) */
					if(next_space==0 && char_read=='K' )          /* if in 1st position and */
						return(char_read);                  /* cur-left - return(key) */
					if(next_space==field_size-1 && char_read=='M')           /* if in last position and */
						return(char_read);                  /* cur_right - return key */
				}
				if(char_read=='K')         //  cur_left */
					if( next_space == 0) continue;  // 1st pos
					else
					{
						next_space -= 1;                     /* decrement next_space */
						printf("\b");
						continue;
					}
				if(char_read=='M')         // cur_right
					if( next_space >= field_size-1) continue;  // last pos
					else
					{
						if (next_space<=z)      //-1
						{
							next_space+=1;
							old_col=oldpos.col +next_space;
							gotoxy(old_col,oldpos.row);  /*print field*/
						}
						continue;
					}
         		if(char_read=='S')    // delete
                {
                    i = next_space;    // store next_space
                    --tot_chars;
                    while(i<field_size-1)
					{
                        old_col = oldpos.col +i;
                        gotoxy(old_col,oldpos.row);
						buf[i]=buf[i+1];
                        putchar(buf[i+1]);      /*print field*/
						++i;
					}
                    buf[i]=' ';
					putchar(buf[i]);      /*print field*/
                    old_col = oldpos.col +next_space;
                    gotoxy(old_col,oldpos.row);
                }

			}
			else
			{
				if(char_read=='\r') break;   /* if return key  */
				if(char_read=='\b' && next_space==0 && ctl == 1)  /* if in 1st position and */
					return(char_read);                   /* back space and ctl = 1*/
												 /* return(key) */
				if(char_read=='\b' )   /* 1st pos and bs*/
					if(next_space==0) continue;
				else
				{
					buf[next_space]=' ';
					next_space -= 1;
					buf[next_space]=' ';
					if(buf[next_space]=='.') dec_sw=0;
						printf(" \b\b \b");
					continue;
				 }
			}
		}
		else
		{
			if(!isprint(char_read))  continue;   /* printable character */
			if(numeric)
			{
				if(!isdigit(char_read))
				{
					if(char_read!='-')
					{
						if(char_read=='.')
						{
							if(dec_sw) continue;
							dec_sw = 1;
						}
						else
						continue;
				   }
				}
			}
			if(next_space <= field_size)
			{
				d[0]=char_read;
				old_col=oldpos.col +next_space;
				if(buf[next_space]=='.'&& char_read !=':') dec_sw=0;
				buf[next_space++] = char_read;                  /* accept character read */
				gotoxy(old_col,oldpos.row);   /*print field*/
				if(echo)
					cputs(d);
				else
					cputs(" ");
                if(tot_chars<next_space)     // count total chars entered
                	tot_chars=next_space;
				if (field_size==1)
			  		break;
				if (next_space==field_size)
				{
                    if(no_rtr) break;   // auto return on last field position
                    gotoxy(old_col,oldpos.row);
					next_space-=1;
				}
			}
		}
	}
if(tot_chars>0)
	for(;field_size>tot_chars;buf[tot_chars++]=' ');
return(0);
}
