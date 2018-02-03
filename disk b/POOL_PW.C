/*
	THIS MODULE GETS AND VERIFIES PASS WORDS
*/

#include<conio.h>
#include<time.h>

	extern struct  employee
	{
		char  name[21];
		char  passw[5];
	} emp[16];
	struct emp_cash
	{
		int emp_no;
		int code;
		int table;
		time_t start;
		time_t stop;
		float amt;
	}e_cash[60];
	struct emp_cash *csh;
	float extern t_cost;
	int extern hcurr_emp;
/****************** GET EMPLOYEE PASSWORD **********************/
int extern fcolor;
int extern hcolor;
int extern f_black,f_yellow,b_black,b_yellow;



void pass_wd_e()
{
	int extern inv,curr_emp;
	char  extern emp_pw[5],mang_pw[5];
	inv = 0;
	open_window(16,15,54,5,f_yellow,hcolor,32,b_black,f_black);
	gotoxy(1,2);
	cputs("          Enter employee password 같같.");
	gotoxy(35,2);
	emp_pw[0]='\0';
	reads(4,emp_pw,0,0,1,0);
	inv = 1;
	if(emp_pw[0] !='\0')
	{
		for (curr_emp=1;curr_emp<16;curr_emp++)
			  {
				  if( !strcmp(emp_pw ,emp[curr_emp].passw ))
				  {
					 inv = 0;
					 break;
				  }
			  }
	}
/*---------------- maintain cash record --------------------------*/

	 while(inv==0 && curr_emp != hcurr_emp)
	{
		sign_out();             /* close any open cash record */
		csh->emp_no = curr_emp;   /* create new cash record */
		time(&(csh)->start);
		csh->amt=0;
		break;
	}

	close_window(0);
}
/*************** GET EMPLOYER PASSWORD *************************/
void pass_wd_m()
	{
		int extern inv;
		char extern mang_pw[5];
		inv=0;

		open_window(17,15,54,5,f_yellow,hcolor,32,b_black,f_black);
		gotoxy(1,2);
		cputs("            Enter employer password 같같.");
		gotoxy(37,2);
		mang_pw[0]='\0';
		reads(4,mang_pw,0,0,1,0);
		if (strcmp(mang_pw,"MANG"))
			inv = 1;
		close_window(0);

	}

/********** sign_out cash record when leaving rental menu **********/
sign_out()
{
	csh = e_cash;
	while(csh->emp_no > 0)
	{
		if(csh->stop == 0)
		time(&csh->stop);     /* close any open cash record */
		++csh;
	}
return 0;
}
/**************** update cash ****************************************/
update_cash()
{
	csh = e_cash;
	while(csh->stop > 0)
		++csh;
	csh->amt += t_cost;
return 0;
}
