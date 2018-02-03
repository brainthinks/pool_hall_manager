/*
	THIS MODULE CONTAINS HELP SCREENS AND RATE SCHEDULE SCREEN LAYOUT
*/

#include<conio.h>
#include<stdio.h>
int extern hcolor;
int extern fcolor;
int extern b_black;
int extern b_red,b_black,b_yellow,b_white,b_grey,b_cyan,b_blue,b_bwhite;
int extern b_green,b_lblue,b_lcyan,b_lmagenta,b_lgreen,b_lred,b_brown;
int extern f_red,f_black,f_yellow,f_white,f_grey,f_cyan,f_blue,f_bwhite;
int extern f_green,f_lblue,f_lcyan,f_lmagenta,f_lgreen,f_lred,f_brown;

/******************** DEFAULT RATE MESSAGE ******************************/
	default_mesg()
	{
	int r_row;
	open_window(11,2,75,13,f_black,b_white,205,f_black,b_white );
	cputs(" You must enter the hourly rates established by your business into a   \n\r");
	cputs(" rate schedule.  There can be multiple rate schedules.  Rates can apply\n\r");
	cputs(" to seperate groups of rental pool tables.   \n\r");
	cputs(" For example -- Pool tables 1 thru 6 can have one set of hourly rental\n\r");
	cputs(" rates and pool tables 7 thru 12 can have a different set of hourly\n\r");
	cputs(" rates.\n\r");
	cputs(" You can establish as many rate schedules as needed for your business.\n\r\n\r\n\r\n\r");
	cputs("                 Press any key to continue !!");
	getch();
	fflush( stdin );
	window(3,7,76,19);
	textcolor(f_black);
	textbackground(b_cyan);
	r_row = 1;
	gotoxy( 2,r_row );
	cputs("DE");
	gotoxy( 7,r_row );
	cputs("00:00AM");
	gotoxy( 18,r_row );
	cputs("06:00AM");
	gotoxy( 29,r_row );
	cputs("6.00 ");
	gotoxy( 37,r_row );
	cputs("5.25 ");
	gotoxy( 45,r_row );
	cputs("4.75 ");
	gotoxy( 53,r_row );
	cputs("4.25 ");
	gotoxy( 61,r_row );
	cputs("4.00 ");
	gotoxy( 69,r_row );
	cputs("3.75 ");

	r_row = 2;
	gotoxy( 2,r_row );
	cputs("DE");
	gotoxy( 7,r_row );
	cputs("06:00AM");
	gotoxy( 18,r_row );
	cputs("03:00PM");
	gotoxy( 29,r_row );
	cputs("5.00");
	gotoxy( 37,r_row );
	cputs("4.75 ");
	gotoxy( 45,r_row );
	cputs("4.25 ");
	gotoxy( 53,r_row );
	cputs("4.00 ");
	gotoxy( 61,r_row );
	cputs("3.75 ");
	gotoxy( 69,r_row );
	cputs("3.50 ");

	r_row = 3;
	gotoxy( 2,r_row );
	cputs("DE");
	gotoxy( 7,r_row );
	cputs("03:00PM");
	gotoxy( 18,r_row );
	cputs("12:00PM");
	gotoxy( 29,r_row );
	cputs("6.00 ");
	gotoxy( 37,r_row );
	cputs("5.25 ");
	gotoxy( 45,r_row );
	cputs("4.75 ");
	gotoxy( 53,r_row );
	cputs("4.25 ");
	gotoxy( 61,r_row );
	cputs("4.00 ");
	gotoxy( 69,r_row );
	cputs("3.75 ");
	close_window(0);
	open_window(11,2,75,13,f_black,b_white,205,f_black,b_white );

	cputs(" In the example above,  The entries coded \'DE\' as the day of the week\n\r");
	cputs(" are default rates which must be present.  These default rates are used\n\r");
	cputs(" by the computer to calculate the charges for each customer. The default\n\r");
	cputs(" rates must be entered for one complete 24 hour period even though your\n\r");
	cputs(" business may not be open for 24 hours.\n\r");
	cputs(" If you have special rates that take effect only on designated days and\n\r");
	cputs(" times, they can be added to the rate schedule.  The special rates will\n\r");
	cputs(" take precedence over the default rates.\n\r\n\r\n\r");
	cputs("                 Press any key to continue !!");
	getch();
	fflush( stdin );
	window(3,7,76,19);
	textcolor(f_black);
	textbackground(b_cyan);

	r_row = 4;
	gotoxy( 2,r_row );
	cputs("MO");
	gotoxy( 7,r_row );
	cputs("10:00AM");
	gotoxy( 18,r_row );
	cputs("05:00PM");
	gotoxy( 29,r_row );
	cputs("3.00 ");
	gotoxy( 37,r_row );
	cputs("1.50 ");
	gotoxy( 45,r_row );
	cputs("1.00 ");
	gotoxy( 53,r_row );
	cputs("1.00 ");
	gotoxy( 61,r_row );
	cputs("1.00 ");
	gotoxy( 69,r_row );
	cputs("1.00 ");
	close_window(0);
	open_window(11,2,75,14,f_black,b_white,205,f_black,b_white );

	cputs(" The above example sets the rates for every day of the week to\n\r");
	cputs(" the following: From 00:00AM to 6:00AM the one player rate will\n\r");
	cputs(" be $6.00 per hour, the two player rate will be $5.25 per hour amd\n\r");
	cputs(" so on.  From 6.00AM to 3:00PM, the one player rate will be $5.00\n\r");
	cputs(" per hour, the two player rate will be $4.75 per hour and so on.\n\r");
	cputs(" From 3:00PM to 12:00PM the one player rate will be $6.00, the two\n\r");
	cputs(" player rate will be $5.25 and so on.  On MONDAY from 10:00AM to\n\r");
	cputs(" 5:00PM the special rates will be, one player $3.00 per hour, two \n\r");
	cputs(" players $1.50, and so on.\n\r");
	cputs(" You may add as many special rates for the different days of the\n\r");
	cputs(" week as you require.\n\r");
	cputs("                 Press any key to continue !!");
	getch();
	fflush( stdin );
	return 0;
	}

/***************** print help screen ***********************************/
hlp_rate()
{



	gotoxy( 17,1 ); cputs("RATE SCHEDULE INSTRUCTIONS AND ILLUSTRATIONS");
	gotoxy( 1,2 );  cputs("ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ");
	gotoxy( 1,3 );  cputs("NOTE: If you are a first-time user of this program or if you want to");
	gotoxy( 7,4 );  cputs("review the explanations with illustrations, PRESS THE F1 KEY NOW !!");
	gotoxy( 15,6 ); cputs("--SPECIAL CONTROL KEYS AND THEIR USAGE--");
	gotoxy( 3,8 );  cputs("1. Press the F6 key to DELETE an entire line from the rate schedule.");
	gotoxy( 6,9 ); cputs("The line to be deleted will be determined by the location of the");
	gotoxy( 6,10 ); cputs(" cursor.");
	gotoxy( 3,12 ); cputs("2. Press the F10 key when you have completed all entries to the rate");
	gotoxy( 6,13 ); cputs("schedule or if you want to review the next rate schedule. ");
	gotoxy( 3,15 ); cputs("3. Press the F8 key when you want to delete the entire rate schedule");
	gotoxy( 6,16 ); cputs("currently displayed on the screen.");
	gotoxy( 12,18 ); cputs("Press the space bar to return to rate schedule update. ");
return 0;
}
/************************ RATE SCREEN LAYOUT ****************************/
rate_lay()
{

	char extern start_tab[3], stop_tab[3];
	int extern h_from;

	window(1,1,80,16);
	textcolor(f_black);
	textbackground(b_cyan);
	clrscr();
	gotoxy( 18,1 ); cputs("H O U R L Y    R E N T A L    R A T E S");
	gotoxy( 23,2 ); cputs("S C H E D U L E    U P D A T E");



	window(1,1,80,25);
	gotoxy( 3,4 ); cputs("WEEK");
	gotoxy( 11,4 ); cputs("START");
	gotoxy( 22,4 ); cputs("STOP");
	gotoxy( 30,4 ); cputs("-----HOURLY TABLE RENTAL RATES BY PLAYERS------");
	gotoxy( 3,5 ); cputs("DAY");
	gotoxy( 11,5 ); cputs("TIME");
	gotoxy( 22,5 ); cputs("TIME");
	gotoxy( 33,5 ); cputs("1");
	gotoxy( 41,5 ); cputs("2");
	gotoxy( 49,5 ); cputs("3");
	gotoxy( 57,5 ); cputs("4");
	gotoxy( 65,5 ); cputs("5");
	gotoxy( 73,5 ); cputs("6");
	gotoxy( 2,6 ); cputs("ÚÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿");
	gotoxy( 2,7 ); cputs("³");
	gotoxy( 7,7 ); cputs("³");
	gotoxy( 18,7 ); cputs("³");
	gotoxy( 29,7 ); cputs("³");
	gotoxy( 37,7 ); cputs("³");
	gotoxy( 45,7 ); cputs("³");
	gotoxy( 53,7 ); cputs("³");
	gotoxy( 61,7 ); cputs("³");
	gotoxy( 69,7 ); cputs("³");
	gotoxy( 77,7 ); cputs("³");
	gotoxy( 2,8 ); cputs("³");
	gotoxy( 7,8 ); cputs("³");
	gotoxy( 18,8 ); cputs("³");
	gotoxy( 29,8 ); cputs("³");
	gotoxy( 37,8 ); cputs("³");
	gotoxy( 45,8 ); cputs("³");
	gotoxy( 53,8 ); cputs("³");
	gotoxy( 61,8 ); cputs("³");
	gotoxy( 69,8 ); cputs("³");
	gotoxy( 77,8 ); cputs("³");
	gotoxy( 2,9 ); cputs("³");
	gotoxy( 7,9 ); cputs("³");
	gotoxy( 18,9 ); cputs("³");
	gotoxy( 29,9 ); cputs("³");
	gotoxy( 37,9 ); cputs("³");
	gotoxy( 45,9 ); cputs("³");
	gotoxy( 53,9 ); cputs("³");
	gotoxy( 61,9 ); cputs("³");
	gotoxy( 69,9 ); cputs("³");
	gotoxy( 77,9 ); cputs("³");
	gotoxy( 2,10 ); cputs("³");
	gotoxy( 7,10 ); cputs("³");
	gotoxy( 18,10 ); cputs("³");
	gotoxy( 29,10 ); cputs("³");
	gotoxy( 37,10 ); cputs("³");
	gotoxy( 45,10 ); cputs("³");
	gotoxy( 53,10 ); cputs("³");
	gotoxy( 61,10 ); cputs("³");
	gotoxy( 69,10 ); cputs("³");
	gotoxy( 77,10 ); cputs("³");
	gotoxy( 2,11 ); cputs("³");
	gotoxy( 7,11 ); cputs("³");
	gotoxy( 18,11 ); cputs("³");
	gotoxy( 29,11 ); cputs("³");
	gotoxy( 37,11 ); cputs("³");
	gotoxy( 45,11 ); cputs("³");
	gotoxy( 53,11 ); cputs("³");
	gotoxy( 61,11 ); cputs("³");
	gotoxy( 69,11 ); cputs("³");
	gotoxy( 77,11 ); cputs("³");
	gotoxy( 2,12 ); cputs("³");
	gotoxy( 7,12 ); cputs("³");
	gotoxy( 18,12 ); cputs("³");
	gotoxy( 29,12 ); cputs("³");
	gotoxy( 37,12 ); cputs("³");
	gotoxy( 45,12 ); cputs("³");
	gotoxy( 53,12 ); cputs("³");
	gotoxy( 61,12 ); cputs("³");
	gotoxy( 69,12 ); cputs("³");
	gotoxy( 77,12 ); cputs("³");
	gotoxy( 2,13 ); cputs("³");
	gotoxy( 7,13 ); cputs("³");
	gotoxy( 18,13 ); cputs("³");
	gotoxy( 29,13 ); cputs("³");
	gotoxy( 37,13 ); cputs("³");
	gotoxy( 45,13 ); cputs("³");
	gotoxy( 53,13 ); cputs("³");
	gotoxy( 61,13 ); cputs("³");
	gotoxy( 69,13 ); cputs("³");
	gotoxy( 77,13 ); cputs("³");
	gotoxy( 2,14 ); cputs("³");
	gotoxy( 7,14 ); cputs("³");
	gotoxy( 18,14 ); cputs("³");
	gotoxy( 29,14 ); cputs("³");
	gotoxy( 37,14 ); cputs("³");
	gotoxy( 45,14 ); cputs("³");
	gotoxy( 53,14 ); cputs("³");
	gotoxy( 61,14 ); cputs("³");
	gotoxy( 69,14 ); cputs("³");
	gotoxy( 77,14 ); cputs("³");
	gotoxy( 2,15 ); cputs("³");
	gotoxy( 7,15 ); cputs("³");
	gotoxy( 18,15 ); cputs("³");
	gotoxy( 29,15 ); cputs("³");
	gotoxy( 37,15 ); cputs("³");
	gotoxy( 45,15 ); cputs("³");
	gotoxy( 53,15 ); cputs("³");
	gotoxy( 61,15 ); cputs("³");
	gotoxy( 69,15 ); cputs("³");
	gotoxy( 77,15 ); cputs("³");
	gotoxy( 2,16 ); cputs("ÀÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ");

	textcolor(fcolor);
	textbackground(hcolor);
		print_ins();
		if(h_from>0||start_tab[0] != '\0')
		{
			gotoxy(1,17);
			textcolor(f_bwhite);
			textbackground(b_black);
			cputs("     The above rate schedule will be applied to tables ");
			cputs(start_tab);
			cputs(" thru ");
			cputs(stop_tab);
			cputs(" only.         ");
		}
return 0;
}

print_ins()
{
	gotoxy(2,23);
	textcolor(b_black);
	textbackground(fcolor);
	cputs("Press the F1 key at any time for instructions, F10 to exit this schedule.   ");
	gotoxy(2,24);
	cputs("F6 to delete a line, or F8 to delete the entire schedule curently displayed.");
	textcolor(fcolor);
	textbackground(hcolor);
return 0;
}

