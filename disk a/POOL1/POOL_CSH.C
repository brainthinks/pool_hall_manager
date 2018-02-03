/*
		THIS MODULE PRINTS AND MAINTAINS THE CASH RECIEPTS DISPLAY
*/
#include<stdlib.h>
#include<graph.h>
#include<time.h>
#include<stdio.h>
		ldiv_t  divtm;

extern struct emp_cash
{
	int emp_no;
	int code;
	int table;
	time_t start;
	time_t stop;
	float amt;
}e_cash[60];
extern struct emp_cash *csh;

	extern struct  employee
	{
		char  name[21];
		char  passw[5];
	} emp[16];
	extern struct rental           /* MEMORY AREA RECORD LAYOUT ARRAY*/
	{
		int cust;
		int table;
		int no_ply;
		float rate;
		int employee;
		int trans;
		time_t start;
		time_t stop ;
		long *prev;
		char freeze;
		int new_table;
	}ren[1000];

	extern struct  rental *rent;   /* RENTAL RECORD POINTER */
	long extern idx[51];        /* MEMORY AREA INDEX ARRAY */
	long extern  *index;     /* INDEX POINTER */
	int extern bypass;
float grand,uncollected;
char extern store_date[9];
struct tm *tm_str;
char ampm[3];
char *field;
char C1[3];                         /* day        */
char C2[3];                         /* emp. no.    */
char C3[40];                        /* name        */
char C4[7];                         /* start       */
char C5[7];                         /* stop        */
char C6[15];                        /* amt         */
char C7[12];                        /* total       */
char C8[45];                        /* uncollected */
char C9[9];
char F4[21];                        /* time worked */

char mo_name[27];
int extern fcolor,hcolor;
int p_row;
/**************** print cash reciepts ******************************/
cash()
{
	int x;
	grand=0;
	uncollected =0;
	csh= e_cash;
	cash_layout();
	p_row = 7;

	while(csh->emp_no > 0)
	{
		if(p_row>18)        /* page scrolling */
		{
			p_row=18;
			open_window(22,10,22,4,fcolor,(long)hcolor,205,fcolor,hcolor);
			_settextcolor(fcolor+8);
			_outtext(" Press any key\n");
			_outtext(" to view next line.");
			getch();
			fflush( stdin );
			_settextcolor(fcolor);
			close_window(0);
			_settextwindow(7,2,18,77);
			_scrolltextwindow(1);
			_settextposition ( 18,4 ); _outtext("ณ");
			_settextposition ( 18,8 ); _outtext("ณ");
			_settextposition ( 18,49 ); _outtext("ณ");
			_settextposition ( 18,56 ); _outtext("ณ");
			_settextposition ( 18,63 ); _outtext("ณ");

			_settextwindow(1,1,25,80);
		}
		prt_csh_detail();
		++csh;
		++p_row;
	}
	/*----------------C7------total--------------------*/
	sprintf(C7,"$ %5.2f",grand);
	_settextposition( 20,65 ); _outtext(C7);
	/*------------------------uncollected --------------*/
	index = idx;
	(long)rent = *index;
	/*---------------- retrieve uncollected receipts -----------*/
	while(index < &idx[51])
	{
		if(*index < 1L) { ++index; continue; }
		(long)rent=*index;
		if(rent->stop > 0L) { ++index; continue; }
		bypass = 0;
		review();
		bypass = 1;
		++index;
	}
	if(uncollected)
	{
		sprintf(C8,"UNCOLLECTED TOTAL FOR OPEN TABLES $ %5.2f",uncollected);
		_settextposition( 20,3 ); _outtext(C8);
	}
	_settextposition(22,47);
	getch();
	fflush( stdin );
}
/**************** print cash detail *************************/
prt_csh_detail()
{
	long t_used,mins,hrs,sec;
	time_t hstop;
	/*----------------C1---day----------------------*/
	sprintf(C1,"%.2s",&store_date[3]);
	_settextposition( p_row,2 ); _outtext(C1);


	/*----------------C2----emp. no.-----------------*/
	sprintf(C2,"%2d",csh->emp_no);
	_settextposition( p_row,6 ); _outtext(C2);

	/*----------------C4----start--------------------*/
	tm_str = localtime(&csh->start);
	field = C4;
	convert_time();
	C4[6]='\0';
	_settextposition( p_row,51 ); _outtext(C4);

	/*----------------C5------stop--------------------*/
	if(csh->stop >0)
	{
		tm_str = localtime(&csh->stop);
		field = C5;
		convert_time();
		C5[6]='\0';
		if(csh->code != 3){
		_settextposition( p_row,58 ); _outtext(C5);}
	}
	/*----------------C6------amt----------------------*/
	if(csh->code <1)
	{
		sprintf(C6,"$ %5.2f",csh->amt);
		grand += csh->amt;
		_settextposition( p_row,65 ); _outtext(C6);
	}
	/*----------------C3----name---------------------*/
	switch(csh->code)
	{
	case 2:
		sprintf(C3,"Table %2d cleared,  removed $ %3.2f",csh->table,csh->amt);
		_settextposition( p_row,10 ); _outtext(C3);
		 break;



	case 3:
		sprintf(C3,"Table %2d Changed start from %.6s to ->",csh->table,C5);
		_settextposition( p_row,10 ); _outtext(C3);
		 break;
	default:
		sprintf(C3,"%-20s",emp[csh->emp_no].name);
		_settextposition( p_row,10 ); _outtext(C3);
		if(csh->stop > 0L)          /* if stop time emtered */
		{
			t_used =  difftime(csh->stop,csh->start) ;     /* compute time used by line */
		}                                          /*    with stop time */
		else                      /* if no stop time */
		{                         /* compute time used with current time */

			t_used = difftime(time(&hstop),csh->start );
		}
		mins = 0;
		hrs = 0;
		sec = 0;
		/*_________ convert total seconds to hours,minutes & seconds ________*/
		if (t_used >= 60L)
		{
		   divtm =ldiv( t_used,60L);     /* divide by seconds */
		   mins = divtm.quot;
		   sec = divtm.rem;
		   if(mins >= 60L)
		   {
			   divtm = ldiv(mins,60L);      /* divide by minutes */
			   hrs =divtm.quot;
			   mins = divtm.rem;
		   }
		}
		sprintf(F4," Worked %2ld hr %2ld mn\0",hrs,mins);    /*format time used*/
		 _outtext(F4);
		break;
	}

}
/**************** convert time from 2400 to am pm ******************/

convert_time()
{
		if(tm_str->tm_hour>12)
		{
			tm_str->tm_hour -=12;
			strcpy(ampm,"PM");
			if(tm_str->tm_hour ==12)  strcpy(ampm,"AM");
		}
		else
		{
			strcpy(ampm,"AM");
			if(tm_str->tm_hour ==12)  strcpy(ampm,"PM");
			if(tm_str->tm_hour==0) tm_str->tm_hour =12;
		}
		sprintf(field,"%02d:%02d%2s",tm_str->tm_hour,tm_str->tm_min,ampm);
}
/******************* cash screen layout ****************************/
cash_layout()
{
	_clearscreen(_GCLEARSCREEN);

_settextposition ( 2,1 ); _outtext("ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป");
_settextposition ( 3,1 ); _outtext("บ");
_settextposition ( 3,13 ); _outtext(store_date);
_settextposition ( 3,26 ); _outtext("DAILY TABLE RENTAL CASH RECEIPTS");
_settextposition ( 3,78 ); _outtext("บ");
_settextposition ( 4,1 ); _outtext("ฬอออัอออัออออออออออออออออออออออออออออออออออออออออัออออออัออออออัอออออออออออออน");
_settextposition ( 5,1 ); _outtext("บDAYณEMPณEMPLOYEE NAME OR MEMO");
_settextposition ( 5,50 ); _outtext("ณ");
_settextposition ( 5,52 ); _outtext("START");
_settextposition ( 5,57 ); _outtext("ณ");
_settextposition ( 5,59 ); _outtext("STOP");
_settextposition ( 5,64 ); _outtext("ณ");
_settextposition ( 5,66 ); _outtext("RECEIPTS");
_settextposition ( 5,78 ); _outtext("บ");
_settextposition ( 6,1 ); _outtext("วฤฤฤลฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤลฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤฤถ");
_settextposition ( 7,1 ); _outtext("บ");
_settextposition ( 7,5 ); _outtext("ณ");
_settextposition ( 7,9 ); _outtext("ณ");
_settextposition ( 7,50 ); _outtext("ณ");
_settextposition ( 7,57 ); _outtext("ณ");
_settextposition ( 7,64 ); _outtext("ณ");
_settextposition ( 7,78 ); _outtext("บ");
_settextposition ( 8,1 ); _outtext("บ");
_settextposition ( 8,5 ); _outtext("ณ");
_settextposition ( 8,9 ); _outtext("ณ");
_settextposition ( 8,50 ); _outtext("ณ");
_settextposition ( 8,57 ); _outtext("ณ");
_settextposition ( 8,64 ); _outtext("ณ");
_settextposition ( 8,78 ); _outtext("บ");
_settextposition ( 9,1 ); _outtext("บ");
_settextposition ( 9,5 ); _outtext("ณ");
_settextposition ( 9,9 ); _outtext("ณ");
_settextposition ( 9,50 ); _outtext("ณ");
_settextposition ( 9,57 ); _outtext("ณ");
_settextposition ( 9,64 ); _outtext("ณ");
_settextposition ( 9,78 ); _outtext("บ");
_settextposition ( 10,1 ); _outtext("บ");
_settextposition ( 10,5 ); _outtext("ณ");
_settextposition ( 10,9 ); _outtext("ณ");
_settextposition ( 10,50 ); _outtext("ณ");
_settextposition ( 10,57 ); _outtext("ณ");
_settextposition ( 10,64 ); _outtext("ณ");
_settextposition ( 10,78 ); _outtext("บ");
_settextposition ( 11,1 ); _outtext("บ");
_settextposition ( 11,5 ); _outtext("ณ");
_settextposition ( 11,9 ); _outtext("ณ");
_settextposition ( 11,50 ); _outtext("ณ");
_settextposition ( 11,57 ); _outtext("ณ");
_settextposition ( 11,64 ); _outtext("ณ");
_settextposition ( 11,78 ); _outtext("บ");
_settextposition ( 12,1 ); _outtext("บ");
_settextposition ( 12,5 ); _outtext("ณ");
_settextposition ( 12,9 ); _outtext("ณ");
_settextposition ( 12,50 ); _outtext("ณ");
_settextposition ( 12,57 ); _outtext("ณ");
_settextposition ( 12,64 ); _outtext("ณ");
_settextposition ( 12,78 ); _outtext("บ");
_settextposition ( 13,1 ); _outtext("บ");
_settextposition ( 13,5 ); _outtext("ณ");
_settextposition ( 13,9 ); _outtext("ณ");
_settextposition ( 13,50 ); _outtext("ณ");
_settextposition ( 13,57 ); _outtext("ณ");
_settextposition ( 13,64 ); _outtext("ณ");
_settextposition ( 13,78 ); _outtext("บ");
_settextposition ( 14,1 ); _outtext("บ");
_settextposition ( 14,5 ); _outtext("ณ");
_settextposition ( 14,9 ); _outtext("ณ");
_settextposition ( 14,50 ); _outtext("ณ");
_settextposition ( 14,57 ); _outtext("ณ");
_settextposition ( 14,64 ); _outtext("ณ");
_settextposition ( 14,78 ); _outtext("บ");
_settextposition ( 15,1 ); _outtext("บ");
_settextposition ( 15,5 ); _outtext("ณ");
_settextposition ( 15,9 ); _outtext("ณ");
_settextposition ( 15,50 ); _outtext("ณ");
_settextposition ( 15,57 ); _outtext("ณ");
_settextposition ( 15,64 ); _outtext("ณ");
_settextposition ( 15,78 ); _outtext("บ");
_settextposition ( 16,1 ); _outtext("บ");
_settextposition ( 16,5 ); _outtext("ณ");
_settextposition ( 16,9 ); _outtext("ณ");
_settextposition ( 16,50 ); _outtext("ณ");
_settextposition ( 16,57 ); _outtext("ณ");
_settextposition ( 16,64 ); _outtext("ณ");
_settextposition ( 16,78 ); _outtext("บ");
_settextposition ( 17,1 ); _outtext("บ");
_settextposition ( 17,5 ); _outtext("ณ");
_settextposition ( 17,9 ); _outtext("ณ");
_settextposition ( 17,50 ); _outtext("ณ");
_settextposition ( 17,57 ); _outtext("ณ");
_settextposition ( 17,64 ); _outtext("ณ");
_settextposition ( 17,78 ); _outtext("บ");
_settextposition ( 18,1 ); _outtext("บ");
_settextposition ( 18,5 ); _outtext("ณ");
_settextposition ( 18,9 ); _outtext("ณ");
_settextposition ( 18,50 ); _outtext("ณ");
_settextposition ( 18,57 ); _outtext("ณ");
_settextposition ( 18,64 ); _outtext("ณ");
_settextposition ( 18,78 ); _outtext("บ");
_settextposition ( 19,1 ); _outtext("ฬอออฯอออฯออออออออออออออออออออออออออออออออออออออออฯออออออฯออออออฯอออออออออออออน");
_settextposition ( 20,1 ); _outtext("บ");
_settextposition ( 20,57 ); _outtext("TOTAL -");
_settextposition ( 20,78 ); _outtext("บ");
_settextposition ( 21,1 ); _outtext("ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ");

	_settextposition( 22,20 ); _outtext("Press any key to continue.");
}
