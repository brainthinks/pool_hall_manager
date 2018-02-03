/*********************************************************************
*  THIS PROGRAM MODULE IS PART OF THE OPEN_WINDOW() FUNCTION.  IT    *
*  PLACES A WINDOW ON THE SCREEN AFTER SAVING THE CONTENTS OF        *
*  THE SCREEN TO BE USED (COVERED UP).                               *
**********************************************************************/
#include<memory.h>
#include<dos.h>
#include<malloc.h>
#include<graph.h>
	long bck;          /* hold back grown color */
	int text;
	unsigned montor;
void save_window(int wr1,int wc1,int wy,int wz,int wt,long wb)
{
	struct videoconfig video;

	int i=0,hwy=0;
	int off_fm=0;
	int t_out=0;
	extern void far *buf_ptr[25];
	void error_msg();

	int far *int_buf;
	extern void  far *tmp;
	extern int  ptr_no;
	unsigned seg_val;
	unsigned off_val;


/******************** test for video monitor type ***************/
	_getvideoconfig(&video);

	montor = 0xb800;
	if(video.adapter == 1)
	   montor = 0xb000;

/*
*************** ALLOCATE MEMORY TO SAVE SCREEN WINDOWS*****************
*/
	if(!ptr_no)                     /*  save original colors */
	{
		text = _gettextcolor();
		bck = _getbkcolor();
	}
	hwy=wy*2;
	t_out=(hwy*wz)+12;

	tmp = (void far*)_fcalloc( t_out,1)  ;
	if(tmp==0) error_msg();

/******************* STORE WINDOW ***************************************/
	buf_ptr[ptr_no++]=tmp;
	off_fm = (2*wc1)-2  +  (wr1 - 1)* 160;

	seg_val =FP_SEG(tmp);
	off_val =FP_OFF(tmp);

	off_val+=12;
	for (i=0;i<wz;i++)

	{
		movedata(montor,off_fm,seg_val,off_val,hwy);
		off_fm=off_fm+160;
		off_val+=hwy;
	}
/***********************************************************************/
	int_buf = tmp;
	*int_buf= wr1;
	int_buf+=1;
	*int_buf = wc1;
	int_buf+=1;
	*int_buf = wy;
	int_buf+=1;
	*int_buf = wz;
	int_buf+=1;
	*int_buf = wt;
	int_buf+=1;
	*int_buf = (int)wb;
}
void error_msg()
{
	printf("not enough menory for new window.\n");
	printf("Press any key to cotinue.");
	getch();
	exit(1);
}




