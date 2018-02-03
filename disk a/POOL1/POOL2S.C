
/*
		THIS MODULE DISPLAYS THE RENTAL MENU - PAGE 1
*/


#include<graph.h>
#include<time.h>
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
	struct rccoord oldpos;
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
pool2s()
{
	 int x = 0,y=8,z=0;
	 char hx[6];


	 char extern store_date[9];
	 close_window(1);
	_clearscreen(_GCLEARSCREEN);
	_settextposition(1,3);        /*DISPLAY DATE*/
	_outtext(store_date);   /* print date */
	_settextposition(1,( 80 - ( strlen( emp[curr_emp].name)+14)  ) /2) ;
	_setbkcolor((long)fcolor);
	_settextcolor(hcolor);
	_outtext(emp[curr_emp].name);
	_setbkcolor((long)hcolor);
	_settextcolor(fcolor);
	_outtext(" - ");
	_setbkcolor((long)fcolor);
	_settextcolor(hcolor);
	_outtext(" Signed in.");
	_settextposition(3,3);
	_outtext("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
	_settextposition(4,3);
	_outtext("³                    T A B L E   R E N T A L   M E N U                    ³");
	_settextposition(5,3);
	_outtext("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
	_setbkcolor(hcolor);
	_settextcolor(fcolor);
/*------------------- PRINT TABLES IN USE __________________________*/
	 _settextposition(7,3);
	 _outtext("Tables in use - ");
	 x=0;

	 while(x < 50)
	 {
		x = x+1;

		if ( bit_tab[x].on )
		{
		index = idx;
		index+=x-1;

			(long)rent = *index;
			_outtext(", ");
			_settextcolor(fcolor + 8);
			sprintf(hx,"%i",x);
			_outtext(hx);
			_settextcolor(fcolor);
			_outtext("(");

			_settextcolor(fcolor);
			_setbkcolor((long)hcolor);
			sprintf(hx,"%1d",rent->no_ply);
			_outtext(hx);
			_settextcolor(fcolor);
			_setbkcolor((long)hcolor);
			_outtext(")");


			oldpos = _gettextposition();
			if (oldpos.col > 73)
			{
				_outtext("\n");
				_settextposition(y++,7);
			}
		}
	 }

	 _settextposition(7,19);             /* remove comas */
	 _outtext(" ");
	 _settextposition(8,7);
	 _outtext(" ");
	 _settextposition(9,7);
	 _outtext(" ");
	 _settextposition(10,7);
	 _outtext(" ");
	 _settextposition(11,7);
	 _outtext(" ");
	 _settextposition(12,7);
	 _outtext(" ");





/*--------------------------------------------------------------------*/
	_settextposition(13,3);
	_outtext("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
	_settextposition(14,1);
	_outtext("    1. Clock table in or out.         ³  6. Enter on-duty employee password. ");
	_settextposition(15,1);
	_outtext("                                      ³");
	_settextposition(16,1);
	_outtext("    2. Change number of players.      ³     Add rental cue(s) to table. ");
	_settextposition(17,1);
	_outtext("                                      ³");
	_settextposition(18,1);
	_outtext("    3. Review table status.           ³  8. Go to employer menu.");
	_settextposition(19,1);
	_outtext("                                      ³");
	_settextposition(20,1);
	_outtext("    4. Restart table.                 ³  9. Return to main menu.");
	_settextposition(21,1);
	_outtext("                                      ³");
	_settextposition(22,1);
	_outtext("    5. Change table number.           ³  A. Display page 2 of rental menu.");
	_settextposition(23,1);
	_outtext("                                      ³");
	_settextposition(25,1);


	_outtext("                           Enter selection number. ");
	_settextcolor(fcolor+16);
	_outtext("°");
	_settextcolor(fcolor);
}

