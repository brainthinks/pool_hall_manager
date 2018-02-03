#include<time.h>
#include<graph.h>
#include<stdio.h>

	time_t curr_t;
	int hcust,line,amt_sw,no_tot=0,autosw,pwsw=0;
	int tb_no,x,n_players,n_emp;
	int change;
	time_t hstart;
	long *hindex;
	float t_cost;
	int extern fcolor,page2,ex_sw;
	float extern uncollected;
	char far *pdest;
	char tb_nos[3],s_players[3],s_emp[3];
	int view_sw;
	char F1[3];           /*   table   */
	char F2[9];           /*   start   */
	char F3[9];           /*   stop    */
	char F4[11];          /*   used    */
	char F5[3];           /*   # of players */
	char F6[6];           /*   rate    */
	char F7[10];          /*   total cost (line) */
	char F8[7];           /*   per player cost (line)  */
	char F9[14];          /*   trans   */
	char F10[9];         /*   total cost */
	char F11[10];         /*   per player cost (total) */
	char F15[2];          /*  no of emp players */
	char F16[9];          /* credit amt */
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
	char extern buf[80];
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
	} emp[16];

	int extern ch_p_sw;
	float extern credit[51];
	int cr_min_sw =0;
	char err_buf[80];


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
	for( x=tb_no ;  x>1; index++,x--);   /* point index to relative table */
	if(*index > 0)                    /* if table already clocked in,     */
	{                                 /*   then clock it out. */
		(long)rent = *index;
		if (rent->stop < 1L )         /* CLOCKING TABLE OUT */
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
				yn_mesg("Do you want to clock this table out ?");
				if( ex_sw)  return(0);
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
	(long)rent->prev = *index;          /* if not 1st then update previous field */
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
  /*  review();                print detail */
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
	rent->trans = 7;         /* 1 = credit record */
	rent->employee = curr_emp;
	++rent;           /* incrememt rent pointer */
	(long)next_avail=(long)rent;
	(long)rent->prev = *index;    /* if not 1st then update previous field */
	*index = (long)rent;          /* update index pointer */
}
update_cr()
{
	tb_no = 1;
	while(tb_no++ <50)
	{
		if(! credit[tb_no] > 0) continue;
		index = idx;                      /* reset index position to 1st area */
		for( x=tb_no ;  x>1; index++,x--);   /* point index to relative table */
		(long)rent = *index;
		grp = rent->cust;
		curr_emp = rent->employee;
		(long)rent=(long)next_avail;    /* set rec ptr to next blank */
		(long)rent->prev = *index;      /* update previous ptr */
		credit_rec();
	}
}

/************* CHANGE NUMBER OF PLAYERS (selected 2) *********************/
pool_udp()
{
	int hgrp;
	strcpy(buf,"CHANGE NUMBER OF PLAYERS ON TABLE");
	get_table_no();
	if(!tb_no) return(0);
	index = idx;
	for (x=tb_no;x>1;index++,x--);
	if (*index < 1L) {  err_msg(3); return(0);  }
	(long)rent = *index;
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}  /* has table # been changed -yes retn*/
	if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/
	if (rent->stop > 0L){err_msg(3); return(0);} /* if clocked out  return */
	auto_rate_adj();

	page2=1;
	review();
	page2=0;
	yn_mesg("Do you want to change the # of players for this table ?");
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
	(long)rent->prev = *index;          /* if not 1st then update previous field */
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
	if(*index < 1L) { err_msg(3); return(0); } /* check if table has been used */
			/* has table # been changed -yes retn*/
	(long)rent=*index;
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}
	auto_rate_adj();

	view_sw = 1;
	review();
	view_sw = 0;

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
	for( x=tb_no ;  x>1; index++,x--);   /*point index to relative table */
	if(*index <1L) { err_msg(3); return(0); } /* Is there a table at index location */
	(long)rent = *index;

	if (rent->stop < 1L ) { err_msg(8); return(0);}  /* is table clocked out - no return*/
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}  /* has table # been changed -yes retn*/
	if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/
	if(!change)
	{

		page2=1;
		review();
		page2=0;
		yn_mesg("Do you want to restart this table ?");
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
			open_window(12,10,41,9,fcolor,(long)hcolor,205,fcolor,hcolor);
			_outtext("\n  1. Restart with current time ?\n\n");
			_outtext("  2. Restart with previous stop time ?\n\n");
			_settextcolor(fcolor+8);
			_outtext("     Enter selection number");
			_settextcolor(fcolor);
			rs_ans = getch();
			close_window(0);
		}
		if(rs_ans == '1')
			time(&hstart);
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
	for (x=tb_no;x>1;index++,x--);  /* increment index by old table # */
	if (*index < 1L){err_msg(3); return(0);} /* if no table at index addr - return */
	(long)rent = *index;            /* activate rental record */
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}  /* has table # been changed -yes retn*/
	if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/

	if (rent->stop > 0L) {err_msg(3); return(0);} /* if clocked out  return */
	auto_rate_adj();

	page2=1;
	review();
	page2=0;
	yn_mesg("Do you want to move this customer to a new table ?");
	if( ex_sw)  return(0);


	hindex = index;                 /* store index pointer of old table */
	hgrp = rent->cust;              /* store cust # of old table */
	n_players = rent->no_ply;       /* store no players in old tab */
	hno_emp =  rent->no_emp;
	get_new_tab_no();               /* get new table # */
	if(tb_no == htb_no) {err_msg(7); return(0);}  /* if new tab # = to old tab # - return*/

	index = idx;                    /* point index to first table record */
	for (x=tb_no;x>1;index++,x--);  /* increment index by new table # */
	if (*index > 0L)                /* if table at index addr -  */
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
			for (x=tb_no;x>1;index++,x--);
			(long)rent = *index;
			auto_rate_adj();
		}
	}
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
	_settextcursor(0x0607);   /* set cursor to normal */
	while(1)
	{
	_settextposition(23,52);      /* turn off generated cursor */
	_outtext(" ");
		open_window(11,13,55,7,fcolor,(long)hcolor,32,hcolor,fcolor);
		_settextposition(2,(54 - strlen(buf)) / 2);
		_outtext(buf);
		_settextposition(4,1);
		_settextcolor(fcolor+8);
		_outtext("               Enter table number. ");
		_settextcolor(fcolor);
		open_window(4,6,67,3,fcolor,(long)hcolor,196,fcolor,hcolor);
		_outtext("If you have made the wrong selection press return or enter key.");
		_settextwindow(12,12,16,66);
		_settextposition(4,38);
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

}

/***************** get new table # when changed ********************/
get_new_tab_no()
{
	int ok_sw;
	_settextcursor(0x0607);   /* set cursor to normal */
	while(1)
	{
		open_window(16,25,30,5,fcolor,(long)hcolor,32,hcolor,fcolor);
		_settextposition(2,1);
		_settextcolor(fcolor+8);
		_outtext(" Enter new table number    .");
		_settextcolor(fcolor);
		_settextposition(2,25);
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
}

/******************* GET NUMBER OF PLAYERS **********************/
get_no_players()
{
	_settextcursor(0x0607);   /* set cursor to normal */
	while(1)                      /* GET NUMBER OF PLAYERS */
	{

		open_window(16,24,32,5,fcolor,(long)hcolor,32,hcolor,fcolor);
		_settextposition(2,1);
		_settextcolor(fcolor+8);
		_outtext(" Enter number of players    .");
		_settextcolor(fcolor);
		_settextposition(2,26);
		s_players[0]='\0';
		reads(2,s_players,0,1,0,0);

		n_players = atoi(s_players);
		if(n_players  > 0 && n_players  < 7) /* CHECK FOR VALID PLYRS # */
			break;
		err_msg(2);
	}
}
/******************* GET NUMBER OF EMP PLAYERS **********************/
get_no_emp()

{
	_settextcursor(0x0607);   /* set cursor to normal */

	while(1)                      /* GET NUMBER OF PLAYERS */
	{
		open_window(16,24,50,5,fcolor,(long)hcolor,32,hcolor,fcolor);
		_settextposition(2,1);
		_settextcolor(fcolor+8);
		_outtext(" Enter number of players that are employees.");
		_settextcolor(fcolor);
		_settextposition(2,47);
		s_emp[0]='\0';
		reads(2,s_emp,0,1,0,0);
		n_emp = atoi(s_emp);
		if(n_emp > n_players){ err_msg(12); continue; }
		if( n_emp  < 7) /* CHECK FOR VALID PLYRS # */
			break;
		err_msg(2);
	}
}


/******************** print rental record ************************/
review()
{
	int center;
	char hFs[8];

	hist = histr;
	*hist = (long)rent;
	hcust = rent->cust;

	line = 6;          /* print line no. of first detail line */
	/******** read back thru array for first record of current customer *****/
	_settextcursor(0x2000);   /* set cursor to full */
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
		_clearscreen(_GCLEARSCREEN);
		center =  (80 - (strlen(buf)+3)  )/2;    /* print report title */
		_settextposition(0,center);
		_settextcolor(fcolor+24);
		_outtext("-> ");
		_settextcolor(fcolor);
		_outtext(buf);
	}
	if(bypass)
		prt_layout();
	t_cost =0;
	while(1)
	{
		(long)rent = *hist;     /* set rental pointer 1st of group */

		prt_detail();           /* go to print detail */
		tb_no=rent->table;
		if ((long)hist == (long)&histr)       /* has last record of set been printed */
			break;
		--hist;                 /* no decrement history poinnter */
		line += 1;
		if(line>17)
		{
			line=17;
			if(view_sw)
			{
				open_window(20,2,22,4,fcolor,(long)hcolor,205,fcolor,hcolor);
				_settextcolor(fcolor+8);
				_outtext(" Press any key\n");
				_outtext(" to view next line.");
				getch();
				fflush( stdin );
				_settextcolor(fcolor);
				close_window(0);
			}

			_settextwindow(6,3,17,77);
			_scrolltextwindow(1);
			_settextposition( 17,5 ); printf ("�");
			_settextposition( 17,13 ); printf ("�");
			_settextposition( 17,21 ); printf ("�");
			_settextposition( 17,35 ); printf ("�");
			_settextposition( 17,39 ); printf ("�");
			_settextposition( 17,46 ); printf ("�");
			_settextposition( 17,55 ); printf ("�");
			_settextposition( 17,63 ); printf ("�");
			_settextposition( 17,74 ); printf ("�");
			_settextwindow(1,1,25,80);
		}
	}
	compute_tots();
	if(bypass)
	{
		if(credit[tb_no])
		{
			_settextcolor(hcolor);
			_setbkcolor((long)fcolor);
			_settextposition( 19,12 );
			_outtext("Credit");
			_settextcolor(fcolor);
			_setbkcolor((long)hcolor);
			sprintf(F16,"%4.2f",credit[tb_no] );
			sprintf(hFs,"%7s",F16);
			_settextposition( 19,18 );
			_outtext(hFs);
		}
		if(rent->freeze =='2')
		{
			_settextcolor(hcolor);
			_setbkcolor((long)fcolor);
			_settextposition( 20,2 );
			_outtext("Cleared cash receipts.");
			_settextcolor(fcolor);
			_setbkcolor((long)hcolor);

		}
		else {
			if(!no_tot)
			{
				_settextposition( 20,18 );
				sprintf(hFs,"%7s",F10);
				_outtext(hFs);
			}
		}
		if(emp_sw[tb_no])
		{
			_settextcolor(hcolor);
			_setbkcolor((long)fcolor);
			_settextposition( 20,28 );
			_outtext(" Employee rate in effect. ");
			_settextcolor(fcolor);
			_setbkcolor((long)hcolor);
		}
		_settextposition( 20,71 ); printf (F11);
		_settextposition( 23,0 );

		if(!page2)
		 {
			_settextcolor(fcolor+8);
			if(amt_sw)
				_outtext("     Collect amount due, then press any key to continue. ");
			else
				printf("                  Press any key to continue. ");
			_settextcolor(fcolor);
			getch();
			fflush( stdin );
		}
	}
}
/************* compute and format final totals ******************/
compute_tots()
{
	if(credit[tb_no])
		t_cost-= credit[tb_no];
	if(!bypass)
		uncollected+=t_cost;
	sprintf(F10,"%4.2f",t_cost);          /* format line cost */
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

		default: return(0);
	}
	open_window(3,((80-strlen(err_buf))/2),\
					strlen(err_buf)+4,    5,fcolor,\
					(long)hcolor,32,hcolor,fcolor);
	_settextposition(1,((strlen(err_buf)+4)- (strlen("E R R O R  !!")))/2);
	_outtext("E R R O R  !!");
	_settextposition(2,2);
	_outtext(err_buf);
	_settextposition(3,2);
	_outtext(press_any);
	getch();
	fflush( stdin );
	close_window(0);
}
