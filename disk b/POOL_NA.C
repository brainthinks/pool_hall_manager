/*
		THIS MODULE MAINTAINS AND DISPLAYS THE EMPLOYOR NAME AND ADDRESS
*/
#include<stdio.h>
#include<conio.h>
FILE *na;
char na_buff[4][49];
	int centr;
	int extern fcolor;
	int extern b_red,b_black,b_yellow,b_white,b_grey,b_cyan,b_blue,b_bwhite;
	int extern b_green,b_lblue,b_lcyan,b_lmagenta,b_lgreen,b_lred,b_brown;
	int extern f_red,f_black,f_yellow,f_white,f_grey,f_cyan,f_blue,f_bwhite;
	int extern f_green,f_lblue,f_lcyan,f_lmagenta,f_lgreen,f_lred,f_brown;

/************************* RETRIEVE NAME AND ADDRESS ****************/
void pool_nar()

{
	if(( na=fopen ("n_a.txt" ,"rb") ) != '\0')
	{
		fread(&na_buff,196,1,na);
		fclose(na);
	}
	else
	{
		memset(na_buff,' ',196);
		strcpy(&na_buff[0],"Business name");
		strcpy(&na_buff[1],"Street address");
		strcpy(&na_buff[2],"City & state");
		strcpy(&na_buff[3],"Phone no:");

		if(( na=fopen ("n_a.txt" ,"wb") ) != '\0')
		{
			fwrite(&na_buff,196,1,na);
			fclose(na);
		}
		else
		{
		cputs("disk write error");
		exit(0);
		}
	}
}
/****************** UPDATE NAME AND ADDRESS ****************/
void pool_naw()
{
	char c;
	char extern buf[80];
	int extern hcolor;
	c=' ';
	while(1)
	{
		clrscr();
		open_window(3,4,75,5,b_blue,f_cyan,205,f_blue,b_cyan);
		gotoxy(20,2);
		cputs("BUSINESS  NAME AND ADDRESS UPDATE");
		window(1,1,80,24);
		gotoxy(4,19);
		textcolor(fcolor);
		textbackground(hcolor);
		cputs("Enter your business' name, address and phone number.");

		gotoxy(4,10);
		cputs("Enter business name:      ");
		textcolor(b_black);
		textbackground(f_white);
		pad(0);
		cputs(na_buff[0]);
		gotoxy(30,10);
		reads(48,&na_buff[0],0,1,0,0);

		textcolor(fcolor);
		textbackground(hcolor);
		gotoxy(4,12);
		cputs("Enter street address:     ");
		textcolor(b_black);
		textbackground(f_white);
		pad(1);
		cputs(na_buff[1]);
		gotoxy(30,12);
		reads(48,&na_buff[1],0,1,0,0);

		textcolor(fcolor);
		textbackground(hcolor);
		gotoxy(4,14);
		cputs("Enter city & state:       ");
		textcolor(b_black);
		textbackground(f_white);
		pad(2);
		cputs(na_buff[2]);
		gotoxy(30,14);
		reads(48,&na_buff[2],0,1,0,0);

		textcolor(fcolor);
		textbackground(hcolor);
		gotoxy(4,16);
		cputs("Enter phone number:       ");
		textcolor(b_black);
		textbackground(f_white);
		pad(3);
		cputs(na_buff[3]);
		gotoxy(30,16);
		reads(48,&na_buff[3],0,1,0,0);

		open_window(19,20,40,4,f_bwhite,b_black,205,f_black,b_brown);
		cputs(" Is the above correct ?\n\r");
		cputs(" Enter 'Y' for yes, 'N' for no.");
		c=getch();
		close_window(0);
		if(toupper(c)!='Y'){ close_window(1); continue;}
		break;
	}

	open_window(10,20,40,4,f_yellow,b_black,32,b_red,f_red);
	cputs("      Please wait -- updating file.");
	if(( na=fopen ("n_a.txt" ,"wb") ) != '\0')
	{
		fwrite(&na_buff,196,1,na);
		fclose(na);
	}
	else
	{
	cputs("disk write error");
	exit(0);
	}
	close_window(1);
}
/********** pad blanks right on all n & a fields ***********************/
pad(int no)
{
	int y,x;
	x=48;
	y=strlen(na_buff[no]);
	na_buff[no][x--] = '\0';
	while(x-->y)
	na_buff[no][x] = ' ';
	return 0;
}





