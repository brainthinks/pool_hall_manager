/*********************************************************************
*  THIS PROGRAM MODULE IS PART OF THE CLOSE_WINDOW() FUNCTION.  IT   *
*  RESTORES THE SCREEN TO ITS PREVIOS STATE, REMOVING THE LAST       *
*  WINDOW OPENED OR IF PARAMETER = INT 1 CLOSES ALL WINDOWS.         *
**********************************************************************/
#include<memory.h>
#include<dos.h>
#include<graph.h>
	int far *int_buf=0;
	int hr,hc,hy,hz,hwt,hwb;
	 long extern bck;
	 int extern text;
	 unsigned extern montor;
void close_window(int all)
{
	unsigned off_fm;
	int i;
	extern void far *buf_ptr[25];
	extern void far  *tmp;
	extern unsigned  ptr_no;
	unsigned seg_val;
	unsigned off_val;
	unsigned hoff_val;
	void get_coor();
/******************* code segment ******************************/
begin:
	if(!ptr_no) return;
	off_fm =0;
	i=0;
	(void far*)tmp=buf_ptr[--ptr_no];
	get_coor();       /* get coordinstes for stored window */
	seg_val=FP_SEG(tmp);
	off_val =FP_OFF(tmp);
	off_val+=12;
	off_fm = (2*hc)-2   +  (hr - 1)* 160 ; /*video buf offset*/
/***********RESTORE VIDEO BUFFER ****************************************/
	for (i=1;i<=hz;i++)
	{
		movedata(seg_val,off_val,montor,off_fm,hy*2);
		off_val+=(hy*2);
		off_fm +=160;
	}
/*********** ADJUST ALLOCATED MEMORY *************************************/
_ffree(tmp);
if(ptr_no != 0 )
{
	(void far*)tmp=buf_ptr[ptr_no-1];
	get_coor();       /* get coordinstes for previous stored window */
  _settextwindow(hr+1,hc+1,hz+hr-2,hy+hc-2);    /* ROW + 1, COL + 1,
													LENGTH + row - 2, WIDTH +col -2*/
  _settextcolor(hwt);
  _setbkcolor((long)hwb);

}
else
{
	_settextwindow(1,1,25,80);
	all =0;
}
if(all ==1)
	goto begin;
	if (!ptr_no)
	{
		_setbkcolor(bck);
		_settextcolor(text);
	}
}

void get_coor()
{
	int_buf = tmp;
	hr = *int_buf;
	int_buf+=1;
	hc = *int_buf;
	int_buf+=1;
	hy = *int_buf;
	int_buf+=1;
	hz = *int_buf;
	int_buf+=1;
	hwt = *int_buf;
	int_buf+=1;
	hwb = (long)*int_buf;

 }

