/*                  		THIS MODULE DISPLAYS THE MAIN MENU
*/
#include<conio.h>
/**************** PRINT MAIN MENU**********************************/
void pool1s()
{
	int extern mono;
	int extern hcolor;
	int extern fcolor;
	int extern b_red,b_black,b_yellow,b_white,b_grey,b_cyan,b_blue,b_bwhite;
	int extern f_red,f_black,f_yellow,f_white,f_grey,f_cyan,f_blue,f_bwhite;

	char extern na_buff[4][49];
	textbackground( f_black);


	clrscr();
	/*
	printf("Background = %d , Forground = %d ",fcolor,hcolor);
	*/
	open_window(3,4,73,21,f_black, b_cyan,205,f_black,b_cyan);
	if (mono==0)
	{
		open_window(6,17,51,6,f_black, b_black,219,f_black,b_black);
		clrscr();
	}
	open_window(5,15,51,6,b_bwhite, f_blue,205,b_bwhite,f_blue);

	gotoxy(  (48 - strlen(na_buff[0])) /2,1 );
	cputs(na_buff[0]);
	cputs("\n");
	gotoxy(  (48 - strlen(na_buff[1])) /2,2 );
	cputs(na_buff[1]);
	cputs("\n");
	gotoxy(  (48 - strlen(na_buff[2])) /2,3 );
	cputs(na_buff[2]);
	cputs("\n");
	gotoxy(  (48 - strlen(na_buff[3])) /2,4 );
	cputs(na_buff[3]);

	window(1,1,80,24);
	textcolor(f_black);
	textbackground( b_cyan);
	gotoxy(18,14);
	cputs("             1. Table rental menu.");
	gotoxy(18,16);
	cputs("             2. Employer menu.");
	gotoxy(18,18);
	cputs("             3. Exit this program.");
	gotoxy(18,20);
	cputs("          Enter selection number. °");
	gotoxy(52,20);

}

