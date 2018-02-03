/*Dale & Debbie Grey, home -- 373-5570   business -- 645-3913*/
/*
	THIS MODULE RETREIVES AND MAINTAINS THE RATE SCHEDULES
*/


#include<graph.h>
#include<stdlib.h>
#include<stdio.h>
extern struct rate_rec           /******* work rate table record **********/
{
	int from;
	int to;
	int day_of_week;
	long r_start;
	long r_stop;
	float rate[6];
}rate_tab[100] ;

struct rate_rec2           /******* input rate table record **********/
{
	int from;
	int to;
	int day_of_week;
	long r_start;
	long r_stop;
	float rate[6];
}rate_tab2[100] ;
struct rate_rec3           /******* output rate table record **********/
{
	int from;
	int to;
	int day_of_week;
	long r_start;
	long r_stop;
	float rate[6];
}rate_tab3[100] ;

/******** hold area for print formated rate record **************/
struct prt_rate_line
{
	char p_day[3];
	char p_start[8];
	char p_stop[8];
	char p_1[6][6];

}prt;
struct rate_rec3 *tab3;      /* pointer to table records */
struct rate_rec3 *h_tab3;      /* pointer to table records */
struct rate_rec2 *tab2;      /* pointer to table records */
struct rate_rec *tab;      /* pointer to table records */
struct rate_rec *err_tab;   /* pointer to error table entry */
struct rate_rec *next_tab; /* pointer to next available blank record */
struct videoconfig video;

struct funct_ptrs
{
	int (*fld)();
}funct[9];
int e1();
int e2();
int e3();
int e4();
int e5();
int e6();
int e7();
int e8();
int e9();

int tm_err(int);

/******************** update rate table field functions **************/
char err_buf[80];
char day_of_week[3];
char buf[80];
int cur=0,err_cd,col_no,fld_no;
long h_hr,h_mn;
int first = 1;
int extern ex_sw;
int r_row,mono;
int extern fcolor;

int extern hcolor;
char start_tab[3];
char stop_tab[3];
int h_from;
int h_to;
int ctl_key,x,am,pm;
float h_rate;
int hld_playr,hld_col;
int ctl_sw =0;

/***************************MAIN FUNCTION ******************************/
read_rates()
{
	char c;
/************************************************************************/
	funct[0].fld = e1;     /* INITIALIZE FUNTION POINTERS FOR UPDATING FIELDS */
	funct[1].fld = e2;
	funct[2].fld = e3;
	funct[3].fld = e4;
	funct[4].fld = e5;
	funct[5].fld = e6;
	funct[6].fld = e7;
	funct[7].fld = e8;
	funct[8].fld = e9;
	tab = rate_tab;     /* initialize pointer to rate table */
	tab2=rate_tab2;
	next_tab = tab;     /* initialize pointer for next add */
	tab3 = rate_tab3;
	h_tab3 = tab3;
	h_from=0;
	h_to=0;

	_setbkcolor((long)hcolor);      /* set background color */
	_clearscreen(_GCLEARSCREEN);
	open_window(10,20,50,5,fcolor,(long)hcolor,205,fcolor,hcolor);
	_outtext("\n  Please wait -- retrieving FIRST rate schedule.");
	if(!data_in())     /* read rate table from disk */
	{
		first=0;
		close_window(0);
		h_from =  tab2->from;      /* store from/to in first record */
		h_to =  tab2->to;
		sprintf(start_tab,"%2d",tab2->from);
		sprintf(stop_tab,"%2d",tab2->to);
		memset(rate_tab,'\0',sizeof(rate_tab));
		/*--------- load tab with one complete table and print it ----*/
		while(1)
		{
			if(tab2->from==h_from && tab2->to==h_to)
			{
				memcpy(tab,tab2,sizeof(rate_tab[0]));
				++tab;++tab2;
			}
			else
				break;
		}
		tab=rate_tab;    /* set pointer next tab */
		for(next_tab = tab;next_tab->day_of_week >0;next_tab++);
		--next_tab;
		rate_lay();                    /* print rate screen layout */
		r_row = 1;
		ctl_key =0;
		reprint();                     /* print rate records */
		rate_msg("FIRST");

	   /*---------------------------------------------------------*/
	}
	else
	{
		/*--------- if none on disk, print instructions and ------*/
		/*--------  prepare to accept input                 ------*/
		close_window(0);
		rate_lay();                  /* print rate screen layout */
		default_mesg();
		close_window(1);
		rate_lay();
		get_tab_nos();
		rate_lay();                  /* print rate screen layout */
	}

	while(1)
	{
		_settextwindow(0,0,24,79);
		get_data();        /* get rate table data */
		if(ctl_sw != 3)       /* delete table, bypass save if 3 */
		{
			rate_sort();         /* sort work table records */
			save_data();         /* save work table to memory */
		}
		memset(rate_tab,'\0',sizeof(rate_tab));
		tab=rate_tab;    /* set pointer next tab */
		next_tab = tab;
		first =0;
		if(tab2->from ==0 && tab2->to==0)
		{
			first =1;
						 /* ask if above is ok */
			yn_mesg(" There are no additional rate schedules.  Do you want to enter another one ?\n" );
			if(ex_sw) break;    /* test for end of job */
			close_window(0);
			rate_lay();                  /* print rate screen layout */
			get_tab_nos();
			rate_lay();                  /* print rate screen layout */
		}
		else
		{
			h_from =  tab2->from;
			h_to =  tab2->to;
			sprintf(start_tab,"%2d",tab2->from);
			sprintf(stop_tab,"%2d",tab2->to);
			memset(rate_tab,'\0',sizeof(rate_tab));
			while(1)
			{
				if(tab2->from==h_from && tab2->to==h_to)
				{
					memcpy(tab,tab2,sizeof(rate_tab[0]));
					++tab;++tab2;
				}
				else
					break;
			}
			tab=rate_tab;    /* set pointer next tab */
			for(next_tab = tab;next_tab->day_of_week >0;next_tab++);
			--next_tab;

			rate_lay();                    /* print rate screen layout */
			r_row = 1;
			ctl_key =0;
			reprint();                     /* print rate records */
		   rate_msg("NEXT");
		}

	}
	open_window(10,10,44,3,fcolor,(long)hcolor,205,fcolor,hcolor);
	_outtext("  Please wait -- updating rate schedules.");

	data_out();          /* write all tables to disk */
	close_window(1);        /* end of job */
	_clearscreen(_GCLEARSCREEN);
	return(0);

}
rate_msg(char str[6])
{
	_settextwindow(0,0,24,79);
	remove_in();
	open_window(10,10,46,8,fcolor,(long)hcolor,205,fcolor,hcolor);
	sprintf(err_buf,"\n This is the %s rate schedule. \n",str);
	_outtext(err_buf);
	sprintf(err_buf," It applies to tables %2d thru %2d .\n\n",h_from,h_to);
	_outtext(err_buf);
	_outtext("         Press any key to continue.");
	getch();
	fflush( stdin );
	close_window();
	print_ins();
_settextwindow(7,3,19,76);
}

/********************* field functions *****************************/
/************* GET DAY OF WEEK ************************************/
/*E1 get week day */
e1()
{
	int ck;
	open_window(19,2,76,4,fcolor,(long)hcolor,205,fcolor,hcolor );
	 _outtext(" Enter the first two letters of the day of the week that these rates\n");
	 _outtext(" are in effect. Example: DE = Default, FR = FRIDAY, SA = SATURDAY, etc.");
	if(first && (tab-1)->r_stop != 2400L)
	{
		open_window(1,7,71,6,fcolor,(long)hcolor,205,fcolor,hcolor);
		_outtext(" The default rates (day of week = 'DE') must be entered first\n");
		_outtext(" and provide the rates for a complete 24 day (midnight to midnight).\n");
		_outtext(" The instructions for each column will appear at the bottom of\n");
		_outtext(" screen.  For additional information press the F1 key.");
	}
	while(1)
	{
		_settextwindow(7,3,19,76);
		_settextposition( r_row,2 );
		if(tab->day_of_week >0)
			strcpy(buf,prt.p_day);
		else
			buf[0]='\0';
		if(read_str(2,buf,1,1,1,0)) break ;
		if(first)
		{
			if(strncmp(buf,"DE"))
				if((tab-1)->r_stop != 2400L)
				{
					r_err(7);

					_settextwindow(7,3,19,76);
					_settextposition(r_row,2 );
					_outtext("  ");
					continue;
				}
				else
				first = 0;
		}
			strcpy(prt.p_day ,buf);
			ck = strcmp(buf,"MO");
			if(ck==0) {tab->day_of_week =2; break;}
			ck = strcmp(buf,"TU");
			if(ck==0) {tab->day_of_week =3; break;}
			ck = strcmp(buf,"WE");
			if(ck==0) {tab->day_of_week =4; break;}
			ck = strcmp(buf,"TH");
			if(ck==0) {tab->day_of_week =5; break;}
			ck = strcmp(buf,"FR");
			if(ck==0) {tab->day_of_week =6; break;}
			ck = strcmp(buf,"SA");
			if(ck==0) {tab->day_of_week =7; break;}
			ck = strcmp(buf,"SU");
			if(ck==0) {tab->day_of_week =8; break;}
			ck = strcmp(buf,"DE");
			if(ck==0) {tab->day_of_week =1; break;}
			strcpy(prt.p_day,"  ");
			r_err(1);
			_settextwindow(7,3,19,76);
			_settextposition(r_row,2 );
			_outtext("  ");
			continue;
	 }
	 _settextwindow(7,3,19,76);
	 _settextposition(r_row,2 );
	 if(tab->day_of_week)
		_outtext(prt.p_day);

	 close_window(1);
}

/*E2 get start time */

e2()
{

	long h_r_start;

	while(1)
	{
		open_window(19,2,76,4,fcolor,(long)hcolor,205,fcolor,hcolor );
		_outtext(" Enter the time that the corresponding rates on this line should take \n");
		_outtext(" effect. Examples: 00:00AM = start of first hour of the day.");
		col_no=7;
		strcpy(buf,prt.p_start);
		_settextwindow(7,3,19,76);
		if(get_times(&buf,&h_hr,&h_mn,&r_row, &col_no,2, tm_err)) break;
		buf[2]=':';
		strcpy(prt.p_start,buf);
		_settextwindow(7,3,19,76);
		_settextposition( r_row,col_no );
		_outtext(prt.p_start);
		h_r_start = (int)h_hr*100;
		h_r_start += (int)h_mn;
		if(h_r_start ==2400L)
			{
				prt.p_start[0]=0;
				h_r_start=0;
				tm_err(9);
				close_window(0);
				continue;
			}

		if(first && tab == rate_tab)    /* on DE check start time = 00:00an */
		{
			if(h_r_start > 0)
			{
				prt.p_start[0]=0;
				h_r_start=0;
				tm_err(5);
				close_window(0);
				continue;
			}
		 }
		 else
			 if(first && h_r_start != (tab-1)->r_stop)  /* start must = prev stop if DE */
			 {
				 prt.p_start[0]=0;
				 h_r_start=0;
				 tm_err(6);
				 close_window(0);
				 continue;
			 }
		tab->r_start = h_r_start;
		break;
	}
	close_window(1);
}
/*E3 get stop time */
e3()
{
	long h_r_stop;
	while(1)
	{
		open_window(19,2,75,4,fcolor,(long)hcolor,205,fcolor,hcolor );
		_outtext(" Enter the stop time that the corresponding rates on this line should no\n");
		_outtext(" longer be in effect. Example: 12:00AM = midnight.");

		col_no=18;
		strcpy(buf,prt.p_stop);
		_settextwindow(7,3,19,76);
		if(get_times(&buf,&h_hr,&h_mn,&r_row, &col_no,3, tm_err)) break;
		buf[2]=':';
		strcpy(prt.p_stop,buf);
		_settextwindow(7,3,19,76);
		_settextposition( r_row,col_no );
		_outtext(prt.p_stop);
		h_r_stop = (int)h_hr*100;
		h_r_stop += (int)h_mn;
		if(h_r_stop ==0000L)
			{
				prt.p_stop[0]=0;
				h_r_stop=0;
				tm_err(8);
				close_window(0);
				continue;
			}

		if(tab->r_start >=h_r_stop)
			{
				prt.p_stop[0]=0;
				h_r_stop=0;
				tm_err(3);
				close_window(0);
				continue;
			}
	tab->r_stop = h_r_stop;
	break;
	}
	close_window(1);
	}
/*E4 get rate 1 */
e4()
{
	hld_playr = 1;
	hld_col = 29;
	handle_rate();
}
/*E5 get rate 2 */
e5()
{
	hld_playr = 2;
	hld_col = 37;
	handle_rate();
}
/*E6 get rate 3 */
e6()
{
	hld_playr = 3;
	hld_col = 45;
	handle_rate();
}
/*E7 get rate 4 */
e7()
{
	hld_playr = 4;
	hld_col = 53;
	handle_rate();

}
/*E8 get rate 5 */
e8()
{
	hld_playr = 5;
	hld_col = 61;
	handle_rate();

}
/*E9 get rate 6 */
e9()
{
	hld_playr = 6;
	hld_col = 69;
	handle_rate();
	update_tab_no();
}
/************************ copy last table to memory *******************/
save_data()
{
	tab3 = h_tab3;       /* table3 pointer to next blank record */
	tab = rate_tab;    /* initialize work table pointer */
	while(tab->day_of_week > 0)
	{
		memcpy(tab3,tab,sizeof(rate_tab[0]));
		++tab;++tab3;
	}
	h_tab3=tab3;
}


/****************** GET DATA INPUT **************************/
get_data()
{

	r_row =1;
	fld_no = 0;
	while(1)
	{
		ctl_sw = 0;
		if (r_row >9)
		{
			r_row=9;
			_settextwindow(7,3,15,76);
			_scrolltextwindow(_GSCROLLUP);
			if(tab<=next_tab)
				clear_line();
			replace_lines();
		}
		while(fld_no < 9)
		{
		   (*funct[fld_no].fld)();        /* get current field from keybd */
			ctl_sw = 0;
			control_key();             /* test for and process ctl  key */
			if(ctl_sw ) break;
		}
		if(ctl_sw > 1) break;     /* F10 has been keyed */
	}

}
/********************** update table no fields **************/
update_tab_no()
{
	tab->from=atoi(start_tab);
	tab->to =atoi(stop_tab);
}
/****************** remove instructions from screen **************/
remove_in()
{

	_settextposition(23,2);
	_outtext("                                                                             ");
	_settextposition(24,2);
	_outtext("                                                                             ");
}
/*************** get table numbers for rate table *******************/
get_tab_nos()
{
	char c;

		/*---------------- remove instructions from screen  --------*/
		remove_in();


	while(1)
	{
			open_window(10,10,60,8,fcolor,(long)hcolor,205,fcolor,hcolor);
			_outtext(" Enter below the range of tables for which the\n");
			_outtext(" following rate schedule will apply;\n\n");
			   _outtext("   Starting table #. ");
			start_tab[0]='\0';
			reads(2,start_tab,0,1,0,1);
			_outtext("\n\n   Ending table #.  ");
			stop_tab[0]='\0';
			reads(2,stop_tab,0,1,0,1);
			open_window(19,10,60,4,fcolor,(long)hcolor,205,fcolor,hcolor);
			_outtext("  Are the above table numbers correct\n");
			_outtext("  Press 'N' for no, 'Y' for yes");
			if(toupper(c=getch()) == 'Y')
				{ close_window(0); close_window(0); break; }
			close_window(0);
			close_window(0);
	}
		_settextposition(24,2);
		_settextcolor(hcolor);
		_setbkcolor((long)fcolor);
		_outtext("   Press the F1 key at any time for instructions.   ");
		_settextcolor(fcolor);
		_setbkcolor((long)hcolor);

}
/*************** process control keys *****************************/
control_key()
{
char c;

	switch(ctl_key)
	{
		/***********  check for F1 key (help screen) ************/
		  case ';':

			  open_window(4,2,76,21,fcolor,(long)hcolor,205,fcolor,hcolor);
			  hlp_rate();
			  while(1)      /* read any key or F1 */
			  {
				  if((c = getch()) != '\0')break ;
				  c= getch();
				  break;
			  }
			  close_window(1);
			  if (c==';')    /* check for F1 key */
			  {
				  open_window(1,1,76,21,fcolor,(long)hcolor,32,fcolor,hcolor);
				  rate_lay();     /*  print rate screen layout */
				  default_mesg();
				  close_window(1);

			  }
			  break;

		  /********** cursor right ****************************/
		  case 'M':
			  if(fld_no == 8){ line_feed(); fld_no =0; }
			  else
				++fld_no;                        /* increment record pointer */
			  break;
		  /*************** check for currsor left key *********/
		  case 'K':
			  if (fld_no > 0)
			  {
				  --fld_no;
			  }
			  break;

		  /********** return *************************************/
		  case '\r':
			  if(fld_no == 8) { line_feed(); fld_no = 0; }
			  else
				++fld_no;                        /* increment record pointer */
			  break;

		  /************ check for cursor down key ******************/
		  case 'P':

			  line_feed();
			  break;

		  /************** check for cursor up key ***************/
		  case 'H':
			  if(r_row ==1)         /*if on first row */
				  if (tab == rate_tab)
					  break;
				  else
				  {
					  _settextwindow(7,3,15,76);
					  _scrolltextwindow(_GSCROLLDOWN);
					  replace_lines();
				  }
			  if(tab >= next_tab && tab->rate[5] == 0)   /*if last row */
							  /* if line incomplete blank current */
			  {                    /*    record before moving up */
				  memset(prt.p_day,'\0',54); /* clear hold print fields */
				  memset(tab,0,sizeof(rate_tab[0])); /* clear curr record*/
				  clear_line();
			  }
			  if(r_row>1) r_row -= 1;
			  --tab;
			  update_prt_fields();
			  clear_line();
			  break;

		  /************** check for F6 key (delete line) ***********/
		  case '@':
			  yn_mesg(" Do you want to delete a line from the schedule ?\n");
			  if(ex_sw==1) break;
			  memset(prt.p_day,'\0',54); /* clear hold print fields */
			  memset(tab,0,sizeof(rate_tab[0])); /* clear curr record*/
			  reprint();
			  break;

		  /************** check for F8 key (delete table) ***********/
		  case 'B':
		  yn_mesg(" Do you want to delete this entire rate schedule ?\n");
		  if(ex_sw==1) break;

		  ctl_sw = 3;
		  break;
		  /*************** check for F10 key ( end of job) **********/
		  case 'D':
		  remove_in();
		  yn_mesg(" Are you done with this rate schedule ? \n");
		  if(ex_sw==1){print_ins(); break;}
		  if(tab >= next_tab)
		  {
			  memset(prt.p_day,'\0',54);     /*clear hold print fields */
			  clear_line();
		  }

		  rate_sort();
		  if(edit_rates()){  ctl_sw =2; break; }
		  err_tab = tab;       /* store pointer to error entry */
		  rate_lay();                    /* print rate screen layout */
		  h_from= 0;
		  start_tab[0] = '\0';
		  _settextwindow(7,3,19,76);
		  r_row=1;
		  tab = rate_tab;
		  ctl_key=0;
		  reprint();

		  break;
		/******************* default ******************************/
		  default:
			  clear_line();
			  break;
	}
return(0);
}

/************************ LINE FEED  ***********************************/
		  line_feed()
		  {
			  ++tab;
			  r_row += 1;
			  if(tab>next_tab)
			  {
				  next_tab = tab;            /* store pointer to last add */
				  memset(prt.p_day,'\0',54);     /*clear hold print fields */
				  fld_no =0;
			  }
			  else
			  if(tab->day_of_week >0)
				update_prt_fields();
			  else
			  {
				  memset(prt.p_day,'\0',54);     /*clear hold print fields */
				  fld_no = 0;
			  }
			  ctl_sw = 1;
		  }


/*************** time input error *********************************/
tm_err(int x)
{
	r_err(x);
	_settextwindow(7,3,19,76);
	_settextposition( r_row,col_no );
	buf[0]='\0';
	_outtext("       ");
}

/************** reprint screen and/or delete **************************/
reprint()
{
	struct rate_rec *h_tab;
	struct rate_rec *w_tab;
	int h_row = r_row;
	h_tab = tab;
	w_tab = tab;

	while(ctl_key)
	{
		++w_tab;              /* delete current record */
		while(1)
		{
			if (w_tab->day_of_week >0)
			   memcpy(tab++,w_tab++,sizeof(rate_tab[0]));
			   else
			   break;
		}
		memset(tab,0,sizeof(rate_tab[0]));
		tab=h_tab;
		break;
	}
	while(tab->day_of_week >0)
	{
		update_prt_fields();
		clear_line();
		if(err_tab == tab)
		{
			_settextcolor(fcolor+24);
			_settextposition(r_row,1);
			_outtext("");
			_settextcolor(fcolor);
			err_tab =0;
		}
		++tab; ++r_row;
		if(r_row > 9) break;
	}
	if(r_row < 10)
	{
		memset(prt.p_day,'\0',54); /* clear hold print fields */
		clear_line();
	}
	tab=h_tab; r_row = h_row;
	if(tab->rate[0] >0)
		update_prt_fields();
	else
		memset(prt.p_day,'\0',54); /* clear hold print fields */
		clear_line();
   if(ctl_key)
		if(tab!=next_tab)
			--next_tab;    /* decrement if delete */
	fld_no=0;

}
/*************** replace lines when scrolling ************************/
		replace_lines()
		{
		_settextposition( r_row,5 ); _outtext("�");
		_settextposition( r_row,16 ); _outtext("�");
		_settextposition( r_row,27 ); _outtext("�");
		_settextposition( r_row,35 ); _outtext("�");
		_settextposition( r_row,43 ); _outtext("�");
		_settextposition( r_row,51 ); _outtext("�");
		_settextposition( r_row,59 ); _outtext("�");
		_settextposition( r_row,67 ); _outtext("�");
		}

/************************* process each rate ***********************/
handle_rate()
{

	while(1)
	{
		open_window(19,2,75,4,fcolor,(long)hcolor,205,fcolor,hcolor );

		sprintf(err_buf,"  Enter the hourly table rental rate for %1d player/s.\n",hld_playr);
		_outtext(err_buf);
		_outtext("  Examples, 5.00, 6.50, etc.");
		_settextwindow(7,3,19,76);
		_settextposition( r_row,hld_col );
		strcpy(buf,prt.p_1[hld_playr-1]);
		if( read_str(5,buf,1,1,1,1)) break;
		h_rate = atof(buf);
		if(h_rate>99 || !h_rate  >0)
		{
			r_err(4);
			_settextposition( r_row,hld_col );
			_outtext("     ");
			close_window(0);
			continue;
		}
		tab->rate[hld_playr-1]=h_rate;
		sprintf(prt.p_1[hld_playr-1],"%2.2f",tab->rate[hld_playr-1]);
		_settextposition( r_row,hld_col );
		_outtext(prt.p_1[hld_playr-1]);
		break;
	}
	close_window(0);
}

/****************************** update print fields **************/
update_prt_fields()
{

	char h_ampm[3];
	if(tab->day_of_week==2) strcpy(prt.p_day , "MO");
	if(tab->day_of_week==3) strcpy(prt.p_day , "TU");
	if(tab->day_of_week==4) strcpy(prt.p_day , "WE");
	if(tab->day_of_week==5) strcpy(prt.p_day , "TH");
	if(tab->day_of_week==6) strcpy(prt.p_day , "FR");
	if(tab->day_of_week==7) strcpy(prt.p_day , "SA");
	if(tab->day_of_week==8) strcpy(prt.p_day , "SU");
	if(tab->day_of_week==1) strcpy(prt.p_day , "DE");

	sprintf(buf,"%4d",tab->r_start);
	(int)h_mn =atoi(&buf[2]);
	buf[2]='\0';
	(int)h_hr= atoi(buf);
	if (h_hr > 12)
	{
		h_hr -= 12;
		strcpy(h_ampm,"PM");
		if(h_hr == 12 ) strcpy(h_ampm,"AM");
	}
	else
	{
		strcpy(h_ampm,"AM");
		if(h_hr == 12 ) strcpy(h_ampm,"PM");
	}
	sprintf(prt.p_start,"%02d",(int)h_hr);
	prt.p_start[2]= ':';
	sprintf(&prt.p_start[3],"%02d",(int)h_mn);
	strcpy(&prt.p_start[5],h_ampm);
	if(prt.p_start[1]=='\0')
		{
			prt.p_start[1]=prt.p_start[0];
			prt.p_start[0] = '0';
		}
	sprintf(buf,"%4d",tab->r_stop);
	(int)h_mn =atoi(&buf[2]);
	buf[2]='\0';
	(int)h_hr= atoi(buf);
	if (h_hr > 12)
	{
		h_hr -= 12;
		strcpy(h_ampm,"PM");
		if(h_hr == 12 ) strcpy(h_ampm,"AM");
	}
	else
	{
		strcpy(h_ampm,"AM");
		if(h_hr == 12 ) strcpy(h_ampm,"PM");
	}
	sprintf(prt.p_stop,"%02d",(int)h_hr);
	prt.p_stop[2]= ':';
	sprintf(&prt.p_stop[3],"%02d",(int)h_mn);
	strcpy(&prt.p_stop[5],h_ampm);
	if(prt.p_stop[1]=='\0')
		{
			prt.p_stop[1]=prt.p_stop[0];
			prt.p_stop[0] = '0';
		}
	sprintf(prt.p_1[0],"%2.2f",tab->rate[0]);
	sprintf(prt.p_1[1],"%2.2f",tab->rate[1]);
	sprintf(prt.p_1[2],"%2.2f",tab->rate[2]);
	sprintf(prt.p_1[3],"%2.2f",tab->rate[3]);
	sprintf(prt.p_1[4],"%2.2f",tab->rate[4]);
	sprintf(prt.p_1[5],"%2.2f",tab->rate[5]);

}

/******************** CLEAR or PRINT LINE ******************************/
clear_line()

{
	_settextwindow(7,3,19,76);
	_settextposition( r_row,2 );
	_outtext("  ");
	_settextposition( r_row,2 );
	_outtext(prt.p_day);
	_settextposition( r_row,7 );
	_outtext("        ");
	_settextposition( r_row,7 );
	_outtext(prt.p_start);
	_settextposition( r_row,18 );
	_outtext("        ");
	_settextposition( r_row,18 );
	_outtext(prt.p_stop);
	_settextposition( r_row,29 );
	_outtext("     ");
	_settextposition( r_row,29 );
	_outtext(prt.p_1[0]);
	_settextposition( r_row,37 );
	_outtext("     ");
	_settextposition( r_row,37 );
	_outtext(prt.p_1[1]);
	_settextposition( r_row,45 );
	_outtext("     ");
	_settextposition( r_row,45 );
	_outtext(prt.p_1[2]);
	_settextposition( r_row,53 );
	_outtext("     ");
	_settextposition( r_row,53 );
	_outtext(prt.p_1[3]);
	_settextposition( r_row,61 );
	_outtext("     ");
	_settextposition( r_row,61 );
	_outtext(prt.p_1[4]);
	_settextposition( r_row,69 );
	_outtext("     ");
	_settextposition( r_row,69 );
	_outtext(prt.p_1[5]);

}
/******************************* print errors ************************/
r_err(int err_cd)
{
	char press_any[] = {"Press any key to continue."};

	switch (err_cd)
	{
		case 1:
		{
			strcpy(err_buf,"In-valid Day of the Week code.");
			break;
		}
		default: return(0);
		case 2:
		{
			strcpy(err_buf,"Invalid Start time. - Please re-enter.");
			break;
		}
		case 3:
		{
			strcpy(err_buf,"Invalid Stop time. Must be later than start time.");
			break;
		}
		case 4:
		{
			strcpy(err_buf,"Invalid rate  - please re-enter.");
			break;
		}
		case 5:
		{
			strcpy(err_buf,"Invalid \"DE\" start time. Must start with 00:00AM (midnight).");
			break;
		}
		case 6:
		{
			strcpy(err_buf,"Invalid \"DE\" start time. Must be the same as previos stop time.");
			break;
		}
		case 7:
		{
			strcpy(err_buf,"Default times do not cover a full 24 hour period. Please correct.");
			break;
		}
		case 8:
		{
			strcpy(err_buf,"00:00AM is the start of a new day, It can't be in the stop time.");
			break;
		}
		case 9:
		{
			strcpy(err_buf,"12:00AM is used for the end of the day, It can't be in the start time.");
			break;
		}

	}
	open_window(1,(80-strlen(err_buf)+2)/2,strlen(err_buf)+2,5,fcolor,(long)hcolor,32,hcolor,fcolor);
	_settextposition(1,((strlen(err_buf)+4) - strlen("E R R O R  !!"))/2);
	_outtext("E R R O R  !!");
	_settextposition(2,((strlen(err_buf)+2) - strlen(err_buf))/2);
	_outtext(err_buf);
	_settextposition(3,((strlen(err_buf)+2) - strlen(press_any))/2);
	_outtext(press_any);
	getch();
	close_window(0);
	_settextwindow(7,3,19,76);
}


