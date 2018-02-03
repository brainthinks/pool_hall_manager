/*
		THIS MODULE MAINTAINS AND DISPLAYS EMMPLOYEE INFORMATION
*/
#include<conio.h>
#include<stdio.h>
	int extern b_red,b_black,b_yellow,b_white,b_grey,b_cyan,b_blue,b_bwhite;
	int extern b_green,b_lblue,b_lcyan,b_lmagenta,b_lgreen,b_lred,b_brown;
	int extern f_red,f_black,f_yellow,f_white,f_grey,f_cyan,f_blue,f_bwhite;
	int extern f_green,f_lblue,f_lcyan,f_lmagenta,f_lgreen,f_lred,f_brown;

	struct  employee
	{
		char  name[21];
		char  passw[5];
	} emp[16];

	 FILE  *fpe;
	int extern fcolor;
	int  extern hcolor;
/************* LIST EMPLOYEES ************************************/
void list_emp()
{

	int extern emp_no,x,y;
	char extern emp_nos[3];
	emp_no=0;
	close_window(1);
	textbackground(b_black);
	clrscr();
	open_window(1,15,50,3,b_blue,f_cyan,205,b_blue,f_cyan);
	cputs("            UPDATE EMPLOYEE RECORDS");
	open_window(4,15,50,20,f_bwhite,b_black,196,f_bwhite,b_black);
	x=2;        /*print row*/
	y=1;        /*array number*/
	gotoxy(4,1);
	textcolor(fcolor);
	textbackground(hcolor);
	cputs("EMP. # ");
	gotoxy(13,1);
	cputs("NAME                  ");
	gotoxy(37,1);
	cputs("PASSWORD");
loop2:
	gotoxy(4,x++);
	if(*emp[y].name>' ')         /* print all emp */
	{
	printf(" %2d      %-20s     %4s\r",y,emp[y].name,emp[y].passw);
	}
	y++;
	if(y < 16) goto loop2;
	++x;
	for(emp_no =0;emp_no==0 || emp_no>15; )    /* get emp to update */
	{
		window(1,1,80,25);
		gotoxy(14,25);
		textcolor(f_black);
		textbackground(b_white);
		cputs(" To update enter employee number - or 99 to exit. °°");
		gotoxy(64,25);
		emp_nos[0]='\0';          /* use this field for temp storage */
		reads(2,emp_nos,0,1,0,0);
		emp_no = atoi(emp_nos);
		fflush(stdin);
		if (emp_no == 99) break;
		if(emp_no >15)
		{
			open_window(10,22,36,4,f_yellow,b_red,32,b_red,f_red);
			cputs(" Employee number must be 1 to 15.\n\r");
			cputs(" Press any key to continue.");
			getch();
			fflush(stdin);
			close_window(0);
			continue;
		}
	}
	close_window(1);
}
/********************* UPDATE EMPLOYEE RECORDS ******************/
void update_emp()
{
	while(1)
	{
		int extern emp_no;
		list_emp();
		if(emp_no == 99) break;
		open_window(10,10,60,9,fcolor,hcolor,205,fcolor,hcolor);
		gotoxy(2,2);
		printf("Name currently:  %-20s Password = %4s\n",\
				emp[emp_no].name,emp[emp_no].passw);
		gotoxy(2,4);
		cputs("Enter name:  ");
		textcolor(b_black);
		textbackground(fcolor);
		cputs("                    \r");
		gotoxy(15,4);
		cputs(emp[emp_no].name);
		gotoxy(15,4);
		reads(20,emp[emp_no].name,0,1,0,0);
		textcolor(fcolor);
		textbackground(hcolor);
		gotoxy(2,6);
		cputs("Enter password:  ");
		textcolor(b_black);
		textbackground(fcolor);
		cputs("    ");
		gotoxy(19,6);
		cputs(emp[emp_no].passw);
		gotoxy(19,6);
		reads(4,emp[emp_no].passw,0,1,1,0);
	}

}
/*************** READ EMPLOYEE RECORDS FROM DISKETTE *******/
void pool_re()
{
	if(( fpe=fopen ("emp.txt" ,"rb") ) != '\0')
	{

		fread(emp,sizeof(emp),1,fpe);
		fclose(fpe);
	}
	else
	{
	 strcpy(emp[1].name,"John Doe1");
	 strcpy(emp[1].passw,"PAS1");
	 strcpy(emp[2].name,"John Doe2");
	 strcpy(emp[2].passw,"PAS2");
	 strcpy(emp[3].name,"John Doe3");
	 strcpy(emp[3].passw,"PAS3");

		if(( fpe=fopen ("emp.txt" ,"wb") ) != '\0')
		{
			fwrite(emp,sizeof(emp),1,fpe);
			fclose(fpe);
		}
		else
		{
		printf("disk write error");
		exit(0);
		}
	}
}
/************** WRITE UPDATED EMP. RECORDS TO DISKETTE ****************/
void pool_we()
{
	open_window(10,20,40,4,f_yellow,b_black,32,b_red,f_red);
	cputs("      Please wait -- updating file.");

	if(( fpe=fopen ("emp.txt" ,"wb") ) != '\0')
	{
		fwrite(emp,sizeof(emp),1,fpe);
		fclose(fpe);
	}
	else
	printf("disk write error");
	close_window(0);
}
