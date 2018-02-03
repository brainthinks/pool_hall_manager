#include<time.h>
#include<conio.h>
#include<stdio.h>
	int extern b_red,b_black,b_yellow,b_white,b_grey,b_cyan,b_blue,b_bwhite;
	int extern b_green,b_lblue,b_lcyan,b_lmagenta,b_lgreen,b_lred;
	int extern f_red,f_black,f_yellow,f_white,f_grey,f_cyan,f_blue,f_bwhite;
	int extern f_green,f_lblue,f_lcyan,f_lmagenta,f_lgreen,f_lred,f_brown;
	int extern mono,count_lines;
	time_t curr_t;
	int hcust,line,amt_sw,no_tot=0,autosw,pwsw=0;
	int tb_no,xx,n_players,n_emp;
	int change;
	time_t hstart;
	long *hindex;
	float t_cost;
	int extern fcolor,page2,ex_sw,ctl_key;
	float extern uncollected,tot_cue_amt;
	char far *pdest;
	char tb_nos[3],s_players[3],s_emp[3];
	int view_sw;
	char F1[3];           /*   table   */
	char F2[9];           /*   start   */
	char F3[9];           /*   stop    */
	char F4[12];          /*   used    */
	char F5[3];           /*   # of players */
	char F6[6];           /*   rate    */
	char F7[10];          /*   total cost (line) */
	char F8[7];           /*   per player cost (line)  */
	char F9[14];          /*   trans   */
	char F10[9];         /*   total cost */
	char F15[2];          /*  no of emp players */
	char F16[9];          /* credit amt */
	char F11[10];         /*  total cue amt */
	extern struct rate_rec           /******* rate table record **********/
	{
		int from;
		int to;
		int day_of_week;
		long r_start;
		long r_stop;
		float rate[6];
	}rate_tab[100] ;

	struct rate_rec *tab;      /* pointer to rate records */
	struct rate_rec *h_tab;
	extern struct  rental *rent;   /* RENTAL RECORD POINTER */

	long extern idx[51];        /* MEMORY AREA INDEX ARRAY */
	long extern  *index;     /* INDEX POINTER */

	long extern histr[21];         /* MEMORY AREA HISTORY ARRAY */
	long extern *hist ;     /* HISTORY POINTER */

	long extern *next_avail;
	int extern hcolor;
	int extern grp;
	int extern curr_emp;
	int extern bypass;
	char extern buf[80],S8[7];
	int extern emp_sw[51];
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
		int no_emp;
	}rental_s;
	extern struct bits
		{
		unsigned on:1;
		}bit_tab[51];

	extern struct  employee
	{
		char  name[21];
		char  passw[5];
	} emp[100];

	int extern ch_p_sw;
	float extern credit[51];
	int cr_min_sw =0;
	char err_buf[80],cue_buf[10];
	char cue_ctl;

/*********** AUTOMATICALY CHANGE RATES WHEN RATE TIME CHANGES*********/
auto_rate_adj()
{
	int c_day,start_day;
	int c_time,hr;
	while(1)
	{
		autosw =0;
		get_rate(&rent->start);   /* set pointer (tab) to original rate record */
		today = localtime(&rent->start);  /* convert rent start to timr structure */
		start_day = today->tm_wday; /* store start day - rent record */

		time(&curr_t);   /* get current time */
		today = localtime(&curr_t); /* convert current time to structure */
		c_day = today->tm_wday;   /* store curr day */
		c_time=(today->tm_hour*100)+today->tm_min;  /* time to 2400 clock */
		if(c_day == start_day)   /*compare curr day to rate day */
			if(c_time<=tab->r_stop )
				return(0);
		today = localtime(&rent->start);  /* convert rent start to timr structure */
		c_time = tab->r_stop;   /* move rate stop time to work area */
		for(hr=0;c_time>60;c_time-=100,hr++);   /* seperate hrs & min's */
		today->tm_sec =0;              /* set stop time to time structure */
		today->tm_min = c_time;        /*    to be converted to time_t(type)*/
		today->tm_hour=hr;             /*    variable */
		rent->stop = mktime(today);    /* close rental table */
		if(hr == 24)
		{
			curr_t = mktime(today);   /* curr_t will = 12:00am next day */
			autosw = 1;
		}
		change =1;           /* change switch on */
		pool_restart();      /* restart table */
		(long)rent=*index;   /* set pointer to restarted record */
		rent->trans = 7;
		change =0;           /* change switch off */
	}
}

/*-------- START PROCESSING CLOCK IN/OUT (selected 1 ) -------------------*/
pool_cio()
{
	strcpy(buf,"CLOCKING TABLE IN OR OUT");
	if(!change) get_table_no();
	if(!tb_no) return(0);
	index = idx;                      /* reset index position to 1st area */
	for( xx=tb_no ;  xx>1; index++,xx--);   /* point index to relative table */
	if(*index != 0)                    /* if table already clocked in,     */
	{                                 /*   then clock it out. */
		(long)rent = *index;
		if (rent->stop ==0 )         /* CLOCKING TABLE OUT */
		{
			if(pwsw)
			{
				auto_rate_adj();
				change =1;
			}
			if(!change)
			{
				page2=1;
				no_tot=1;
				review();
				no_tot=0;
				page2=0;
				yn_mesg(" Do you want to clock this table out ? ");
				if( ex_sw)  return(0);
				close_cues();
			}

			time(&rent->stop);
			bit_tab[tb_no].on=0;
			amt_sw=1;
			if(!change)
			{
				strcpy(buf,"THIS CUSTOMER IS NOW CLOCKED OUT.");
				review();
			}
			amt_sw =0;
			if(!change && rent->freeze !='1') update_cash();
			return(0);
		}
	}
/*_____________ if table not clocked out then clock in.__________ */
	get_no_players();                              /* GET NUMBER OF PLAYERS */
	sprintf(err_buf," Do you want to open table %2d with %1d player(s) ? ",tb_no,n_players);
	yn_mesg(err_buf);
	if( ex_sw)  return(0);
	(long)rent=(long)next_avail;
	(long)rent->prev = *index;   /* if not 1st then update previous field */
	*index = (long)rent;          /* update index pointer */
	if(emp_sw[tb_no]==2) emp_sw[tb_no]=0;
	if(emp_sw[tb_no]){ emp_sw[tb_no]=2;  get_no_emp(); }
	if(credit[tb_no])     /* if credit build credit record */
	{
		credit_rec();
		credit[tb_no] =0;
	}
	++grp;
	bit_tab[tb_no].on=1;
/*_____________ UPDATE RECORD FIELDS ADD _______________________*/
	time(&rent->start);
	rent->cust = grp;
	rent->table = tb_no;
	rent->no_ply = n_players;
	if(emp_sw[tb_no])
		rent->no_emp = n_emp;
	get_rate(&rent->start);
	rent->trans = 1;         /* 1 = clock on table */
	rent->employee = curr_emp;
	strcpy(buf,"THIS CUSTOMER IS NOW CLOCKED IN.");
  /*  review();            print detail - used for testing */
	++rent;           /* incrememt rent pointer */
	(long)next_avail=(long)rent;
	return(0);
}
/**************CREATE CREDIT RECORD AFTER TABLE COLSED ****************/
credit_rec()
{
	time(&rent->start);
	time(&rent->stop);
	rent->cust = grp;
	rent->table = tb_no;
	rent->no_ply = 0;
	rent->rate =  credit[tb_no];
	rent->trans = 7;         /* 7 = credit record */
	rent->employee = curr_emp;
	++rent;           /* incrememt rent pointer */
	(long)next_avail=(long)rent;
//	(long)rent->prev = *index;    /* if not 1st then update previous field */
	*index = (long)rent;          /* update index pointer */
return 0;
}
update_cr()                // called when exiting program
{
	tb_no = 0;
	while(tb_no++ <50)
	{
		if( credit[tb_no] == 0) continue;
		index = idx;                /* reset index position to 1st area */
		for( xx=tb_no ;  xx>1; index++,xx--);   /* point index to relative table */
		(long)rent = *index;
		grp = rent->cust;
		curr_emp = rent->employee;
		(long)rent=(long)next_avail;    /* set rec ptr to next blank */
		(long)rent->prev = *index;      /* update previous ptr */
		credit_rec();
	}
	return 0;
}
/******************* PROCESS_F1 ****************************/
process_f1()
{
	strcpy(buf,"REVIEW AND CHANGE CUE STICKS");
	get_table_no();
	if(!tb_no) return(0);
	index = idx;
	for (xx=tb_no;xx>1;index++,xx--);
	if (*index ==0) {  err_msg(3); return(0);  }
	(long)rent = *index;
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}  /* has table # been changed -yes retn*/
	if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/
	if (rent->stop > 0L){err_msg(3); return(0);} /* if clocked out  return */
	go_edit_cues();
    return 0;

}
/************* CHANGE NUMBER OF PLAYERS (selected 2) *********************/
pool_udp()
{
	int hgrp;
	strcpy(buf,"CHANGE NUMBER OF PLAYERS ON TABLE");
	get_table_no();
	if(!tb_no) return(0);
	index = idx;
	for (xx=tb_no;xx>1;index++,xx--);
	if (*index ==0) {  err_msg(3); return(0);  }
	(long)rent = *index;
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}  /* has table # been changed -yes retn*/
	if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/
	if (rent->stop > 0L){err_msg(3); return(0);} /* if clocked out  return */
	auto_rate_adj();

	page2=1;
	review();
	page2=0;
	yn_mesg(" Do you want to change the # of players for this table ? ");
if( ex_sw)  return(0);
	get_no_players();
	if(!emp_sw[tb_no])
		if (rent->no_ply == n_players) { err_msg(4); return(0); }
	time (&rent->stop);
	if(emp_sw[tb_no]) get_no_emp();
	if(ch_p_sw)
	{
	  rent->freeze = '3';
	  hstart = rent->start;
	}
	else
		hstart = rent->stop;

	hgrp = rent->cust;
	/*_____________ update record fields - player change ___________________*/
	(long)rent=(long)next_avail;
	(long)rent->prev = *index;   /* if not 1st then update previous field */
	*index = (long)rent;
	rent->start = hstart;
	rent->cust = hgrp;
	rent->table = tb_no;
	rent->no_ply = n_players;
	if(emp_sw[tb_no])
		rent->no_emp = n_emp;
	get_rate(&rent->start);
	if(ch_p_sw)
	{
	  rent->trans = 6;       /* correct # of players */
	}
	else  rent->trans = 2;      /* 2 = change # of players */
	rent->employee = curr_emp;
	strcpy(buf,"NUMBER OF PLAYERS CHANGED FOR THIS TABLE");
	review() ;
	++rent;
	(long)next_avail = (long)rent;
	return(0);
}

/*************** REVIEW RENTAL TABLE (selected 3) *********************/
pool_rev()
{
	int x =0;
	strcpy(buf,"REVIEW TABLE STATUS");
	get_table_no();
	if(!tb_no) return(0);
	index = idx;                       /* reset index position to 1st area */
	for( x=tb_no ;  x>1; index++,x--); /*point index to relative table */
	if(*index ==0) { err_msg(3); return(0); } /* check if table has been used */
			/* has table # been changed -yes retn*/
	(long)rent=*index;
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}
	auto_rate_adj();

	view_sw = 1;
	review();
	view_sw = 0;
return 0;
}
/********************* RESTART TABLE (selected 4) **********************/
pool_restart()
{
	int hcust,rs_ans;
	int htable;
	int hno_ply,hno_emp;
	float hrate;
	int hemployee;

	if(!change) { strcpy(buf,"RESTART TABLE"); get_table_no();}
	if(!tb_no) return(0);
	index = idx;                      /* reset index position to 1st area */
	for( xx=tb_no ;  xx>1; index++,xx--);   /*point index to relative table */
	if(*index ==0) { err_msg(3); return(0); } /* Is there a table at index location */
	(long)rent = *index;

	if (rent->stop < 1L ) { err_msg(8); return(0);}  /* is table clocked out - no return*/
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}  /* has table # been changed -yes retn*/
	if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/
	if(!change)
	{

		page2=1;
		review();
		page2=0;
		yn_mesg(" Do you want to restart this table ? ");
		if( ex_sw)  return(0);
		t_cost -= (t_cost *2);  /*change to negitive number */
		update_cash();

	}
	bit_tab[tb_no].on=1;
	hcust = rent->cust;
	htable = rent->table;
	hno_emp = rent->no_emp;
	hno_ply = rent->no_ply;
	hrate = rent->rate;
	if (autosw == 1)
		hstart = curr_t;
	else
		hstart = rent->stop;
	if(!change)
	{
		rs_ans = 0;
		while(rs_ans < '1' || rs_ans > '2')
		{
			open_window(12,10,41,9,fcolor,hcolor,205,fcolor,hcolor);
			cprintf("\n\r  1. Restart with current time ?\n\r\n\r");
			cprintf("  2. Restart with previous stop time ?\n\r\n\r");
			textcolor(fcolor+8);
			cputs("     Enter selection number");
			textcolor(fcolor);
			rs_ans = getch();
			close_window(0);
		}
		if(rs_ans == '1')
			time(&hstart);
			restart_cues(hstart,rent->stop);
	}

	(long)rent=(long)next_avail;
	(long)rent->prev = *index;
	*index = (long)rent;        /*   update index pointer */

/*_____________ UPDATE RECORD FIELDS RESTART _______________________*/
	rent->cust = hcust;
	rent->table = htable;
	rent->no_ply  = hno_ply;
	rent->no_emp = hno_emp;
	rent->rate = hrate;
	rent->employee = curr_emp;
	rent->trans = 4;
	rent->start = hstart;
	rent->stop = 0L;

	strcpy(buf,"THIS CUSTOMER IS NOW RE-STARTED.");
	if(!change)
		review();                /* print detail */
	++rent;           /* incrememt rent pointer */
	(long)next_avail=(long)rent;

	return(0);
}



/********************* CHANGE TABLE NUMBER (selected 5) *****************/
pool_tab()
{
	int htb_no,hgrp, hno_emp;
	strcpy(buf,"CHANGE TABLE NUMBER");
	get_table_no();
	if(!tb_no) return(0);
	htb_no = tb_no;

	index = idx;                    /* point index to first table record */
	for (xx=tb_no;xx>1;index++,xx--);  /* increment index by old table # */
	if (*index ==0){err_msg(3); return(0);} /* if no table at index addr - return */
	(long)rent = *index;            /* activate rental record */
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}  /* has table # been changed -yes retn*/
	if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/

	if (rent->stop > 0L) {err_msg(3); return(0);} /* if clocked out  return */
	auto_rate_adj();

	page2=1;
	review();
	page2=0;
	yn_mesg(" Do you want to move this customer to a new table ? ");
	if( ex_sw)  return(0);


	hindex = index;                 /* store index pointer of old table */
	hgrp = rent->cust;              /* store cust # of old table */
	n_players = rent->no_ply;       /* store no players in old tab */
	hno_emp =  rent->no_emp;
	get_new_tab_no();               /* get new table # */
	if(tb_no == htb_no) {err_msg(7); return(0);}  /* if new tab # = to old tab # - return*/

	index = idx;                    /* point index to first table record */
	for (xx=tb_no;xx>1;index++,xx--);  /* increment index by new table # */
	if (*index != 0L)                /* if table at index addr -  */
	{
		(long)rent = *index;        /*  yes - activate rental record */
		if (rent->stop <  1L) {err_msg(8); return(0);}    /* if not clocked out - return*/
	}
	(long)rent = *hindex;
	time(&rent->stop);
	hstart = rent->stop;
	rent->new_table=tb_no;
	bit_tab[rent->table].on=0;
	rent->freeze = '1';              /* code record so it cant be re-opened*/
	(long)rent = *index;
	bit_tab[tb_no].on = 1;

	(long)rent=(long)next_avail;    /* make new record available */
	(long)rent->prev = *hindex;     /* update previous with old record addr*/

	*index = (long)rent;            /* update index array */

	/*_____________ update record fields - table # change ___________________*/

	rent->start = hstart;
	rent->cust = hgrp;
	rent->table = tb_no;
	rent->no_ply = n_players;
	rent->no_emp = hno_emp;
	if(emp_sw[htb_no])
	{
		emp_sw[htb_no]=0;
		emp_sw[tb_no]=2;
	}
	get_rate(&rent->start);
	rent->trans = 3;         /* 1 = clock on table */
	rent->employee = curr_emp;
	credit[tb_no] = credit[htb_no];
	credit[htb_no] = 0;
	strcpy(buf,"THIS CUSTOMER MOVED TO THIS TABLE");
	review() ;
	++rent;
	(long)next_avail = (long)rent;
	return(0);
}

/********************* PASS WORD CHANGED (selected 6) *****************/
pw_changed()
{
	static int y;
	y=0;
	change =0;
	pwsw =1;
	while(y<50)
	{
		y=y+1;
		if(bit_tab[y].on)
		{
			tb_no=y;
			change=1;
			pool_cio();
			pool_restart();
			(long)rent=*index;   /* set pointer to restarted record */
			rent->trans=8;
		}
	}
	pwsw =0;
	change = 0;
return 0;
}



/********************** SUPPORT FUNCTIONS ********************************/
						   /*******/
						   /*******/
/**********check and change any rates where needed ***********************/
process_auto_rate()
{
	static int y;
	 y=0;
	while(y<50)
	{
		y=y+1;
		if(bit_tab[y].on)
		{
			tb_no=y;
			index = idx;
			for (xx=tb_no;xx>1;index++,xx--);
			(long)rent = *index;
			auto_rate_adj();
		}
	}
	return 0;
}

/****************** Get rate from rate table *************************/
get_rate(time_t *time)
{
	struct rate_rec *pointer;

	float rate;
	int start,c_day,h_from;
	pointer = 0;
	today = localtime(time);    /* convert start time to struct tm  */
	start = today->tm_hour;
	start = start * 100;
	start += today->tm_min;     /* start = start time 24hr clock */
	if(today->tm_wday == 0)
		c_day = 8;
	else
		c_day = today->tm_wday +1;
	tab = rate_tab;           /* set pointer to first record */
	while(1)
	{
		if(tb_no >= tab->from)       /* find schedule by table # */
			if(tb_no <= tab->to)
			{
				h_from = tab->from;
				h_tab = tab;
				break;
			}
		++tab;
	}
	while(pointer == 0) {           /* find time line */
		while(h_from== tab->from) {
			if(c_day == tab->day_of_week)
				if(start >= tab->r_start)
					if(start < tab->r_stop) {
						pointer = tab;
						break;
					}
					++tab;
		}
		if(pointer > 0) break;
		tab = h_tab;
		c_day = 1;     /* if no match use default */
	}
rent->rate=tab->rate[rent->no_ply-1];
return(0);

}
/***************** get table number from keyboard ********************/
get_table_no()
{
	int ok_sw;
	_setcursortype(_NORMALCURSOR);   /* set cursor to normal */
	while(1)
	{
	gotoxy(52,25);      /* turn off generated cursor */
	cputs(" ");
		open_window(13,13,55,7,f_black,b_white,32,b_black,f_black);
		gotoxy((54 - strlen(buf)) / 2,2);
		cputs(buf);
		gotoxy(1,4);
		if(mono==1)
		textcolor(fcolor+8);
		cputs("               Enter table number. --->");
		textcolor(fcolor);
		open_window(4,7,67,3,f_yellow,b_black,205,f_green,b_green);
		cputs(" If you have made the wrong selection press return or enter key.");
		window(12,16,66,20);
		gotoxy(43,2);
		textbackground(b_white);
		textcolor(f_black);
		tb_nos[0]='\0';
		reads(2,tb_nos,0,1,0,0);
		tb_no = atoi(tb_nos);
		close_window(0);
		if(tb_no ==0)break;
		if(tb_no > 50)   /* CHECK FOR VALID TABLE # */
		{
			err_msg(1);
			continue;
		}
		/*------------ check table no. against rate file --------*/
		tab=rate_tab;   /* set pointer to first record */
		ok_sw = 0;
		while(1)
		{
			if(tb_no>=tab->from)
				if(tb_no<=tab->to)
				{
					ok_sw =1;
					break;
				}
			++tab;
			if(tab->from < 1) break;
		}

		if(ok_sw)  break;
		err_msg(10);
	}
	return 0;
}

/***************** get new table # when changed ********************/
get_new_tab_no()
{
	int ok_sw;
	_setcursortype(_NORMALCURSOR);   /* set cursor to normal */
	while(1)
	{
		open_window(16,25,30,5,fcolor,hcolor,32,hcolor,fcolor);
		gotoxy(1,2);
		textcolor(fcolor+8);
		cputs(" Enter new table number    .");
		textcolor(fcolor);
		gotoxy(25,2);
		tb_nos[0]='\0';
		reads(2,tb_nos,0,1,0,0);
		tb_no = atoi(tb_nos);
		close_window(0);
		if(tb_no ==0)break;
		if(tb_no > 50)   /* CHECK FOR VALID TABLE # */
		{
			err_msg(1);
			continue;
		}
		/*------------ check table no. against rate file --------*/
		tab=rate_tab;   /* set pointer to first record */
		ok_sw = 0;
		while(1)
		{
			if(tb_no>=tab->from)
				if(tb_no<=tab->to)
				{
					ok_sw =1;
					break;
				}
			++tab;
			if(tab->from < 1) break;
		}
		if(ok_sw) break;
		err_msg(10);
	 }
	 return 0;
}

/******************* GET NUMBER OF PLAYERS **********************/
get_no_players()
{
	_setcursortype(_NORMALCURSOR);   /* set cursor to normal */
	while(1)                      /* GET NUMBER OF PLAYERS */
	{

		open_window(16,24,32,5,f_white,b_black,32,b_lcyan,f_lcyan);
		gotoxy(1,2);
		textcolor(fcolor+8);
		cputs(" Enter number of players    .");
		textcolor(fcolor);
		gotoxy(26,2);
		s_players[0]='\0';
		reads(2,s_players,0,1,0,0);

		n_players = atoi(s_players);
		if(n_players  > 0 && n_players  < 7) /* CHECK FOR VALID PLYRS # */
			break;
		err_msg(2);
	}
	return 0;
}
/******************* GET NUMBER OF EMP PLAYERS **********************/
get_no_emp()

{
	_setcursortype(_NORMALCURSOR);   /* set cursor to normal */

	while(1)                      /* GET NUMBER OF PLAYERS */
	{
		open_window(16,24,50,5,f_bwhite,b_black,32,b_green,f_green);
		gotoxy(1,2);
		if(mono)
			textcolor(fcolor+8);
		cputs(" Enter number of players that are employees.");
		if(mono)
		textcolor(fcolor);
		gotoxy(47,2);
		s_emp[0]='\0';
		reads(2,s_emp,0,1,0,0);
		n_emp = atoi(s_emp);
		if(n_emp > n_players){ err_msg(12); continue; }
		if( n_emp  < 7) /* CHECK FOR VALID PLYRS # */
			break;
		err_msg(2);
	}
	return 0;
}


/******************** print rental record ************************/
review()
{
	int center,x;
	char hFs[8];
while(1)
{
	hist = histr;
	*hist = (long)rent;
	hcust = rent->cust;

	line = 6;          /* print line no. of first detail line */
	/******** read back thru array for first record of current customer *****/
	_setcursortype(_SOLIDCURSOR);   /* set cursor to full */
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
	/*************** print customer records ****************/
	if(bypass)
	{
		close_window(1);
		textcolor(f_black);
		textbackground(b_white);
		clrscr();
		center =  (80 - (strlen(buf)+3)  )/2;    /* print report title */
		gotoxy(center,1);
		if(mono)
			textcolor(fcolor+BLINK);
		else
			textcolor(f_red+BLINK);
		cputs("-> ");
		textcolor(f_black);
		cputs(buf);
	}
	if(bypass)
		prt_layout();
	t_cost =0;

	while(1)
	{
		(long)rent = *hist;     /* set rental pointer 1st of group */

		prt_detail();           /* go to print detail */
		tb_no=rent->table;
		if ((long)hist == (long)&histr)  /* has last record of set been printed */
			break;
		--hist;                 /* no decrement history poinnter */
		line += 1;
		if((line>17) && (bypass) )     /* 17 */
		{
			line=17;
			if(view_sw)
			{
				open_window(20,2,22,4,fcolor,hcolor,205,fcolor,hcolor);
				textcolor(fcolor+8);
				cputs(" Press any key\n\r");
				cputs(" to view next line.");
				getch();
				fflush( stdin );
				textcolor(fcolor);
				close_window(0);
			}

			window(3,6,77,17);
			gotoxy(75,12);
			cprintf("\n\r");           /*scroll window */
			gotoxy( 5,12 );
			cprintf ("�");
			gotoxy( 13,12 );
			cprintf ("�");
			gotoxy( 21,12 );
			cprintf ("�");
			gotoxy( 35,12 ); cprintf ("�");
			gotoxy( 39,12 ); cprintf ("�");
			gotoxy( 46,12 ); cprintf ("�");
			gotoxy( 55,12 ); cprintf ("�");
			gotoxy( 63,12 ); cprintf ("�");
			gotoxy( 74,12 ); cprintf ("�");
			window(1,1,80,25);
		}
	}


	if(bypass)
	{
					 /* print table rental amt */
		sprintf(F10,"%4.2f",t_cost);          /* format line cost */
		gotoxy( 2,19 ); cputs ("Table rental      ");
		gotoxy( 21,19);
		sprintf(hFs,"%7s",F10);
		cputs(hFs);
	}
	get_cue_amt(0);
	compute_tots();

	if(bypass)
	{
		gotoxy( 2,20 ); cputs ("Cue stick rental  ");
		sprintf(F11,"%3.2f",tot_cue_amt);          /* format line cost */
		gotoxy((7-strlen(F11)+21),20);
		cputs( F11 );

		get_cue_amt(3);  /*locate cue stick record */
		if(count_lines)
		{
			gotoxy(30,20);
			textcolor(f_brown);
			cputs("Press the F1 key to review cue sticks.");
			textcolor(f_black);
		}
		gotoxy( 11,21 );
		cputs("Credits");

		if(credit[tb_no])
		{
			textcolor(b_black);
			textbackground(f_red);
			gotoxy( 11,21 );
			cputs("Credits");
			textcolor(f_black);
			textbackground(b_white);
			sprintf(F16,"%4.2f",credit[tb_no] );
			if(F16[0] =='-')
			{
				F16[0] = ' ';
			}
			else
			{
				for(x=7;x>=0;x--)
				{
					F16[x+1]=F16[x];

				}
				F16[0]='-';
			}
			sprintf(hFs,"%7s",F16);
			gotoxy( 21,21 );
			cputs(hFs);
		}
		if(rent->freeze =='2')
		{
			textcolor(b_yellow);
			textbackground(f_red);
			gotoxy( 2,22 );
			cputs("Cleared cash receipts.");
			textcolor(f_black);
			textbackground(b_white);

		}
		else {
			if(!no_tot)
			{
				gotoxy( 21,22 ); cputs("컴컴컴컴");
				gotoxy( 2,23 ); cputs ("TOTAL AMOUNT DUE $");
				gotoxy( 21,23 );
				sprintf(hFs,"%7s",F10);
				cputs(hFs);
			}
		}
		if(emp_sw[tb_no])
		{
			textcolor(b_black);
			textbackground(f_cyan);
			gotoxy( 32,23 );
			cputs(" Employee rate in effect. ");
			textcolor(f_black);
			textbackground(b_white);
		}

		gotoxy( 3,25 );

		if(!page2)
		{
			if(mono)
				textcolor(fcolor+8);
			else
			textcolor(f_lred);
			textbackground(b_black);
			if(amt_sw)
			{
				cputs(" Collect amount due, then press any key to continue. ");
				_setcursortype(_NOCURSOR);
				textcolor(f_blue+BLINK);
				textbackground(b_white);
				cputs("<컴컴�-");
//				gotoxy(60,24);
			}
			else
				printf("    Press any key to continue ");
			textcolor(fcolor);
			textbackground(hcolor);
			cue_buf[0]='\0';

			if( (cue_ctl= reads(1,cue_buf,1,0,0,0)) == ';')
			{
				go_edit_cues();
				continue;
			}
			_setcursortype(_SOLIDCURSOR);
			fflush( stdin );
			break;
		}
        break;
	}
	break;
}
return 0;
}
/************* compute and format final totals ******************/
compute_tots()
{
	t_cost += tot_cue_amt;
	if(credit[tb_no])
		t_cost-= credit[tb_no];
	if(!bypass)
		uncollected+=t_cost;
	sprintf(F10,"%4.2f",t_cost);          /* format line cost */
return 0;
}

/********************  PRINT ERROR MESSAGES *****************************/
err_msg(int err_cd,int table)
{
	char press_any[] = {"Press any key to continue."};

	switch (err_cd)
	{
		case 1:
		{
			strcpy(err_buf,"Invalid table number.  Must be 1 thru 50.");
			break;
		}
		case 2:
		{
			strcpy(err_buf,"Invalid number of players.  Must be 1 thru 6.");
			break;
		}
		case 3:
		{
			strcpy(err_buf,"This table has not been clocked in.");
			break;
		}
		case 4:
		{
			strcpy(err_buf,"This number of players allready clocked in.");
			break;
		}
		case 5:
		{
			strcpy(err_buf,"This table has been clocked out.");
			break;
		}
		case 6:
		{
			sprintf(err_buf,"Invalid table #.  This customer has been moved to table %2d.",table);
			break;
		}

		case 7:
		{
			strcpy(err_buf,"You have entered the same table number.");
			break;
		}
		case 8:
		{
			strcpy(err_buf,"The table you have entered is not clocked out.");
			break;
		}
		case 9:
		{
			strcpy(err_buf,"All tables must be clocked out before exiting.");
			break;
		}
		case 10:
		{
			strcpy(err_buf,"Invalid table #.  Not in rate table. Call manager and advise.");
			break;
		}
		case 11:
		{
			strcpy(err_buf,"Invalid table #.  Table has been cleared from cash receipts.");
			break;
		}
		case 12:
		{
			strcpy(err_buf,"Invalid # of employees, exceeds # of players.");
			break;
		}
		case 13:
		{
			sprintf(err_buf,"The cue stick you have entered is already rented on table %2d.",table);
			break;
		}
		case 14:
		{
			strcpy(err_buf,"The cue stick rate you have entered is incorrect, please re-enter.");
			break;
		}
		case 15:
		{
			strcpy(err_buf,"The cue stick line # must be listed below.");
			break;
		}
		case 16:
		{
			strcpy(err_buf,"Rental table clocked out, cue stick cannot be updated.");
			break;
		}
		case 17:
		{
			strcpy(err_buf,"Rental table not clocked out, cue stick stop time cannot be updated.");
			break;
		}
		case 18:
		{
			strcpy(err_buf,"There are no cue sticks rented for this table.");
			break;
		}

		default: return(0);
	}
	open_window(3,((80-strlen(err_buf))/2),\
					strlen(err_buf)+4,    5,f_yellow,\
					b_red,32,b_red,f_red);
	gotoxy(((strlen(err_buf)+4)- (strlen("E R R O R  !!")))/2,1);
	cputs("E R R O R  !!");
	gotoxy(2,2);
	cputs(err_buf);
	gotoxy(2,3);
	cputs(press_any);
	getch();
	fflush( stdin );
	close_window(0);
return 0;
}
