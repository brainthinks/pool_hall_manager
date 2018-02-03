/*
		THIS MODULE DISPLAYS THE RENTAL MENU - PAGE 1
*/

#include<dos.h>
#include<conio.h>
#include<time.h>
	extern struct date store_date;
	int tot_tab;
	int tot_plyrs;

	int extern mono;
	int extern b_red,b_black,b_yellow,b_white,b_grey,b_cyan,b_blue,b_bwhite;
	int extern b_green,b_lblue,b_lcyan, b_magenta,b_lmagenta,b_lgreen;
	int extern f_red,f_black,f_yellow,f_white,f_grey,f_cyan,f_blue,f_bwhite;
	int extern f_green,f_lblue,f_lcyan,f_magenta, f_lmagenta,f_lgreen;

	long extern idx[51];        /* MEMORY AREA INDEX ARRAY */
	long extern  *index;     /* INDEX POINTER */
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

	extern struct bits
		{
		unsigned on:1;
		}bit_tab[51];
	struct rccoord
	{
		short row;
		short col;
	}oldpos;
	extern struct  employee
	{
		char  name[21];
		char  passw[5];
	} emp[16];
	int extern fcolor;
	int extern tb_no;
	int extern curr_emp;
	int extern hcolor;
/******************** PRINT RENTAL MENU *************************/
void pool2s()
{
	int x = 0,y=8;
	char hx[6];
	char buf[10];
	close_window(1);
	textbackground(b_blue);
	clrscr();
	textcolor(f_lcyan);
	gotoxy(3,5);        /*DISPLAY DATE*/
	cprintf("%d/%d/%i",store_date.da_mon,\
		store_date.da_day,store_date.da_year);   /* print date */

	gotoxy(( 80 - ( strlen( emp[curr_emp].name)+14)  ) /2,5) ;
	textbackground(f_black);
	textcolor(b_red);
	cputs(emp[curr_emp].name);
	cputs(" - ");
	cputs(" Signed in.");

	open_window(1,1,80,3,f_lcyan,b_black,205,f_lcyan,b_blue);
	gotoxy(22,1);
	cputs("T A B L E   R E N T A L   M E N U");
	window(1,1,80,25);

	textbackground(b_blue);
/*------------------- PRINT TABLES IN USE __________________________*/
	 gotoxy(3,7);
	 textcolor(f_bwhite);
	 cputs("Tables in use - ");
	 tot_tab = 0;
	 tot_plyrs =0;
	 x=0;
	 textcolor(fcolor);
	 while(x < 50)
	 {
		x = x+1;

		if ( bit_tab[x].on )
		{
		tot_tab+=1;
		index = idx;
		index+=x-1;

			(long)rent = *index;
			cputs(", ");
			if(mono)
				textcolor(fcolor + 8);
			else
			textcolor(f_lcyan);
			sprintf(hx,"%i",x);
			cputs(hx);
			textcolor(f_magenta);
			cputs("(");
			tot_plyrs += rent->no_ply;
			sprintf(hx,"%1d",rent->no_ply);
			cputs(hx);
			cputs(")");
			textcolor(fcolor);
			textbackground(hcolor);
			oldpos.row = wherey();
			oldpos.col = wherex();
			if (oldpos.col > 73)
			{
				cputs("\n");
				gotoxy(7,y++);
			}
		}
	 }

	 gotoxy(19,7);      /* remove comas in left margin */
	 cputs(" ");
	 gotoxy(7,8);
	 cputs(" ");
	 gotoxy(7,9);
	 cputs(" ");
	 gotoxy(7,10);
	 cputs(" ");
	 gotoxy(7,11);
	 cputs(" ");

	 gotoxy(5,12);
	 cputs("Total tables open - ");
	 sprintf(buf,"%i",tot_tab);
	 textcolor(f_bwhite);
	 cputs(buf);
	 textcolor(f_white);
	 gotoxy(42,12);
	 cputs("Total players - ");
	 textcolor(f_bwhite);
	 sprintf(buf,"%i",tot_plyrs);
	 cputs(buf);

/*--------------------------------------------------------------------*/
	gotoxy(1,13);
	textcolor(f_cyan);
	cputs("  ออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออออออออ");
	gotoxy(1,14);
	cputs("    1. Clock table in or out.         ณ  6. Enter on-duty employee password. ");
	gotoxy(1,15);
	cputs("                                      ณ");
	gotoxy(1,16);
	cputs("    2. Change number of players.      ณ  7. Clock rental cue(s) in or out. ");
	gotoxy(1,17);
	cputs("                                      ณ      ( Press F1 key to review cues. )");
	gotoxy(1,18);
	cputs("    3. Review table status.           ณ  8. Go to employer menu.");
	gotoxy(1,19);
	cputs("                                      ณ");
	gotoxy(1,20);
	cputs("    4. Restart table.                 ณ  9. Return to main menu.");
	gotoxy(1,21);
	cputs("                                      ณ");
	gotoxy(1,22);
	cputs("    5. Change table number.           ณ  A. Display page 2 of rental menu.");
	gotoxy(1,23);
	cputs("                                      ณ");
	gotoxy(1,25);


	cputs("                           Enter selection number. ");
	textcolor(fcolor+BLINK);
	cputs("ฐ");
	textcolor(fcolor);
}

