/*
		THIS MODULE MAINTAINS AND DISPLAYS EMMPLOYEE INFORMATION
*/
#include<graph.h>
#include<stdio.h>

	struct  employee
	{
		char  name[21];
		char  passw[5];
	} emp[16];

	 FILE  *fp;
	int extern fcolor;
	int  extern hcolor;
/************* LIST EMPLOYEES ************************************/
list_emp()
{

	int extern emp_no,x,y;
	char extern emp_nos[3];
	emp_no=0;

	_clearscreen(_GCLEARSCREEN);
	_setbkcolor((long)fcolor);
	_settextcolor(hcolor);
	_settextposition(1,12);

	_outtext("旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커");
	_settextposition(2,12);

	_outtext("�           UPDATE EMPLOYEE RECORDS              �");
	_settextposition(3,12);

	_outtext("읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸");
	_setbkcolor(hcolor);
	_settextcolor(fcolor);

	x=7;        /*print row*/
	y=1;        /*array number*/
	_settextposition(5,17);
	_outtext("EMP. #  NAME                   PASSWORD");
loop2:
	_settextposition(x++,17);
	if(*emp[y].name>' ')         /* print all emp */
	{
	printf(" %2d  -  %-20s    %4s\r",y,emp[y].name,emp[y].passw);
	}
	y++;
	if(y < 16) goto loop2;
	++x;
	for(emp_no =0;emp_no==0 || emp_no>15; )    /* get emp to update */
	{
		_settextposition(x,15);
		_outtext("Enter number of employee to update or 99 to exit. 같 ");
		_settextposition(x,65);
		emp_nos[0]='\0';          /* use this field for temp storage */
		reads(2,emp_nos,0,1,0,0);
		emp_no = atoi(emp_nos);
		fflush(stdin);
		if (emp_no == 99) break;
	}

}
/********************* UPDATE EMPLOYEE RECORDS ******************/
update_emp()
{
	while(1)
	{
		list_emp();
		if(emp_no == 99) break;
		open_window(10,10,60,9,fcolor,(long)hcolor,205,fcolor,hcolor);
		_settextposition(2,2);
		printf("Name currently:  %-20s Password = %4s\n",\
				emp[emp_no].name,emp[emp_no].passw);
		_settextposition(4,2);
		_outtext("Enter name:  ");
		_settextcolor(hcolor);
		_setbkcolor((long)fcolor);
		_outtext("                    \r");
		_settextposition(4,15);
		_outtext(emp[emp_no].name);
		_settextposition(4,15);
		reads(20,emp[emp_no].name,0,1,0,0);
		_settextcolor(fcolor);
		_setbkcolor((long)hcolor);
		_settextposition(6,2);
		_outtext("Enter password:  ");
		_settextcolor(hcolor);
		_setbkcolor((long)fcolor);
		_outtext("    ");
		_settextposition(6,19);
		_outtext(emp[emp_no].passw);
		_settextposition(6,19);
		reads(4,emp[emp_no].passw,0,1,1,0);
		_settextcolor(fcolor);
		_setbkcolor((long)hcolor);
		close_window(0);

	}

}
/*************** READ EMPLOYEE RECORDS FROM DISKETTE *******/
pool_re()
{
	if(( fp=fopen ("a:\\emp.txt" ,"rb") ) != '\0')
	{

		fread(emp,sizeof(emp),1,fp);
		fclose(fp);
	}
	else
	{
	 strcpy(emp[1].name,"John Doe1");
	 strcpy(emp[1].passw,"PAS1");
	 strcpy(emp[2].name,"John Doe2");
	 strcpy(emp[2].passw,"PAS2");
	 strcpy(emp[3].name,"John Doe3");
	 strcpy(emp[3].passw,"PAS3");

		if(( fp=fopen ("a:\\emp.txt" ,"wb") ) != '\0')
		{

			fwrite(emp,sizeof(emp),1,fp);
			fclose(fp);

		}
		else
		{
		printf("disk write error");
		exit(0);
		}
	}
}
/************** WRITE UPDATED EMP. RECORDS TO DISKETTE ****************/
pool_we()
{
	open_window(10,15,40,4,fcolor,(long)hcolor,32,hcolor,fcolor);
	_outtext("      Please wait -- updating file.");

	if(( fp=fopen ("a:\\emp.txt" ,"wb") ) != '\0')
	{
		fwrite(emp,sizeof(emp),1,fp);
		fclose(fp);
	}
	else
	printf("disk write error");
	close_window(0);
}
