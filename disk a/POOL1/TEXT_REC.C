/*************************************************************************
*  THIS PROGRAM MODULE WORKES IN CONJUNCTION WITH THE FUNCTIONS          *
*  OPEN_WINDOW() AND CLOSE_WINDOW_S.                                     *
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
#include<graph.h>
void open_window(int r,int c, int w,int l,int wt,long wb,int panel,int pt,long pb)
{
int cnt,num,num2,x=0,y=0,z=0;

char hpanel,tlpanel,trpanel,blpanel,brpanel,spanel,alter;
char buff[80];

save_window(r,c,w,l,wt,wb);
_settextwindow(1,1,25,80);
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
/************************ top line ***************************/
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
_setbkcolor(pb);
_settextcolor(pt);
_settextposition(r,c);          /* TOP LEFT CORNER */
_outtext(buff);
/*********************** side lines *****************************/
x=r+1;  y=c; z=w+c-1;      /* ROW +1 , COL , WIDTH +COL-1 */
for(num=0;num<l-2;x++,num++)   /*    LENGTH -2 */
{
	cnt=0;                        /* PLACE LEFT BOARDER CHARACTER */
	_settextposition(x,y);
	buff[cnt++]=spanel;
	buff[cnt]='\0';
	_settextcolor(pt);
	_setbkcolor(pb);
	_outtext(buff);
/*********************/
	cnt=0;                      /* PLACE CHARACTERS BETWEEN BOARDERS */
	for(num2=0;num2<w-2;num2++)
		buff[cnt++]=' ';
	buff[cnt]='\0';
	_settextcolor(wt);
	_setbkcolor(wb);

  _outtext(buff);
/**********************/
	cnt=0;                     /* PLACE RIGHT BOARDER CHARACTER */
	buff[cnt++]=spanel;
	buff[cnt]='\0';
	_settextcolor(pt);
	_setbkcolor(pb);
  _outtext(buff);
}

/********************** bottom line *******************************/
_settextposition(r+l-1,c);      /*ROW+LENGTH -1,col   */
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
_outtext(buff);
/*****************************************************************/
_settextwindow(r+1,c+1,l+r-2,w+c-2);    /* ROW + 1, COL + 1, LENGTH + row - 2,
												WIDTH +col -2*/
_setbkcolor(wb);
_settextcolor(wt);
}

