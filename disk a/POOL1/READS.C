/*
	THIS MODULE READS VARIANLE STRINGS FROM THE KEYBOARD
*/

#include<stdio.h>
#include<graph.h>
char bufr[80];
/*
main()
{
strcpy(bufr,"\0");
_outtext(bufr);
_outtext("\r");

reads(1,bufr,0,1,0,1);
}
*/

/*************** read char string into buffer *************************/
reads(int x,char *buf, int ctl,int echo,int upr,int num) /* x = field size,
											buffer for data read,
											ctl = 1 if control keys are
											to be returned,
											echo = 1 to echo char's.
											upr = 1 - convert to upper case
											num = 1 = accept float only*/
{
	int y =0,z=1,w=1,dec_sw=0;
	char c=' ',d[2];
	struct rccoord oldpos;
	/*   y = points to next available space in input buf */
	oldpos =_gettextposition();
	d[1]='\0';
	while(kbhit()) getch();     /* flush keyboard buffer */
	if(buf[0]!=0)              /* check first pos of buf for null */
	{                          /* if not null */
		z=x+1;
		w=oldpos.col +y;
		_settextposition(oldpos.row,w); /*print field*/
	}
	while(c!='\r')
	{
		if(upr)
			c = toupper(getch());       /* read character from keyboard */
		else
			c=getch();
		if(iscntrl(c))     /* Control character(escape sequence)  */
		{
			if(c=='\0')     /* if null (function or cursor key  */
			{
				(c) = getch() ;    /* read again from buffer */
				/****** test for and return control keys  *************/
				if (ctl == 1)     /* if requested return control keys */
				{
					if(c!= 'M' && c != 'K')      /* if not cur_right or     */
						return(c);               /*    cur left return(key) */
					if(y==0 && c=='K' )          /* if in 1st position and */
						return(c);                  /* cur-left - return(key) */
					if(y==x-1 && c=='M')           /* if in last position and */
						return(c);                  /* cur_right - return key */
				}
				if(c=='K')
					if( y == 0) continue;  /* 1st pos and cur_left */
					else
					{
						y -= 1;                     /* decrement y */

						printf("\b");
						continue;
					}
				if(c=='M')
					if( y >= x-1) continue;  /* last pos and cur_right */
					else
					{
						if (y<z-1)
						{
							y+=1;
							w=oldpos.col +y;

							_settextposition(oldpos.row,w); /*print field*/
						}
					continue;
					}
			}
			else
			{
				if(c=='\r') break;   /* if return key  */
				if(c=='\b' && y==0 && ctl == 1)  /* if in 1st position and */
					return(c);                   /* back space and ctl = 1*/
												 /* return(key) */
				if(c=='\b' )   /* 1st pos and bs*/
					if(y==0) continue;
				else
				{
					buf[y]=' ';
					y -= 1;
					buf[y]=' ';
					if(buf[y]=='.') dec_sw=0;

						printf(" \b\b \b");
					continue;
				 }
			}
		}
		else
		{
			if(!isprint(c))  continue;   /* printable character */
			if(num)
			{
				if(!isdigit(c))
				{
					if(c!='-')
					{
						if(c=='.')
						{
							if(dec_sw) continue;
							dec_sw = 1;
						}
						else
						continue;
				   }
				}
			}
			if(y <= x)
			{
				d[0]=c;
				w=oldpos.col +y;
				if(buf[y]=='.'&& c !=':') dec_sw=0;
				buf[y++] = c;                  /* accept character read */
				if(y==z)
					buf[z++] = '\0';


				_settextposition(oldpos.row,w);   /*print field*/
				if(echo)
					_outtext(d);
				else
					_outtext(" ");
				if (x==1)
					break;
				if (y==x)
				{
					_settextposition(oldpos.row,w);
					y-=1;
				}

			}
		}
	}
buf[z-1]='\0';
for(x=0;buf[x] !='\0';x++);      /* remove trailing blanks */
while(buf[--x]==' ') ;
buf[x+1]='\0';
if(ctl)return(c);
else
return(0);
}
