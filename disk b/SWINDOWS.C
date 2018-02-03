//revised 6\20\91 WORKING COPY SMALL windows

/*************************************************************************
*  THIS PROGRAM MODULE CONTAINS THE FUNCTIONS - OPEN_WINDOW() AND        *
*  CLOSE_WINDOW().                                                       *
*  IT PLACES RECTANGLES WITH BOARDERS ONTO THE SCREEN AFTER STORING      *
*  THE CONTENTS OF THE SCREEN TO BE COVERED UP. A WINDOW IS  SET SO      *
*  THE COORDINATES IF THE UPPER LEFT CORNER OF THE RECTANGLE WILL        *
*  BE (ROW 1 ,COLUMN 1)                                                  *
*                                                                        *
*  THE PARAMETERS ARE:                                                   *               *
*         1. ROW                                                         *
*         2. COLUMN                                                      *
*         3. WIDTH                                                       *
*         4. LENGTH                                                      *
*         5. RECTANGLE TEXT COLOR                                        *
*         6. RECTANGLE BACKGROUND COLOR                                  *
*         7. CHARACTER TO USE FOR BOARDER (CAN BE ANY CHARACTER)         *
*               FOR SINGLE LINE USE ASCII 196                            *
*               FOR DOUBLE LINE USE ASCII 205                            *
*         8. BOARDER TEXT COLOR                                          *
*         9. BOARDER BACKGROUND COLOR                                    *
*                                                                        *
*    TO REMOVE THE RECTANGLE AND RESTORE THE SCREEN USE                  *
*      CLOSE_WINDOW FUNCTION                                             *
**************************************************************************/
#include<alloc.h>
#include<conio.h>

void  *tmp;
extern unsigned ptr_no;
void *buf_ptr[25];    /* up to 25 windows can be open at once */

		struct ctl_code
	{
		char wr1;
		char wc1;
		char wy;
		char wz;
		char wt;
		int wb;
		char winleft;
		char wintop;
		char winright;
		char winbottom;
		char attribute;
		char curx;
		char cury;
	} *cc;
//******************** OPEN WINDOW() *******************************
void open_window(int r,int c, int w,int l,int wt,int wb,int panel,int pt,int pb)
{
int cnt,num,num2,x=0,y=0;
int extern _wscroll;

char hpanel,tlpanel,trpanel,blpanel,brpanel,spanel,alter;
char buff[81];

save_window(r,c,w,l,wt,wb);
window(1,1,80,25);
hpanel=panel;
tlpanel=panel;
trpanel=panel;
blpanel=panel;
brpanel=panel;
spanel=panel;
alter=' ';
	if (panel == 205)    /* TEST FOR DOUBLE LINE */
	{
		alter=205;
		tlpanel=201;
		trpanel=187;
		blpanel=200;
		brpanel=188;
		spanel=186;
	}
	if (panel == 196)   /* TEST FOR SINGLE LINE */
	{
		alter=196;
		tlpanel=218;
		trpanel=191;
		blpanel=192;
		brpanel=217;
		spanel=179;
	}
	if (panel == 219 ||panel == 176 || panel == 177 ||  panel == 178)   /* TEST FOR SINGLE LINE */
	{
		alter=panel;
	}

//------------------------ top line ----------------------------
cnt=0;
	buff[cnt++] =tlpanel;
for(num=0;num<w-2;num++)      /* TOTAL WIDTH-2 */
	{
		buff[cnt++]=alter;
		num+=1;
		if (num>=w-2)
			break;
		buff[cnt++]=hpanel;
	}
	buff[cnt++]=trpanel;
	buff[cnt]='\0';
textbackground(pb);
textcolor(pt);
gotoxy(c,r);          /* TOP LEFT CORNER */
cputs(buff);
//---------------------- side lines ------------------------------
x=r+1;  y=c; ;      /* ROW +1 , COL , WIDTH +COL-1 */
for(num=0;num<l-2;x++,num++)   /*    LENGTH -2 */
{
	cnt=0;                        /* PLACE LEFT BOARDER CHARACTER */
	gotoxy(y,x);
	buff[cnt++]=spanel;
	buff[cnt]='\0';
	textcolor(pt);
	textbackground(pb);
	cputs(buff);
//------------------ PLACE CHARACTERS BETWEEN BOARDERS ------------
	cnt=0;
	for(num2=0;num2<w-2;num2++)
		buff[cnt++]=' ';
	buff[cnt]='\0';
	textcolor(wt);
	textbackground(wb);

  cputs(buff);
//----------------------  PLACE RIGHT BOARDER CHARACTER -----------
	cnt=0;
	buff[cnt++]=spanel;
	buff[cnt]='\0';
	textcolor(pt);
	textbackground(pb);
  cputs(buff);
}

//-------------------- PLACE BOTTOM LINE ------------------------------
gotoxy(c,r+l-1);      /*ROW+LENGTH -1,col   */
cnt=0;
buff[cnt++]=blpanel;
for(num=0;num<w-2;num++)     /* WIDTH -2       */
		{
			buff[cnt++]=alter;
			num+=1;
			if (num>=w-2)
				break;
			buff[cnt++]=hpanel;
		}
buff[cnt++]=brpanel;
buff[cnt]='\0';
_wscroll =0;
cputs(buff);
_wscroll =1;
window(c+1,r+1,w+c-2,l+r-2);    /* COL + 1, ROW + 1, LENGTH + row - 2,
												WIDTH +col -2*/
textbackground(wb);
textcolor(wt);
}
/****************** SAVE WINDOWS ********************************/
save_window(int wr1,int wc1,int wy,int wz,int wt,int wb)
{
	int hwy=0;
	unsigned long t_out=0;
	void error_msg();
	struct text_info video2;
	struct ctl_code zcc;
	gettextinfo(&video2);

//------------- ALLOCATE MEMORY TO SAVE SCREEN WINDOWS ----------------
	hwy=wy*2;
	t_out=(hwy*wz)+23;

	tmp = (void *)calloc( t_out,1)  ;
	if(tmp==0) error_msg();

//------------------ STORE WINDOW -----------------------------
	buf_ptr[ptr_no++]=tmp;

	cc = tmp;
	cc->wr1 = wr1;
	cc->wc1 = wc1;
	cc->wy = wy;
	cc->wz = wz;
	cc->wt = wt;
	cc->wb = wb;
	cc->winleft =video2.winleft;
	cc->wintop =video2.wintop;
	cc->winright =video2.winright;
	cc->winbottom =video2.winbottom;
	cc->attribute =video2.attribute;
	cc->curx =video2.curx;           // store column
	cc->cury =video2.cury;           // store row

	(char)tmp+=sizeof(*cc);
	gettext(wc1,wr1,(wc1+wy)-1,(wr1+wz)-1,(void*)tmp);
	return 0;

/******** MEMORY ALLOCATION ERROR MESSAGE ********************************/
}
void error_msg()
{
	printf("not enough menory for new window.\n");
	printf("Press any key to continue.");
	getch();
	exit(1);
}

/******************* CLOSE WINDOWS ************************************/

close_window(int all)
{
	int hrow=0;
	int hcol=0;
	int bck;

//----------- RESTORE PREVIOS SCREEN
	while(1)
	{
		if(!ptr_no) return;
		(void*)tmp=buf_ptr[--ptr_no];
		cc = tmp;
		(char)tmp+=sizeof(*cc);
		puttext(cc->wc1,cc->wr1,(cc->wc1+cc->wy)-1,(cc->wr1+cc->wz)-1,(void*)tmp);
		window(cc->winleft,cc->wintop,cc->winright,cc->winbottom);
		textattr(cc->attribute);
		hcol = cc->curx;
		hrow = cc->cury;
		gotoxy(hcol,hrow);

		free(tmp);
		if(ptr_no == 0 ) all =0;

		if(all) continue;
		else
			break;
	}
	return ;
}
