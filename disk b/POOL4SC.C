/*
		THIS MODULE DISPLAYS THE RENTAL MENU - PAGE 2
*/

#include<conio.h>
int extern fcolor,f_yellow;
int extern hcolor;

pool4()
{
		open_window(13,1,77,11,fcolor,hcolor,32,fcolor,hcolor);
		window(1,13,78,23);

		gotoxy(1,1);
		textcolor(f_yellow);
		cputs("  ออออออออออออออออออออออออออออออออออออัอออออออออออออออออออออออออออออออออออออออ");

		gotoxy(1,2);
		cputs("    1. Clear table from daily         ณ  5. Set table to employee player/s.");
		gotoxy(1,3);
		cputs("       cash receipts.                 ณ");
		gotoxy(1,4);
		cputs("                                      ณ     Activate promotional rental");
		gotoxy(1,5);
		cputs("    2. Issue a credit.                ณ     rates.");
		gotoxy(1,6);
		cputs("                                      ณ");
		gotoxy(1,7);
		cputs("    3. Change incorrect table start   ณ  7. Return to page 1 of rental menu.");
		gotoxy(1,8);
		cputs("       time.                          ณ");
		gotoxy(1,9);
		cputs("                                      ณ");
		gotoxy(1,10);
		cputs("    4. Change incorrect number of     ณ");
		gotoxy(1,11);
		cputs("       players.                       ณ");
		window(1,1,80,25);
return 0;
}
