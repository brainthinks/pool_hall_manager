/*
		THIS MODULE DISPLAYS THE EMPLOYER MENU
*/
#include<conio.h>

int extern fcolor;
int extern b_green,b_black,f_yellow,b_brown,f_brown,f_black;
/******************** PRINT EMPLOYER MENU *************************/
pool3s()
{
	int  extern hcolor,mono;
	textbackground(b_black);
	clrscr();
	open_window(3,5,70,20,f_brown,b_green,205,f_brown,b_green);
	open_window(6,17,50,3,f_black,b_black,32,f_black,b_black);
	open_window(5,15,50,3,b_black,f_brown,205,b_black,f_brown);
	cputs("        M A N A G E M E N T     M E N U");
	window(1,1,80,25);
	textbackground(b_green);
	textcolor(f_black);
	gotoxy(15,10);
	cputs("      1. Review daily rental cash receipts.");
	gotoxy(15,12);
	cputs("      2. Assign employee passwords.");
	gotoxy(15,14);
	cputs("      3. Enter your business' name & address.");
	gotoxy(15,16);
	cputs("      4. Update rate schedules.");
	gotoxy(15,18);
	cputs("      5. Return to previous menu.");
	gotoxy(15,20);
	cputs("           Enter selection number. °");
	gotoxy(50,20);
return 0;
}

