/*Dale & Debbie Grey, home -- 373-5570   business -- 645-3913*/
/*
	THIS MODULE RETREIVES AND MAINTAINS THE RATE SCHEDULES
*/


#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
	int extern b_red,b_black,b_yellow,b_white,b_grey,b_cyan,b_blue,b_bwhite;
	int extern b_green,b_lblue,b_lcyan,b_lmagenta,b_lgreen,b_lred,b_brown;
	int extern f_red,f_black,f_yellow,f_white,f_grey,f_cyan,f_blue,f_bwhite;
	int extern f_green,f_lblue,f_lcyan,f_lmagenta,f_lgreen,f_lred,f_brown;

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
struct rate_rec *ttab;      /* pointer to table records */
struct rate_rec *err_tab;   /* pointer to error table entry */
struct rate_rec *next_tab; /* pointer to next available blank record */


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

char day_of_week[3];
char buf2[80];
int cur=0,err_cd,col_no,fld_no;
long h_hr,h_mn;
int first = 1;
int extern ex_sw;
int r_row;
int extern fcolor;

int extern hcolor;
char start_tab[3];
char stop_tab[3];
int h_from;
int h_to;
int ctl_key,am,pm;
float h_rate;
int hld_playr,hld_col;
int ctl_sw =0;
	char err_buff[80];
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
	ttab = rate_tab;     /* initialize pointer to rate table */
	tab2=rate_tab2;
	next_tab = ttab;     /* initialize pointer for next add */
	tab3 = rate_tab3;
	h_tab3 = tab3;
	h_from=0;
	h_to=0;

	textbackground(hcolor);      /* set background color */
	clrscr();
	open_window(10,15,50,5,f_yellow,b_black,205,f_yellow,b_red);
	cputs("\n\r  Please wait -- retrieving FIRST rate schedule.");
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
				memcpy(ttab,tab2,sizeof(rate_tab[0]));
				++ttab;++tab2;
			}
			else
				break;
		}
		ttab=rate_tab;    /* set pointer next tab */
		for(next_tab = ttab;next_tab->day_of_week >0;next_tab++);
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
		window(1,1,80,25);
		get_data();        /* get rate table data */
		if(ctl_sw != 3)       /* delete table, bypass save if 3 */
		{
			rate_sort();         /* sort work table records */
			save_data();         /* save work table to memory */
		}
		memset(rate_tab,'\0',sizeof(rate_tab));
		ttab=rate_tab;    /* set pointer next tab */
		next_tab = ttab;
		first =0;
		if(tab2->from ==0 && tab2->to==0)
		{
			first =1;
						 /* ask if above is ok */
			yn_mesg(" There are no additional rate schedules.  Do you want to enter another one ?\n\r" );
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
					memcpy(ttab,tab2,sizeof(rate_tab[0]));
					++ttab;++tab2;
				}
				else
					break;
			}
			ttab=rate_tab;    /* set pointer next tab */
			for(next_tab = ttab;next_tab->day_of_week >0;next_tab++);
			--next_tab;

			rate_lay();                    /* print rate screen layout */
			r_row = 1;
			ctl_key =0;
			reprint();                     /* print rate records */
		   rate_msg("NEXT");
		}

	}
	open_window(10,18,44,3,f_yellow,b_black,205,f_yellow,b_red);
	cputs("  Please wait -- updating rate schedules.");

	data_out();          /* write all tables to disk */
	close_window(1);        /* end of job */
	window(1,1,80,25);
	clrscr();
	return(0);

}
rate_msg(char str[6])
{
	window(1,1,80,25);
	remove_in();
	open_window(15,17,46,8,f_yellow,b_black,205,f_red,b_red);
	sprintf(err_buff,"\n\r      This is the %s rate schedule. \n\r",str);
	cputs(err_buff);
	sprintf(err_buff,"      It applies to tables %2d thru %2d .\n\n\r",h_from,h_to);
	cputs(err_buff);
	cputs("         Press any key to continue.");
	getch();
	fflush( stdin );
	close_window();
	print_ins();
window(3,7,76,19);
return 0;
}

/********************* field functions *****************************/
/************* GET DAY OF WEEK ************************************/
/*E1 get week day */
e1()
{
	int ck;
	open_window(19,2,76,4,f_lcyan,b_black,205,f_lcyan,b_black );
	 cputs(" Enter the first two letters of the day of the week that these rates\n\r");
	 cputs(" are in effect. Example: DE = Default, FR = FRIDAY, SA = SATURDAY, etc.");
	if(first && (ttab-1)->r_stop != 2400L)
	{
		open_window(1,7,71,6,f_yellow,b_black,205,f_yellow,b_black);
		cputs(" The default rates (day of week = 'DE') must be entered first\n\r");
		cputs(" and provide the rates for a complete 24 day (midnight to midnight).\n\r");
		cputs(" The instructions for each column will appear at the bottom of\n\r");
		cputs(" screen.  For additional information press the F1 key.");
	}
	while(1)
	{
		window(3,7,76,19);
		textcolor(f_black);
		textbackground(b_cyan);
		gotoxy( 2,r_row );
		if(ttab->day_of_week >0)
			strcpy(buf2,prt.p_day);
		else
			buf2[0]='\0';
		if(read_str(2,buf2,1,1,1,0)) break ;
		if(first)
		{
			if(strcmp(buf2,"DE"))
				if((ttab-1)->r_stop != 2400L)   // not = to DE
				{
					r_err(7);

					window(3,7,76,19);
					gotoxy(2,r_row );
					cputs("  ");
					continue;
				}
				else
				first = 0;
		}
			strcpy(prt.p_day ,buf2);
			ck = strcmp(buf2,"MO");
			if(ck==0) {ttab->day_of_week =2; break;}
			ck = strcmp(buf2,"TU");
			if(ck==0) {ttab->day_of_week =3; break;}
			ck = strcmp(buf2,"WE");
			if(ck==0) {ttab->day_of_week =4; break;}
			ck = strcmp(buf2,"TH");
			if(ck==0) {ttab->day_of_week =5; break;}
			ck = strcmp(buf2,"FR");
			if(ck==0) {ttab->day_of_week =6; break;}
			ck = strcmp(buf2,"SA");
			if(ck==0) {ttab->day_of_week =7; break;}
			ck = strcmp(buf2,"SU");
			if(ck==0) {ttab->day_of_week =8; break;}
			ck = strcmp(buf2,"DE");
			if(ck==0) {ttab->day_of_week =1; break;}
			strcpy(prt.p_day,"  ");
			r_err(1);
			window(3,7,76,19);
			gotoxy(2,r_row );
			cputs("  ");
			continue;
	 }
	 window(3,7,76,19);
	 gotoxy(2,r_row );
	 if(ttab->day_of_week)
		cputs(prt.p_day);

	 close_window(1);
return 0;
}

/*E2 get start time */

e2()
{

	long h_r_start;

	while(1)
	{
		open_window(19,2,76,4,f_black,b_cyan,205,f_black,b_cyan );
		cputs(" Enter the time that the corresponding rates on this line should take \n\r");
		cputs(" effect. Examples: 00:00AM = start of first hour of the day.");
		col_no=7;
		strcpy(buf2,prt.p_start);
		window(3,7,76,19);
		textcolor(f_black);
		textbackground(b_cyan);
		if(get_times(&buf2,&h_hr,&h_mn,&r_row, &col_no,2, tm_err)) break;
		buf2[2]=':';
		strcpy(prt.p_start,buf2);
		window(3,7,76,19);
		gotoxy( col_no,r_row );
		cputs(prt.p_start);
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

		if(first && ttab == rate_tab)    /* on DE check start time = 00:00an */
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
			 if(first && h_r_start != (ttab-1)->r_stop)  /* start must = prev stop if DE */
			 {
				 prt.p_start[0]=0;
				 h_r_start=0;
				 tm_err(6);
				 close_window(0);
				 continue;
			 }
		ttab->r_start = h_r_start;
		break;
	}
	close_window(1);
return 0;
}
/*E3 get stop time */
e3()
{
	long h_r_stop;
	while(1)
	{
		open_window(19,2,76,4,f_lcyan,b_black,205,f_lcyan,b_black );
		cputs(" Enter the stop time that the corresponding rates on this line should no\n\r");
		cputs(" longer be in effect. Example: 12:00AM = midnight.");

		col_no=18;
		strcpy(buf2,prt.p_stop);
		window(3,7,76,19);
		textcolor(f_black);
		textbackground(b_cyan);

		if(get_times(&buf2,&h_hr,&h_mn,&r_row, &col_no,3, tm_err)) break;
		buf2[2]=':';
		strcpy(prt.p_stop,buf2);
		window(3,7,76,19);
		gotoxy(col_no,r_row );
		cputs(prt.p_stop);
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

		if(ttab->r_start >=h_r_stop)
			{
				prt.p_stop[0]=0;
				h_r_stop=0;
				tm_err(3);
				close_window(0);
				continue;
			}
	ttab->r_stop = h_r_stop;
	break;
	}
	close_window(1);
	return 0;
	}
/*E4 get rate 1 */
e4()
{
	hld_playr = 1;
	hld_col = 29;
	handle_rate();
return 0;
}
/*E5 get rate 2 */
e5()
{
	hld_playr = 2;
	hld_col = 37;
	handle_rate();
return 0;
}
/*E6 get rate 3 */
e6()
{
	hld_playr = 3;
	hld_col = 45;
	handle_rate();
return 0;
}
/*E7 get rate 4 */
e7()
{
	hld_playr = 4;
	hld_col = 53;
	handle_rate();

return 0;
}
/*E8 get rate 5 */
e8()
{
	hld_playr = 5;
	hld_col = 61;
	handle_rate();
return 0;
}
/*E9 get rate 6 */
e9()
{
	hld_playr = 6;
	hld_col = 69;
	handle_rate();
	update_tab_no();
return 0;
}
/************************ copy last table to memory *******************/
save_data()
{
	tab3 = h_tab3;       /* table3 pointer to next blank record */
	ttab = rate_tab;    /* initialize work table pointer */
	while(ttab->day_of_week > 0)
	{
		memcpy(tab3,ttab,sizeof(rate_tab[0]));
		++ttab;++tab3;
	}
	h_tab3=tab3;
return 0;
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
			window(3,7,76,15);
			gotoxy(1,9);          /* scroll window */
			cputs("\n");
			if(ttab<=next_tab)
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

return 0;
}
/********************** update table no fields **************/
update_tab_no()
{
	ttab->from=atoi(start_tab);
	ttab->to =atoi(stop_tab);
return 0;
}
/****************** remove instructions from screen **************/
remove_in()
{
    window(1,1,80,25);
	textcolor(fcolor);
	textbackground(hcolor);
	gotoxy(2,23);
	cputs("                                                                            ");
	gotoxy(2,24);
	cputs("                                                                            ");
return 0;
}
/*************** get table numbers for rate table *******************/
get_tab_nos()
{
	char c;
        /*---------------- remove instructions from screen  --------*/
		remove_in();
    while(1)
	{
			open_window(10,10,60,8,f_black,b_white,205,f_black,b_white);
			cputs(" Enter below the range of tables for which the\n\r");
			cputs(" following rate schedule will apply;\n\n\r");
			cputs("   Starting table #. ");
			start_tab[0]='\0';
			reads(2,start_tab,0,1,0,1);
			cputs("\n\n\r   Ending table #.  ");
			stop_tab[0]='\0';
			reads(2,stop_tab,0,1,0,1);
			open_window(19,10,60,4,f_bwhite,b_black,205,f_black,b_brown);
			cputs("  Are the above table numbers correct\n\r");
			cputs("  Press 'N' for no, 'Y' for yes");
            c=getch();
			if(  toupper(c) == 'Y')
				{ close_window(0); close_window(0); break; }
			fflush(stdin);
			close_window(0);
			close_window(0);
	}
		gotoxy(2,24);
		textcolor(hcolor);
		textbackground(fcolor);
		cputs("   Press the F1 key at any time for instructions.   ");
		textcolor(fcolor);
		textbackground(hcolor);
return 0;
}
/*************** process control keys *****************************/
control_key()
{
char c;

	switch(ctl_key)
	{
		/***********  check for F1 key (help screen) ************/
		  case ';':

			  remove_in();
			  open_window(4,2,76,21,f_black,b_white,205,f_black,b_white);
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
				  open_window(1,1,76,21,fcolor,hcolor,32,fcolor,hcolor);
				  rate_lay();     /*  print rate screen layout */
				  remove_in();
				  default_mesg();
				  close_window(1);

			  }
			  print_ins();
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
				  if (ttab == rate_tab)
					  break;
				  else
				  {
					  window(3,7,76,15);
					  gotoxy(1,9);          /* scroll window */
					  cputs("\n");
					  replace_lines();
				  }
			  if(ttab >= next_tab && ttab->rate[5] == 0)   /*if last row */
							  /* if line incomplete blank current */
			  {                    /*    record before moving up */
				  memset(prt.p_day,'\0',54); /* clear hold print fields */
				  memset(ttab,0,sizeof(rate_tab[0])); /* clear curr record*/
				  clear_line();
			  }
			  if(r_row>1) r_row -= 1;
			  --ttab;
			  update_prt_fields();
			  clear_line();
			  break;

		  /************** check for F6 key (delete line) ***********/
		  case '@':
			  yn_mesg(" Do you want to delete a line from the schedule ?\n\r");
			  if(ex_sw==1) break;
			  memset(prt.p_day,'\0',54); /* clear hold print fields */
			  memset(ttab,0,sizeof(rate_tab[0])); /* clear curr record*/
			  reprint();
			  break;

		  /************** check for F8 key (delete table) ***********/
		  case 'B':
		  yn_mesg(" Do you want to delete this entire rate schedule ?\n\r");
		  if(ex_sw==1) break;

		  ctl_sw = 3;
		  break;
		  /*************** check for F10 key ( end of job) **********/
		  case 'D':
			  if(ttab >= next_tab && ttab->rate[5] == 0)   /*if last row */
								  /* if line incomplete blank current */
			  {                    /*    record before exit			   */
				  memset(prt.p_day,'\0',54); /* clear hold print fields */
				  memset(ttab,0,sizeof(rate_tab[0])); /* clear curr record*/

				  if(( fld_no > 0) || (ttab->day_of_week > 0) || (ttab->r_start))
				  {
						open_window(16,12,58,4,f_yellow,b_red,205,f_red,b_red);
						cputs("Last line entered was incomplete and will be deleted !!\n\r");
						cputs("Press any key to continue.");
						getch();
						fflush(stdin);
						close_window(0);
				  }
				  fld_no =0;
				  clear_line();
			  }

		  remove_in();
		  yn_mesg(" Are you done with this rate schedule ? \n\r");
		  if(ex_sw==1){print_ins(); break;}
		  if(ttab >= next_tab)
		  {
			  memset(prt.p_day,'\0',54);     /*clear hold print fields */
			  clear_line();
		  }

		  rate_sort();
		  if(edit_rates()){  ctl_sw =2; break; }
		  err_tab = ttab;       /* store pointer to error entry */
		  rate_lay();                    /* print rate screen layout */
		  h_from= 0;
		  start_tab[0] = '\0';
		  window(3,7,76,19);
		  r_row=1;
		  ttab = rate_tab;
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
			  ++ttab;
			  r_row += 1;
			  if(ttab>next_tab)
			  {
				  next_tab = ttab;            /* store pointer to last add */
				  memset(prt.p_day,'\0',54);     /*clear hold print fields */
				  fld_no =0;
			  }
			  else
			  if(ttab->day_of_week >0)
				update_prt_fields();
			  else
			  {
				  memset(prt.p_day,'\0',54);     /*clear hold print fields */
				  fld_no = 0;
			  }
			  ctl_sw = 1;
		  return 0;
		  }


/*************** time input error *********************************/
tm_err(int x)
{
	r_err(x);
	window(3,7,76,19);
	gotoxy( col_no,r_row );
	buf2[0]='\0';
	cputs("       ");
return 0;
}

/************** reprint screen and/or delete **************************/
reprint()
{
	struct rate_rec *h_tab;
	struct rate_rec *w_tab;
	int h_row = r_row;
	h_tab = ttab;
	w_tab = ttab;

	while(ctl_key)
	{
		++w_tab;              /* delete current record */
		while(1)
		{
			if (w_tab->day_of_week >0)
			   memcpy(ttab++,w_tab++,sizeof(rate_tab[0]));
			   else
			   break;
		}
		memset(ttab,0,sizeof(rate_tab[0]));
		ttab=h_tab;
		break;
	}
	while(ttab->day_of_week >0)
	{
		update_prt_fields();
		clear_line();
		if(err_tab == ttab)
		{
			textcolor(f_lred+BLINK);
			gotoxy(1,r_row);
			cputs("");
			textcolor(fcolor);
			err_tab =0;
		}
		++ttab; ++r_row;
		if(r_row > 9) break;
	}
	if(r_row < 10)
	{
		memset(prt.p_day,'\0',54); /* clear hold print fields */
		clear_line();
	}
	ttab=h_tab; r_row = h_row;
	if(ttab->rate[0] >0)
		update_prt_fields();
	else
		memset(prt.p_day,'\0',54); /* clear hold print fields */
		clear_line();
   if(ctl_key)
		if(ttab!=next_tab)
			--next_tab;    /* decrement if delete */
	fld_no=0;
return 0;
}
/*************** replace lines when scrolling ************************/
		replace_lines()
		{
		gotoxy( 5,r_row ); cputs("�");
		gotoxy( 16,r_row ); cputs("�");
		gotoxy( 27,r_row ); cputs("�");
		gotoxy( 35,r_row ); cputs("�");
		gotoxy( 43,r_row ); cputs("�");
		gotoxy( 51,r_row ); cputs("�");
		gotoxy( 59,r_row ); cputs("�");
		gotoxy( 67,r_row ); cputs("�");
		return 0;
		}

/************************* process each rate ***********************/
handle_rate()
{
	char c_hld_playr[2];
	while(1)
	{
		open_window(19,2,76,4,f_yellow,b_black,205,f_yellow,b_black );

		cputs("  Enter the hourly table rental rate for   player/s.\n\r");
		gotoxy(42,1);
		itoa(hld_playr,c_hld_playr,10);
		textcolor(f_bwhite+BLINK);
		cputs(c_hld_playr);
		textcolor(f_yellow);
		gotoxy(1,2);
		cputs("  Examples, 5.00, 6.50, etc.");

		window(3,7,76,19);
		textcolor(f_black);
		textbackground(b_cyan);

		gotoxy( hld_col,r_row );
		strcpy(buf2,prt.p_1[hld_playr-1]);
		if( read_str(5,buf2,1,1,1,1)) break;
		h_rate = atof(buf2);
		if(h_rate>99 || !h_rate  >0)
		{
			r_err(4);
			gotoxy( hld_col,r_row );
			cputs("     ");
			close_window(0);
			continue;
		}
		ttab->rate[hld_playr-1]=h_rate;
		sprintf(prt.p_1[hld_playr-1],"%2.2f",ttab->rate[hld_playr-1]);
		gotoxy( hld_col,r_row );
		cputs("     ");

		gotoxy(( hld_col-strlen(prt.p_1[hld_playr-1]))+5,r_row );
		cputs(prt.p_1[hld_playr-1]);
		break;
	}
	close_window(0);
return 0;
}

/****************************** update print fields **************/
update_prt_fields()
{

	char h_ampm[3];
	if(ttab->day_of_week==2) strcpy(prt.p_day , "MO");
	if(ttab->day_of_week==3) strcpy(prt.p_day , "TU");
	if(ttab->day_of_week==4) strcpy(prt.p_day , "WE");
	if(ttab->day_of_week==5) strcpy(prt.p_day , "TH");
	if(ttab->day_of_week==6) strcpy(prt.p_day , "FR");
	if(ttab->day_of_week==7) strcpy(prt.p_day , "SA");
	if(ttab->day_of_week==8) strcpy(prt.p_day , "SU");
	if(ttab->day_of_week==1) strcpy(prt.p_day , "DE");

	sprintf(buf2,"%4d",ttab->r_start);
	(int)h_mn =atoi(&buf2[2]);
	buf2[2]='\0';
	(int)h_hr= atoi(buf2);
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
	sprintf(buf2,"%4d",ttab->r_stop);
	(int)h_mn =atoi(&buf2[2]);
	buf2[2]='\0';
	(int)h_hr= atoi(buf2);
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
	sprintf(prt.p_1[0],"%2.2f",ttab->rate[0]);
	sprintf(prt.p_1[1],"%2.2f",ttab->rate[1]);
	sprintf(prt.p_1[2],"%2.2f",ttab->rate[2]);
	sprintf(prt.p_1[3],"%2.2f",ttab->rate[3]);
	sprintf(prt.p_1[4],"%2.2f",ttab->rate[4]);
	sprintf(prt.p_1[5],"%2.2f",ttab->rate[5]);
return 0;
}

/******************** CLEAR or PRINT LINE ******************************/
clear_line()

{
	window(3,7,76,19);
	textcolor(f_black);
    textbackground(b_cyan);
	gotoxy( 2,r_row );
	cputs("  ");
	gotoxy( 2,r_row );
	cputs(prt.p_day);
	gotoxy( 7,r_row );
	cputs("        ");
	gotoxy( 7,r_row );
	cputs(prt.p_start);
	gotoxy( 18,r_row );
	cputs("        ");
	gotoxy( 18,r_row );
	cputs(prt.p_stop);
	gotoxy( 29,r_row );
	cputs("     ");
	gotoxy(( 29-strlen(prt.p_1[0]))+5,r_row );
	cputs(prt.p_1[0]);
	gotoxy( 37,r_row );
	cputs("     ");
	gotoxy(( 37-strlen(prt.p_1[1]))+5,r_row );
	cputs(prt.p_1[1]);
	gotoxy( 45,r_row );
	cputs("     ");
	gotoxy(( 45-strlen(prt.p_1[2]))+5,r_row );
	cputs(prt.p_1[2]);
	gotoxy( 53,r_row );
	cputs("     ");
	gotoxy(( 53-strlen(prt.p_1[3]))+5,r_row );
	cputs(prt.p_1[3]);
	gotoxy( 61,r_row );
	cputs("     ");
	gotoxy(( 61-strlen(prt.p_1[4]))+5,r_row );
	cputs(prt.p_1[4]);
	gotoxy( 69,r_row );
	cputs("     ");
	gotoxy(( 69-strlen(prt.p_1[5]))+5,r_row );
	cputs(prt.p_1[5]);
return 0;
}
/******************************* print errors ************************/
r_err(int err_cd)
{
	char press_any[] = {"Press any key to continue."};

	switch (err_cd)
	{
		case 1:
		{
			strcpy(err_buff,"In-valid Day of the Week code.");
			break;
		}
		default: return(0);
		case 2:
		{
			strcpy(err_buff,"Invalid Start time. - Please re-enter.");
			break;
		}
		case 3:
		{
			strcpy(err_buff,"Invalid Stop time. Must be later than start time.");
			break;
		}
		case 4:
		{
			strcpy(err_buff,"Invalid rate  - please re-enter.");
			break;
		}
		case 5:
		{
			strcpy(err_buff,"Invalid \"DE\" start time. Must start with 00:00AM (midnight).");
			break;
		}
		case 6:
		{
			strcpy(err_buff,"Invalid \"DE\" start time. Must be the same as previos stop time.");
			break;
		}
		case 7:
		{
			strcpy(err_buff,"Default times do not cover a full 24 hour period. Please correct.");
			break;
		}
		case 8:
		{
			strcpy(err_buff,"00:00AM is the start of a new day, It can't be in the stop time.");
			break;
		}
		case 9:
		{
			strcpy(err_buff,"12:00AM is used for the end of the day, It can't be in the start time.");
			break;
		}

	}
	open_window(1,(80-strlen(err_buff)+2)/2,strlen(err_buff)+2,5,f_yellow,\
						b_red,32,b_red,f_red);
	gotoxy(((strlen(err_buff)+4) - strlen("E R R O R  !!"))/2,1);
	cputs("E R R O R  !!");
	gotoxy(((strlen(err_buff)+2) - strlen(err_buff))/2,2);
	cputs(err_buff);
	gotoxy(((strlen(err_buff)+2) - strlen(press_any))/2,3);
	cputs(press_any);
	getch();
	fflush(stdin);
	close_window(0);
	window(3,7,76,19);
	textcolor(f_black);
	textbackground(b_cyan);
return 0;
}


