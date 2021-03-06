/*
	THIS MODULE PROCESSES THE RENTAL MENU - PAGE 2
*/
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

	int extern b_red,b_black,b_yellow,b_white,b_grey,b_cyan,b_blue,b_bwhite;
	int extern b_green,b_lblue,b_lcyan,b_lmagenta,b_lgreen,b_lred,b_brown;
	int extern f_red,f_black,f_yellow,f_white,f_grey,f_cyan,f_blue,f_bwhite;
	int extern f_green,f_lblue,f_lcyan,f_lmagenta,f_lgreen,f_lred,f_brown;


	int extern hcust,ex_sw;;
	int extern tb_no,x,n_players,count_lines;
	int extern change,page2;
	long  extern *hindex;

	int  extern fcolor;
	float extern uncollected;
	char extern far *pdest;
	char extern tb_nos[3],s_players[3];

	char extern F1[3];           /*   table   */
	char extern F2[9];           /*   start   */
	char extern F3[9];           /*   stop    */
	char extern F4[11];          /*   used    */
	char extern F5[3];           /*   # of players */
	char extern F6[6];           /*   rate    */
	char extern F7[10];          /*   total cost (line) */
	char extern F8[7];           /*   per player cost (line)  */
	char extern F9[14];          /*   trans   */
	char extern F10[10];         /*   total cost */
	char extern F11[10];         /*   per player cost (total) */

	long extern idx[51];        /* MEMORY AREA INDEX ARRAY */
	long extern  *index;     /* INDEX POINTER */

	long extern histr[21];         /* MEMORY AREA HISTORY ARRAY */
	long extern *hist ;     /* HISTORY POINTER */

	long extern *next_avail;
	int extern  hcolor;
	int extern grp;
	int extern curr_emp;
	int extern bypass;
	char extern buf[80];

	extern struct tm *today;
	char extern ampm[];
	extern struct rental           /* MEMORY AREA RECORD LAYOUT ARRAY*/
	{
		int cust;
		int table;
		int no_ply;
		float rate;
		int employee;
		int trans;
		time_t start;
		time_t stop ;
		long *prev;
		char freeze;
		int new_table;
	}rental_s;
	extern struct  rental *rent;   /* RENTAL RECORD POINTER */

	extern struct  employee
	{
		char  name[21];
		char  passw[5];
	} emp[16];

	extern struct emp_cash
	{
		int emp_no;
		int code;
		int table;
		time_t start;
		time_t stop;
		float amt;
	}e_cash[15];
	extern struct emp_cash *csh;
	struct emp_cash *h_csh;
	extern struct rate_rec           /******* rate table record **********/
	{
		int  from:8;
		int  to:8;
		int  day_of_week;
		long r_start;
		long r_stop;
		float rate[6];
	}rate_tab[100] ;
	extern struct rate_rec *tab;      /* pointer to rate records */
	extern struct rate_rec *h_tab;

	extern struct bits
		{
		unsigned on:1;
		}bit_tab[51];
	 time_t cnv_tm;
	 int curr_time,clear_sw;
	 struct tm *today2;
	 int extern emp_sw[51];

/**************** start employee ( selected 5 ) *************************/
pool_emp()
{
	char err_buff[80];
	strcpy(buf," IDENTIFY TABLE EMPLOYEES ARE PLAYING ON");
	get_table_no();
	if(tb_no>0)
	{
		index = idx;        /* load record */
		for (x=tb_no;x>1;index++,x--);
		emp_sw[tb_no] = 1;
		if (*index != 0L)
		{
			(long)rent = *index;
			if(rent->stop  <1)      /* if tab open */
				emp_sw[tb_no] = 2;
		}
		open_window(10,10,50,10,fcolor,hcolor,205,fcolor,hcolor);
		sprintf(err_buff,"\n\r\n\r	   Be sure to add employees to table %2d\n\r",tb_no);
		cputs(err_buff);
		cputs("       after exiting this selection.\n\r\n\r");
		cputs("        Press any key to continue.");
		getch();
	}
	fflush( stdin );
	close_window(0);
return 0;
}
/****************** tine credit **********************************/
pool_cr()
{
	strcpy(buf,"ISSUE CREDIT");
	get_table_no();
	if(!tb_no) return(0);
	index = idx;                       /* reset index position to 1st area */
	for( x=tb_no ;  x>1; index++,x--); /*point index to relative table */
	if(*index ==0L) { err_msg(3); return(0); } /* check if table has been used */
	(long)rent=*index;

	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}  /* has table # been changed -yes retn*/
	if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/
	if (rent->stop > 0L){err_msg(3); return(0);} /* if clocked out  return */
	page2=1;
	review();
	page2=0;
	yn_mesg("Do you want to enter a credit for this table ?");
	if(ex_sw) return(0);
	get_cr_min();
	review();
return 0;
}
get_cr_min()
{
	float extern credit[51];
	char s_cr[10];
	float  conv;
	_setcursortype	(_NORMALCURSOR);   /* set cursor to norm */
	open_window(14,12,50,8,fcolor,hcolor,205,fcolor,hcolor);
	cputs("\n\r   Enter total amount of credit. \n\r");
	gotoxy(1,4);
	cputs(" NOTE: To reverse a previous credit preceed\n\r");
	cputs("       amount with a minus sign. Ex: -3.50.");
	gotoxy(34,2);
	s_cr[0]='\0';
	reads(9,s_cr,0,1,0,1);
	close_window(0);
	_setcursortype(_NOCURSOR);   /* set cursor off */
	conv = atof(s_cr);
	sprintf(s_cr,"%3.2f",conv);
	credit[tb_no] += atof(s_cr);
return 0;
}
/*********** CLEAR TABLE FROM CASH RECEIPTS (selected 1)*******************/
pool_clr()
{
	
	float extern t_cost;
	int x =0,reverse_sw;
	float h_t_cost;
	strcpy(buf,"CLEAR TABLE FROM CASH RECEIPTS");
	get_table_no();
	if(!tb_no) return(0);
	index = idx;                       /* reset index position to 1st area */
	for( x=tb_no ;  x>1; index++,x--); /*point index to relative table */
	if(*index ==0L) { err_msg(3); return(0); } /* check if table has been used */
	(long)rent=*index;
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}  /* has table # been changed -yes retn*/
	if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/
	page2=1;
	review();
	page2=0;
	yn_mesg("Do you want to clear the receipt for this customer ?");
	if( ex_sw)  return(0);

	reverse_sw =0;
	if(!rent->stop > 0)
	{
		time(&rent->stop);
		bypass=0;
		review();
		bypass =1;
		bit_tab[tb_no].on=0;
	}
	else reverse_sw =1;
	bypass=0;
	review();
	bypass =1;
	if(reverse_sw)
	{
		h_t_cost = t_cost;
		t_cost -= (t_cost *2);  /*change to negitive number */
		update_cash();
		t_cost = h_t_cost;
	}
	h_csh = csh;
	for(csh =e_cash;csh->emp_no>0;csh++);
	csh->stop=rent->stop;
	csh->emp_no = rent->employee;
	csh->code =2;
	(long)rent=*index;
	csh->amt = t_cost;
	get_cue_amt(2);  /* delete all cue sticks */
	while(1)
	{
		csh->start=rent->start;
		rent->freeze ='2';
		csh->table = rent->table;
		if (rent->prev >0L)         /* curr cust have previous record */
		{
			(long)rent = (long)rent->prev;
			if (rent->cust == hcust)
				continue;
		}
		break;
	}
	(long)rent=*index;
	csh =  h_csh;
	strcpy(buf,"TABLE CLEARED FROM CASH RECEIPTS");

	review();          /*      print detail */

return 0;
}
tm_err2()
{
	cputs("\r Invalid time entered,    \n\r");
	cputs("   press any key to continue.\r ");
	 getch();
	fflush( stdin );
	gotoxy(8,3);
	cputs("\r                           \n\r");
	cputs("                             \r ");
	gotoxy(8,3);
	buf[0]='\0';
return 0;
}


/************* change start time *****************************/
pool_str()
{
	int mo_end[]= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int x =0,h_hr,h_mn;
	int r_row,col_no,h_r_start;
	time_t new_start;
	int extern chng_cue_start;
	while(!chng_cue_start)
	{
		strcpy(buf,"MANUALLY CHANGE START TIME");
		get_table_no();
		if(!tb_no) return(0);
		index = idx;                       /* reset index position to 1st area */
		for( x=tb_no ;  x>1; index++,x--); /*point index to relative table */
		if(*index ==0L) { err_msg(3); return(0); } /* check if table has been used */
		(long)rent=*index;
		if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}  /* has table # been changed -yes retn*/
		if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/

		if(rent->stop > 0) { err_msg(5); return(0); } /* error table closed */
		page2=1;
		review();
		page2=0;
		yn_mesg("Do you want to change the start time for this table ?");
		if(ex_sw) return(0);
		hcust = rent->cust;
		while(1)
		{
			if (rent->prev >0L)         /* curr cust have previous record */
			{
				(long)rent = (long)rent->prev;
				if (rent->cust == hcust)
				{
					*++hist = (long)rent;    /*yes - put addr in history array */
					continue;               /* loop */
				}
				else
				{
					(long)rent = *hist;  /* prev record not same cust no */
					break;
				}
			}
			break;
		}
	break;
	}
			/*------------- get new start time --------------------*/
	if(chng_cue_start)
	open_window(17,22,40,6,f_black,b_white,205,b_lcyan,f_black);
	else
	open_window(10,20,40,6,fcolor,hcolor,32,hcolor,fcolor);
	cputs("\n\r  Enter the correct start time.\n\r");
	 r_row = 3; col_no =8;
	 while(1)
	 {
		r_row = 3; col_no =8;
		buf[0]='\0';
		_setcursortype(_NORMALCURSOR);   /* set cursor to norm */
		if(get_times(&buf,&h_hr,&h_mn, &r_row,&col_no,1,tm_err2)) break;
		_setcursortype(_NOCURSOR);   /* set cursor off */
		buf[2]=':';
		if(h_hr==24) h_hr=0;         /* if 2400 change to 00?? */
		h_r_start = (int)h_hr*100;   /* store new time */
		h_r_start += (int)h_mn;
		time(&cnv_tm);   /* get current (present) time */
		today2 = localtime(&cnv_tm);   /* convert to structure tm */
		curr_time = today2->tm_hour *100;  /* store present time */
		curr_time += today2->tm_min;
		/*----------- update structure tm with new time ------------*/
		today2->tm_sec = 0;        /* seconds */
		today2->tm_min = h_mn;     /* minuets */
		today2->tm_hour = h_hr;    /* hours */
		if(h_r_start > curr_time)     /* if true, previous days time */
		{
			if(today->tm_wday == 0)    today->tm_wday = 6;    /* week day */
				else  today->tm_wday -= 1;
			if(today->tm_yday == 0)    today->tm_yday = 365;  /* day of the yr*/
				else  today->tm_yday -= 1;
			while(1)
			{
				today->tm_mday -= 1;             /* day of month */
				if(today->tm_mday > 0)  break;
				if(today->tm_mon == 0) { today->tm_mon =11; today->tm_year -=1;}
					else  today->tm_mon -=1;     /* month */
				today->tm_mday = mo_end[today->tm_mon];
				break;
			}
		}

		get_cue_amt(3);  /*locate cue stick record */
		if((count_lines)&&(!chng_cue_start))
		{
			open_window(10,10,51,6,f_bwhite,b_black,206,b_black,f_brown);
			cputs("\n\r Be sure to change start time for cue sticks !!\n\r");
			cputs(" Press any key to continue.");
			getch();
			fflush(stdin);
			close_window(0);
		}
		new_start = mktime(today2);   /* convert structure to type time_t */

		/************* update employee memo *********************************/
		while(!chng_cue_start)
		{
			h_csh = csh;         /* STORE CSH POINTER */
			for(csh =e_cash;csh->emp_no>0;csh++); /* point to next blank csh record*/
			csh->stop=rent->start;
			csh->start=new_start;
			csh->emp_no = rent->employee;
			csh->code =3;
			csh->table = rent->table;
			csh->amt =0;
			csh = h_csh;
			rent->start = new_start;
			(long)rent = *index;
			strcpy(buf,"START TIME HAS BEEN MANUALLY CHANGED");
			review();
			break;
		}
			break;
	}
	close_window(0);
	return(0);
}
