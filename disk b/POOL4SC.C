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
		cputs("  様様様様様様様様様様様様様様様様様様冤様様様様様様様様様様様様様様様様様様様");

		gotoxy(1,2);
		cputs("    1. Clear table from daily         �  5. Set table to employee player/s.");
		gotoxy(1,3);
		cputs("       cash receipts.                 �");
		gotoxy(1,4);
		cputs("                                      �     Activate promotional rental");
		gotoxy(1,5);
		cputs("    2. Issue a credit.                �     rates.");
		gotoxy(1,6);
		cputs("                                      �");
		gotoxy(1,7);
		cputs("    3. Change incorrect table start   �  7. Return to page 1 of rental menu.");
		gotoxy(1,8);
		cputs("       time.                          �");
		gotoxy(1,9);
		cputs("                                      �");
		gotoxy(1,10);
		cputs("    4. Change incorrect number of     �");
		gotoxy(1,11);
		cputs("       players.                       �");
		window(1,1,80,25);
return 0;
}
