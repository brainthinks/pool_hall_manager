/*
	THIS MODULE CONTAINS HELP SCREENS AND RATE SCHEDULE SCREEN LAYOUT
*/

#include<graph.h>
#include<stdio.h>
int extern hcolor;
int extern fcolor;

/******************** DEFAULT RATE MESSAGE ******************************/
	default_mesg()
	{
	int r_row;

	open_window(11,2,75,13,fcolor,(long)hcolor,205,fcolor,hcolor );

	_outtext(" You must enter the hourly rates established by your business into a   \n");
	_outtext(" rate schedule.  There can be multiple rate schedules.  Rates can apply\n");
	_outtext(" to seperate groups of rental pool tables.   \n");
	_outtext(" For example -- Pool tables 1 thru 6 can have one set of hourly rental\n");
	_outtext(" rates and pool tables 7 thru 12 can have a different set of hourly rates.\n");
	_outtext(" You can establish as many rate schedules as needed for your business.\n\n\n\n");
	_outtext("                 Press any key to continue !!\r");
	getch();
	fflush( stdin );
	_settextwindow(7,3,19,76);
	r_row = 1;
	_settextposition( r_row,2 );
	_outtext("DE");
	_settextposition( r_row,7 );
	_outtext("00:00AM");
	_settextposition( r_row,18 );
	_outtext("06:00AM");
	_settextposition( r_row,29 );
	_outtext("6.00 ");
	_settextposition( r_row,37 );
	_outtext("5.25 ");
	_settextposition( r_row,45 );
	_outtext("4.75 ");
	_settextposition( r_row,53 );
	_outtext("4.25 ");
	_settextposition( r_row,61 );
	_outtext("4.00 ");
	_settextposition( r_row,69 );
	_outtext("3.75 ");

	r_row = 2;
	_settextposition( r_row,2 );
	_outtext("DE");
	_settextposition( r_row,7 );
	_outtext("06:00AM");
	_settextposition( r_row,18 );
	_outtext("03:00PM");
	_settextposition( r_row,29 );
	_outtext("5.00");
	_settextposition( r_row,37 );
	_outtext("4.75 ");
	_settextposition( r_row,45 );
	_outtext("4.25 ");
	_settextposition( r_row,53 );
	_outtext("4.00 ");
	_settextposition( r_row,61 );
	_outtext("3.75 ");
	_settextposition( r_row,69 );
	_outtext("3.50 ");

	r_row = 3;
	_settextposition( r_row,2 );
	_outtext("DE");
	_settextposition( r_row,7 );
	_outtext("03:00PM");
	_settextposition( r_row,18 );
	_outtext("12:00PM");
	_settextposition( r_row,29 );
	_outtext("6.00 ");
	_settextposition( r_row,37 );
	_outtext("5.25 ");
	_settextposition( r_row,45 );
	_outtext("4.75 ");
	_settextposition( r_row,53 );
	_outtext("4.25 ");
	_settextposition( r_row,61 );
	_outtext("4.00 ");
	_settextposition( r_row,69 );
	_outtext("3.75 ");
	close_window(0);
	open_window(11,2,75,13,fcolor,(long)hcolor,205,fcolor,hcolor );

	_outtext(" In the example above,  The entries coded \'DE\' as the day of the week\n");
	_outtext(" are default rates which must be present.  These default rates are used\n");
	_outtext(" by the computer to calculate the charges for each customer. The default\n");
	_outtext(" rates must be entered for one complete 24 hour period even though your\n");
	_outtext(" business may not be open for 24 hours.\n");
	_outtext(" If you have special rates that take effect only on designated days and\n");
	_outtext(" times, they can be added to the rate schedule.  The special rates will\n");
	_outtext(" take precedence over the default rates.\n\n\n");
	_outtext("                 Press any key to continue !!");
	getch();
	fflush( stdin );
	_settextwindow(7,3,19,76);

	r_row = 4;
	_settextposition( r_row,2 );
	_outtext("MO");
	_settextposition( r_row,7 );
	_outtext("10:00AM");
	_settextposition( r_row,18 );
	_outtext("05:00PM");
	_settextposition( r_row,29 );
	_outtext("3.00 ");
	_settextposition( r_row,37 );
	_outtext("1.50 ");
	_settextposition( r_row,45 );
	_outtext("1.00 ");
	_settextposition( r_row,53 );
	_outtext("1.00 ");
	_settextposition( r_row,61 );
	_outtext("1.00 ");
	_settextposition( r_row,69 );
	_outtext("1.00 ");
	close_window(0);
	open_window(11,2,75,14,fcolor,(long)hcolor,205,fcolor,hcolor );

	_outtext(" The above example sets the rates for every day of the week to\n");
	_outtext(" the following: from 00:00AM to 6:00AM the one player rate will\n");
	_outtext(" be $6.00 per hour, the two player rate will be $5.25 per hour amd\n");
	_outtext(" so on;  from 6.00AM to 3:00PM, the one player rate will be $5.00\n");
	_outtext(" per hour, the two player rate will be $4.75 per hour and so on;\n");
	_outtext(" from 3:00PM to 12:00PM the one player rate will be $6.00, the two\n");
	_outtext(" player rate will be $5.25 and so on.  On MONDAY from 10:00AM to\n");
	_outtext(" 5:00PM the special rates will be, one player $3.00 per hour, two \n");
	_outtext(" players $1.50, and so on.\n");
	_outtext(" You may add as many special rates for the different days of the\n");
	_outtext(" week as you require.\n");
	_outtext("                 Press any key to continue !!");
	getch();
	fflush( stdin );
	}

/***************** print help screen ***********************************/
hlp_rate()
{
	_settextposition( 1,17 ); _outtext("RATE SCHEDULE INSTRUCTIONS AND ILLUSTRATIONS");
	_settextposition( 2,1 );  _outtext("ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ");
	_settextposition( 3,1 );  _outtext("NOTE: If you are a first-time user of this program or if you want to");
	_settextposition( 4,7 );  _outtext("review the explanations with illustrations, PRESS THE F1 KEY NOW !!");
	_settextposition( 6,15 ); _outtext("--SPECIAL CONTROL KEYS AND THEIR USAGE--");
	_settextposition( 8,3 );  _outtext("1. Press the F6 key to DELETE an entire line from the rate schedule.");
	_settextposition( 9,6 ); _outtext("The line to be deleted will be determined by the location of the");
	_settextposition( 10,6 ); _outtext(" cursor.");
	_settextposition( 12,3 ); _outtext("2. Press the F10 key when you have completed all entries to the rate");
	_settextposition( 13,6 ); _outtext("schedule or if you want to review the next rate schedule. ");
	_settextposition( 15,3 ); _outtext("3. Press the F8 key when you want to delete the entire rate schedule");
	_settextposition( 16,6 ); _outtext("currently displayed on the screen.");
	_settextposition( 18,12 ); _outtext("Press the space bar to return to rate schedule update. ");
}
/************************ RATE SCREEN LAYOUT ****************************/
rate_lay()
{
	char extern start_tab[3], stop_tab[3];
	int extern h_from;
	_settextwindow(0,0,24,79);
	_clearscreen(_GCLEARSCREEN);
	_settextposition( 1,18 ); _outtext("H O U R L Y    R E N T A L    R A T E S");
	_settextposition( 2,23 ); _outtext("S C H E D U L E    U P D A T E");
	_settextposition( 4,3 ); _outtext("WEEK");
	_settextposition( 4,11 ); _outtext("START");
	_settextposition( 4,22 ); _outtext("STOP");
	_settextposition( 4,30 ); _outtext("-----HOURLY TABLE RENTAL RATES BY PLAYERS------");
	_settextposition( 5,3 ); _outtext("DAY");
	_settextposition( 5,11 ); _outtext("TIME");
	_settextposition( 5,22 ); _outtext("TIME");
	_settextposition( 5,33 ); _outtext("1");
	_settextposition( 5,41 ); _outtext("2");
	_settextposition( 5,49 ); _outtext("3");
	_settextposition( 5,57 ); _outtext("4");
	_settextposition( 5,65 ); _outtext("5");
	_settextposition( 5,73 ); _outtext("6");
	_settextposition( 6,2 ); _outtext("ÚÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
	_settextposition( 7,2 ); _outtext("³");
	_settextposition( 7,7 ); _outtext("³");
	_settextposition( 7,18 ); _outtext("³");
	_settextposition( 7,29 ); _outtext("³");
	_settextposition( 7,37 ); _outtext("³");
	_settextposition( 7,45 ); _outtext("³");
	_settextposition( 7,53 ); _outtext("³");
	_settextposition( 7,61 ); _outtext("³");
	_settextposition( 7,69 ); _outtext("³");
	_settextposition( 7,77 ); _outtext("³");
	_settextposition( 8,2 ); _outtext("³");
	_settextposition( 8,7 ); _outtext("³");
	_settextposition( 8,18 ); _outtext("³");
	_settextposition( 8,29 ); _outtext("³");
	_settextposition( 8,37 ); _outtext("³");
	_settextposition( 8,45 ); _outtext("³");
	_settextposition( 8,53 ); _outtext("³");
	_settextposition( 8,61 ); _outtext("³");
	_settextposition( 8,69 ); _outtext("³");
	_settextposition( 8,77 ); _outtext("³");
	_settextposition( 9,2 ); _outtext("³");
	_settextposition( 9,7 ); _outtext("³");
	_settextposition( 9,18 ); _outtext("³");
	_settextposition( 9,29 ); _outtext("³");
	_settextposition( 9,37 ); _outtext("³");
	_settextposition( 9,45 ); _outtext("³");
	_settextposition( 9,53 ); _outtext("³");
	_settextposition( 9,61 ); _outtext("³");
	_settextposition( 9,69 ); _outtext("³");
	_settextposition( 9,77 ); _outtext("³");
	_settextposition( 10,2 ); _outtext("³");
	_settextposition( 10,7 ); _outtext("³");
	_settextposition( 10,18 ); _outtext("³");
	_settextposition( 10,29 ); _outtext("³");
	_settextposition( 10,37 ); _outtext("³");
	_settextposition( 10,45 ); _outtext("³");
	_settextposition( 10,53 ); _outtext("³");
	_settextposition( 10,61 ); _outtext("³");
	_settextposition( 10,69 ); _outtext("³");
	_settextposition( 10,77 ); _outtext("³");
	_settextposition( 11,2 ); _outtext("³");
	_settextposition( 11,7 ); _outtext("³");
	_settextposition( 11,18 ); _outtext("³");
	_settextposition( 11,29 ); _outtext("³");
	_settextposition( 11,37 ); _outtext("³");
	_settextposition( 11,45 ); _outtext("³");
	_settextposition( 11,53 ); _outtext("³");
	_settextposition( 11,61 ); _outtext("³");
	_settextposition( 11,69 ); _outtext("³");
	_settextposition( 11,77 ); _outtext("³");
	_settextposition( 12,2 ); _outtext("³");
	_settextposition( 12,7 ); _outtext("³");
	_settextposition( 12,18 ); _outtext("³");
	_settextposition( 12,29 ); _outtext("³");
	_settextposition( 12,37 ); _outtext("³");
	_settextposition( 12,45 ); _outtext("³");
	_settextposition( 12,53 ); _outtext("³");
	_settextposition( 12,61 ); _outtext("³");
	_settextposition( 12,69 ); _outtext("³");
	_settextposition( 12,77 ); _outtext("³");
	_settextposition( 13,2 ); _outtext("³");
	_settextposition( 13,7 ); _outtext("³");
	_settextposition( 13,18 ); _outtext("³");
	_settextposition( 13,29 ); _outtext("³");
	_settextposition( 13,37 ); _outtext("³");
	_settextposition( 13,45 ); _outtext("³");
	_settextposition( 13,53 ); _outtext("³");
	_settextposition( 13,61 ); _outtext("³");
	_settextposition( 13,69 ); _outtext("³");
	_settextposition( 13,77 ); _outtext("³");
	_settextposition( 14,2 ); _outtext("³");
	_settextposition( 14,7 ); _outtext("³");
	_settextposition( 14,18 ); _outtext("³");
	_settextposition( 14,29 ); _outtext("³");
	_settextposition( 14,37 ); _outtext("³");
	_settextposition( 14,45 ); _outtext("³");
	_settextposition( 14,53 ); _outtext("³");
	_settextposition( 14,61 ); _outtext("³");
	_settextposition( 14,69 ); _outtext("³");
	_settextposition( 14,77 ); _outtext("³");
	_settextposition( 15,2 ); _outtext("³");
	_settextposition( 15,7 ); _outtext("³");
	_settextposition( 15,18 ); _outtext("³");
	_settextposition( 15,29 ); _outtext("³");
	_settextposition( 15,37 ); _outtext("³");
	_settextposition( 15,45 ); _outtext("³");
	_settextposition( 15,53 ); _outtext("³");
	_settextposition( 15,61 ); _outtext("³");
	_settextposition( 15,69 ); _outtext("³");
	_settextposition( 15,77 ); _outtext("³");
	_settextposition( 16,2 ); _outtext("ÀÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ");


		print_ins();
		if(h_from>0||start_tab[0] != '\0')
		{
			_settextposition(17,5);
			_outtext("The above rate schedule will be applied to tables ");
		_settextcolor(hcolor);
		_setbkcolor((long)fcolor);

			_outtext(start_tab);
		_settextcolor(fcolor);
		_setbkcolor((long)hcolor);

			_outtext(" thru ");
		_settextcolor(hcolor);
		_setbkcolor((long)fcolor);

			_outtext(stop_tab);
		_settextcolor(fcolor);
		_setbkcolor((long)hcolor);

			_outtext(" only.");
		}
}

print_ins()
{
	_settextposition(23,2);
	_settextcolor(hcolor);
	_setbkcolor((long)fcolor);
	_outtext("Press the F1 key at any time for instructions, F10 to exit this schedule.   ");
	_settextposition(24,2);
	_outtext("F6 to delete a line, or F8 to delete the entire schedule curently displayed.");
	_settextcolor(fcolor);
	_setbkcolor((long)hcolor);
}

