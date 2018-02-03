/*
		THIS MODULE PRINTS AND MAINTAINS THE CASH RECIEPTS DISPLAY
*/
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
#include<dos.h>
		ldiv_t  divtm;

extern struct emp_cash
{
	int emp_no;
	int code;
	int table;
	time_t start;
	time_t stop;
	float amt;

}e_cash[100];
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
	}rental_s;

	extern struct  rental *rent;   /* RENTAL RECORD POINTER */
	long extern idx[51];        /* MEMORY AREA INDEX ARRAY */
	long extern  *index;     /* INDEX POINTER */
	int extern bypass,f_white,b_black;
float grand,uncollected;
extern struct date store_date;
struct date csh_date;
float extern tot_cue_amt;
struct tm *tm_str;

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
			open_window(22,10,22,4,fcolor,hcolor,205,fcolor,hcolor);
			textcolor(fcolor+8);
			cputs(" Press any key\n\r");
			cputs(" to view next line.");
			getch();
			fflush( stdin );
			textcolor(fcolor);
			close_window(0);
			window(3,7,77,18);
			gotoxy ( 4,12 );
			cputs("\n");		/* scrool window */
			cputs("ณ");
			gotoxy ( 8,12 ); cputs("ณ");
			gotoxy ( 49,12 ); cputs("ณ");
			gotoxy ( 56,12 ); cputs("ณ");
			gotoxy ( 63,12 ); cputs("ณ");

		}
		window(1,1,80,25);
		prt_csh_detail();
		++csh;
		++p_row;
	}
	/*----------------C7------total--------------------*/
	sprintf(C7,"$ %5.2f",grand);
	gotoxy( 66,20 ); cputs(C7);
	/*------------------------uncollected --------------*/
	index = idx;
	(long)rent = *index;
	/*---------------- retrieve uncollected receipts -----------*/
	while(index < &idx[51])
	{
		if(*index ==0) { ++index; continue; }
		(long)rent=*index;
		if(rent->stop > 0L) { ++index; continue; }
		bypass = 0;
		review();
		bypass = 1;
		++index;
	}
	get_cue_amt(1);
	uncollected += tot_cue_amt;
	if(uncollected)
	{
		sprintf(C8,"TOTAL FOR OPEN TABLES & CUE STICKS $ %5.2f",uncollected);
		gotoxy( 4,20 ); cputs(C8);
	}
	gotoxy(48,22);
	getch();
	fflush( stdin );
	textcolor(fcolor);
	textbackground(hcolor);
return 0;
}
/**************** print cash detail *************************/
prt_csh_detail()
{
	long t_used,mins,hrs;
	char F4[21];                        /* time worked */
	time_t hstop;
	/*----------------C1---day----------------------*/
/*
	sprintf(C1,"%d",store_date.da_day);
	gotoxy( 3,p_row ); cputs(C1);*/


	/*----------------C2----emp. no.-----------------*/
	sprintf(C2,"%2d",csh->emp_no);
	gotoxy( 7,p_row ); cputs(C2);

	/*----------------C4----start--------------------*/
	tm_str = localtime(&csh->start);
	field = C4;
	convert_time();
	C4[6]='\0';
	gotoxy( 52,p_row ); cputs(C4);

	/*----------------C5------stop--------------------*/
	if(csh->stop >0)
	{
		tm_str = localtime(&csh->stop);
		field = C5;
		convert_time();
		C5[6]='\0';
		if(csh->code != 3){
		gotoxy( 59,p_row ); cputs(C5);}
	}
	/*----------------C6------amt----------------------*/

	if(csh->code <1)
	{
		sprintf(C6,"$ %5.2f",csh->amt);
		grand += csh->amt;
		gotoxy( 66,p_row ); cputs(C6);
	}
	/*----------------C3----name---------------------*/
	switch(csh->code)
	{
	case 2:
		sprintf(C3,"Table %2d cleared,  removed $ %3.2f",csh->table,csh->amt);
		gotoxy( 11,p_row ); cputs(C3);
		 break;



	case 3:
		sprintf(C3,"Table %2d changed start from %.6s to ->",csh->table,C5);
		gotoxy( 11,p_row ); cputs(C3);
		 break;
	default:
		sprintf(C3,"%-20s",emp[csh->emp_no].name);
		gotoxy( 11,p_row ); cputs(C3);
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

		/*_________ convert total seconds to hours,minutes & seconds ________*/
		if (t_used >= 60L)
		{
		   divtm =ldiv( t_used,60L);     /* divide by seconds */
		   mins = divtm.quot;

		   if(mins >= 60L)
		   {
			   divtm = ldiv(mins,60L);      /* divide by minutes */
			   hrs =divtm.quot;
			   mins = divtm.rem;
		   }
		}
		sprintf(F4," Worked %2ld hr %2ld mn\0",hrs,mins);    /*format time used*/
		 cputs(F4);
		break;
	}
return 0;
}
/**************** convert time from 2400 to am pm ******************/

convert_time()
{
		char ampm[3];
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
return 0;
}
/******************* cash screen layout ****************************/
cash_layout()
{
extern int b_white,f_black;
textbackground(b_white);
textcolor(f_black);
clrscr();

gotoxy ( 2,2 ); cputs("ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป");

gotoxy ( 2,3 ); cputs("บ");
gotoxy ( 14,3 ); cprintf("%d/%d/%d",store_date.da_mon,store_date.da_day,\
						store_date.da_year);
gotoxy ( 27,3 ); cputs("DAILY TABLE RENTAL CASH RECEIPTS");
gotoxy ( 79,3 ); cputs("บ");

gotoxy ( 2,4 ); cputs("ฬอออัอออัออออออออออออออออออออออออออออออออออออออออัออออออัออออออัอออออออออออออน");

gotoxy ( 2,5 ); cputs("บ   ณEMPณEMPLOYEE NAME OR MEMO");
gotoxy ( 51,5 ); cputs("ณ");
gotoxy ( 53,5 ); cputs("START");
gotoxy ( 58,5 ); cputs("ณ");
gotoxy ( 60,5 ); cputs("STOP");
gotoxy ( 65,5 ); cputs("ณ");
gotoxy ( 67,5 ); cputs("RECEIPTS");
gotoxy ( 79,5 ); cputs("บ");

gotoxy ( 2,6 ); cputs("วฤฤฤลฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤลฤฤฤฤฤฤลฤฤฤฤฤฤลฤฤฤฤฤฤฤฤฤฤฤฤฤถ");

gotoxy ( 2,7 ); cputs("บ");
gotoxy ( 6,7 ); cputs("ณ");
gotoxy ( 10,7 ); cputs("ณ");
gotoxy ( 51,7 ); cputs("ณ");
gotoxy ( 58,7 ); cputs("ณ");
gotoxy ( 65,7 ); cputs("ณ");
gotoxy ( 79,7 ); cputs("บ");

gotoxy ( 2,8 ); cputs("บ");
gotoxy ( 6,8 ); cputs("ณ");
gotoxy ( 10,8 ); cputs("ณ");
gotoxy ( 51,8 ); cputs("ณ");
gotoxy ( 58,8 ); cputs("ณ");
gotoxy ( 65,8 ); cputs("ณ");
gotoxy ( 79,8 ); cputs("บ");

gotoxy ( 2,9 ); cputs("บ");
gotoxy ( 6,9 ); cputs("ณ");
gotoxy ( 10,9 ); cputs("ณ");
gotoxy ( 51,9 ); cputs("ณ");
gotoxy ( 58,9 ); cputs("ณ");
gotoxy ( 65,9 ); cputs("ณ");
gotoxy ( 79,9 ); cputs("บ");

gotoxy ( 2,10 ); cputs("บ");
gotoxy ( 6,10 ); cputs("ณ");
gotoxy ( 10,10 ); cputs("ณ");
gotoxy ( 51,10 ); cputs("ณ");
gotoxy ( 58,10 ); cputs("ณ");
gotoxy ( 65,10 ); cputs("ณ");
gotoxy ( 79,10 ); cputs("บ");

gotoxy ( 2,11 ); cputs("บ");
gotoxy ( 6,11 ); cputs("ณ");
gotoxy ( 10,11 ); cputs("ณ");
gotoxy ( 51,11 ); cputs("ณ");
gotoxy ( 58,11 ); cputs("ณ");
gotoxy ( 65,11 ); cputs("ณ");
gotoxy ( 79,11 ); cputs("บ");

gotoxy ( 2,12 ); cputs("บ");
gotoxy ( 6,12 ); cputs("ณ");
gotoxy ( 10,12 ); cputs("ณ");
gotoxy ( 51,12 ); cputs("ณ");
gotoxy ( 58,12 ); cputs("ณ");
gotoxy ( 65,12 ); cputs("ณ");
gotoxy ( 79,12 ); cputs("บ");

gotoxy ( 2,13 ); cputs("บ");
gotoxy ( 6,13 ); cputs("ณ");
gotoxy ( 10,13 ); cputs("ณ");
gotoxy ( 51,13 ); cputs("ณ");
gotoxy ( 58,13 ); cputs("ณ");
gotoxy ( 65,13 ); cputs("ณ");
gotoxy ( 79,13 ); cputs("บ");

gotoxy ( 2,14 ); cputs("บ");
gotoxy ( 6,14 ); cputs("ณ");
gotoxy ( 10,14 ); cputs("ณ");
gotoxy ( 51,14 ); cputs("ณ");
gotoxy ( 58,14 ); cputs("ณ");
gotoxy ( 65,14 ); cputs("ณ");
gotoxy ( 79,14 ); cputs("บ");

gotoxy ( 2,15 ); cputs("บ");
gotoxy ( 6,15 ); cputs("ณ");
gotoxy ( 10,15 ); cputs("ณ");
gotoxy ( 51,15 ); cputs("ณ");
gotoxy ( 58,15 ); cputs("ณ");
gotoxy ( 65,15 ); cputs("ณ");
gotoxy ( 79,15 ); cputs("บ");

gotoxy ( 2,16 ); cputs("บ");
gotoxy ( 6,16 ); cputs("ณ");
gotoxy ( 10,16 ); cputs("ณ");
gotoxy ( 51,16 ); cputs("ณ");
gotoxy ( 58,16 ); cputs("ณ");
gotoxy ( 65,16 ); cputs("ณ");
gotoxy ( 79,16 ); cputs("บ");

gotoxy ( 2,17 ); cputs("บ");
gotoxy ( 6,17 ); cputs("ณ");
gotoxy ( 10,17 ); cputs("ณ");
gotoxy ( 51,17 ); cputs("ณ");
gotoxy ( 58,17 ); cputs("ณ");
gotoxy ( 65,17 ); cputs("ณ");
gotoxy ( 79,17 ); cputs("บ");

gotoxy ( 2,18 ); cputs("บ");
gotoxy ( 6,18 ); cputs("ณ");
gotoxy ( 10,18 ); cputs("ณ");
gotoxy ( 51,18 ); cputs("ณ");
gotoxy ( 58,18 ); cputs("ณ");
gotoxy ( 65,18 ); cputs("ณ");
gotoxy ( 79,18 ); cputs("บ");

gotoxy ( 2,19 ); cputs("ฬอออฯอออฯออออออออออออออออออออออออออออออออออออออออฯออออออฯออออออฯอออออออออออออน");

gotoxy ( 2,20 ); cputs("บ");
gotoxy ( 58,20 ); cputs("TOTAL -");
gotoxy ( 79,20 ); cputs("บ");

gotoxy ( 2,21 ); cputs("ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ");

	gotoxy( 21,22 ); cputs("Press any key to continue.");
return 0;
}
