#include<string.h>
#include<time.h>
#include<dos.h>
#include<math.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
	extern struct tm *today2;
	int extern b_red,b_black,b_yellow,b_white,b_grey,b_cyan,b_blue,b_bwhite;
	int extern b_green,b_lblue,b_lcyan,b_magenta,b_lgreen,b_lred,b_brown;
	int extern f_red,f_black,f_yellow,f_white,f_grey,f_cyan,f_blue,f_bwhite;
	int extern f_green,f_lblue,f_lcyan,f_magenta,f_lgreen,f_lred,f_brown;
	int extern fcolor,hcolor;
	extern struct tm *today;
	char  extern ampm[3];
	long  t_used;
	long  hstop,hrs,mins;
	extern ldiv_t  divtm;
	int nickel=0;

	int cue_line_no,count_lines,err_sw,cue_change_sw,cue_sw,chng_cue_start;
	float costpp,tot_cue_amt;
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
	extern struct  rental *rent;   /* RENTAL RECORD POINTER */
	extern struct cues          /* cue stick structure */
	{
		int cue_no;
		int cue_tab;
		time_t cue_start;
		time_t cue_stop;
		float cue_rate;
		int cue_cust;
		int flag;
	}cue[200];
    char S0;        /*note- * = closed*/
	char S1[3];		/*line no*/
	char S2[4]; 	/*cue no*/
	char S3[3];     /*cust no*/
	char S4[8];		/*start*/
	char S5[8];		/*stop*/
	char S6[10];    /*time used*/
	char S7[6];     /*rate*/
	char S8[7];     /*amt*/
	char S9[8];


	get_cue_amt(int);
	time_t curr_time2;
	extern struct cues *cue_ptr;
	extern struct cues *next_cue_ptr;
	extern struct cues *hold_next_cue_ptr;

	char extern buf[81],cue_buf[81];
	char s_cue_no[4];
	int n_cue,cnt,cline;
	char s_cue_rate[6],cue_ans[2];
	float cue_rate,cue_amt,cue_sec_rate,cue_time_used;
	int extern tb_no,xx,ex_sw;
	long extern  *index;     /* INDEX POINTER */
	long extern idx[51];        /* MEMORY AREA INDEX ARRAY */
/*****************************************************************/
cue_stick()
{
	strcpy(buf,"ENTER TABLE NUMBER FOR CUE STICK BILLING");
	get_table_no();
	if(!tb_no) return(0);
	index = idx;
	for (xx=tb_no;xx>1;index++,xx--);
	if (*index ==0) {  err_msg(3); return(0);  }
	(long)rent = *index;
	if (rent->freeze == '1') {err_msg(6,rent->new_table); return(0);}\
									  /* has table # been changed -yes retn*/
	if (rent->freeze == '2') {err_msg(11); return(0);}  /* cash cleared*/
	if (rent->stop > 0L){err_msg(3); return(0);} /* if clocked out  return */
	get_cue_no();
    return  0;
}
get_cue_no()
{
	_setcursortype(_NORMALCURSOR);   /* set cursor to normal */

	while(1)
	{
		n_cue =0;
		cue_rate =0;
		open_window(17,20,40,8,f_bwhite,b_black,32,b_lcyan,f_magenta);
		gotoxy(1,1);
		textcolor(f_bwhite);
		if(cue_change_sw)
			cputs(" Enter correct stick #      .");
		else
			cputs(" Enter cue stick number     .");
		textcolor(f_lcyan);
		gotoxy(26,1);
		s_cue_no[0]='\0';
		reads(4,s_cue_no,0,1,0,1);
		n_cue = atoi(s_cue_no);
		textcolor(f_white);
		if(n_cue == 0||n_cue>200)
		{
			close_window(0);
			continue;
		}
		textcolor(f_bwhite);
   /*--------------- check, is cue allready rented -----------------*/
		for(cue_ptr =cue,cnt =0;cnt<200;cnt++,cue_ptr++)
		{
			if(cue_ptr->cue_no ==0) break;
			if(cue_ptr->flag==1)continue;
			if((cue_ptr->cue_no == n_cue) && (cue_ptr->cue_stop == 0)\
								&& (cue_ptr->cue_cust != rent->cust ))
				{err_msg(13,cue_ptr->cue_tab); return(0);}
			if((cue_ptr->cue_no == n_cue) && (cue_ptr->cue_stop == 0))

/*---------------- clock out cue ------------------------------------*/
			{
				if(cue_change_sw) {err_msg(13,cue_ptr->cue_tab); return 1;}
				textcolor(f_lcyan);
				cputs(" \n\r\n\r Clock this cue stick out.\n\r Press Y for yes.");
				textcolor(f_bwhite);
				cue_ans[0]='\0';
				reads(1,cue_ans,0,1,1,0);
								textcolor(f_white);
				if(cue_ans[0]!='Y') return(0);
				time(&cue_ptr->cue_stop);   /* update stop time */
				return(0);
			}
		}
        if(cue_change_sw) return 0;
		cputs(" \n\r\n\r Enter cue stick hourly rate       .");


			while(cue_rate == 0)

			{
				textcolor(f_lcyan);
				gotoxy(32,3);
				cputs("   ");
				gotoxy(32,3);
				s_cue_rate[0]='\0';
				reads(4,s_cue_rate,0,1,0,1);
                cue_rate=atof(s_cue_rate);
				if(cue_rate<10)
				{
					gotoxy(32,3);
					cprintf("%3.2f",cue_rate);
				}
				else
				{
                    err_msg(14);
					cue_rate=0;
				}
			}

		cputs(" \n\r\n\r Is the above correct.\n\r Press Y for yes or N for no.");
		textcolor(f_bwhite);
		cue_ans[0]='\0';
		reads(1,cue_ans,0,1,1,0);
		textcolor(f_white);
		if(cue_ans[0]=='Y')
		/*--------------- build record ---------------------------*/
		{
			next_cue_ptr->cue_no = n_cue;
			time(&next_cue_ptr->cue_start);
			next_cue_ptr->cue_cust=rent->cust;
			next_cue_ptr->cue_tab=rent->table;
			next_cue_ptr->cue_rate=cue_rate;
			next_cue_ptr++;
			break;
		}
		else
		{
			gotoxy(2,5);
            textcolor(f_yellow);
			cputs("Do you want to re-enter.\n\r Press Y for yes or N for no.  ");
			cue_ans[0]='\0';
			reads(1,cue_ans,0,1,1,0);
			textcolor(f_white);
			if(cue_ans[0]!='Y')
			break;
		}
   }
	return 0;

}
close_cues()
{
		for(cue_ptr =cue,cnt =0;cnt<200;cnt++,cue_ptr++)
		{
			if(cue_ptr->cue_no ==0) return(0);;
			if(cue_ptr->flag==1)continue;
			if((cue_ptr->cue_cust == rent->cust) && (cue_ptr->cue_stop == 0))

			{
				time(&cue_ptr->cue_stop);  /* clock out cue */
			}
	   }
return(0);
}
restart_cues(time_t hstart,time_t rentstop)    /*hstart,rent->stop*/
{

	hold_next_cue_ptr=next_cue_ptr;
	for(cue_ptr =cue,cnt =0;cnt<200;cnt++,cue_ptr++)
	{
		if(cue_ptr->cue_no ==0) return(0);
		if(cue_ptr==hold_next_cue_ptr) return 0;;
		if(cue_ptr->flag)continue;

		if(cue_ptr->cue_cust == rent->cust)
		{
			while((cue_ptr->cue_stop/10)==(rentstop/10)||rentstop==0)
			{
				if((cue_ptr->cue_stop/10)==(hstart/10))
						{
							cue_ptr->cue_stop =0;
							break;
						}
					cue_ptr->flag=2;   /*do not reopen*/
					next_cue_ptr->cue_no = cue_ptr->cue_no;
					next_cue_ptr->cue_start=hstart;
					next_cue_ptr->cue_cust=cue_ptr->cue_cust;
					next_cue_ptr->cue_tab=cue_ptr->cue_tab;
					next_cue_ptr->cue_rate=cue_ptr->cue_rate;
					next_cue_ptr++;
					break;
			}


		}
	}
return 0;
}
get_cue_amt(int cue_sw)
{
		tot_cue_amt =0;
		count_lines=0;
		for(cue_ptr =cue,cnt =0;cnt<200;cnt++,cue_ptr++)
		{
			if(cue_ptr->cue_no ==0) return(0);
			if(cue_ptr->flag==1) continue; /*deleted record*/
			if(cue_ptr->cue_cust == rent->cust)
			{
					 /* compute time used by line */
				if(cue_sw==1)
				{
					if(cue_ptr->cue_stop==0)
					{
						cue_time_used =  difftime(time(&curr_time2),\
												  cue_ptr->cue_start) ;
									  /* compute cue rental amt */
						compute_cue_amt();
						tot_cue_amt += costpp;
					 }
					 continue;
				}
				if(cue_ptr->cue_stop==0)
				cue_time_used =  difftime(time(&curr_time2),\
								  cue_ptr->cue_start) ;
				else
					cue_time_used =  difftime(cue_ptr->cue_stop,\
											  cue_ptr->cue_start) ;
					  /* compute cue rental amt */
				compute_cue_amt();
				tot_cue_amt += costpp;
				count_lines+=1;
				if(cue_sw==2)
					 cue_ptr->flag=1; /*delete all cues*/
				if(cue_sw ==3 && count_lines == cue_line_no)
					return 0;
			}
	   }
return 0;
}
compute_cue_amt()
{
		cue_sec_rate = (cue_ptr->cue_rate / 3600);
		cue_amt = cue_sec_rate * cue_time_used;
		sprintf(S8,"%3.2f",cue_amt);        /* load edit field */
		for(xx=0;S8[xx]!='.';xx++);
		/*_____________ round to nearest nickel ___________________*/
		if(S8[xx+2] != '0')
		{
			if(S8[xx+2] > '0' && S8[xx+2] < '6') S8[xx+2]= '5';
					else  { S8[xx+2]  = '0'; nickel =1;}
		}
		costpp = atof(S8);                 /* convert to two deimal places */
		if (nickel == 1) { costpp += .10; nickel = 0; }
        sprintf(S8,"%3.2f",costpp);        /* load edit field */
return 0;
}
/********************************************************************/
go_edit_cues()
 {
    time_t rentstop,hstart;
	get_cue_amt(3);  /*locate cue stick record */
	if(!count_lines){err_msg(18); return 0;}
	while(1)
	{
		edit_cues();
		cue_buf[0]='\0';
		reads(1,cue_buf,0,1,0,1);
		switch(cue_buf[0])
		{
/*-------------  DELETE CUE STICK LINE # ? ---------------*/
			case '1':

				if(rent->stop != 0){err_msg(16); break;}
				get_line_no();
				sprintf(cue_buf," Do you want to delete line # %1d ? ",cue_line_no);
				yn_mesg(cue_buf);
				if( ex_sw)  break;
				get_cue_amt(3);  /*locate cue stick record */
				cue_ptr->flag=1;
				break;

			case '3':
				return 0;
			case '2':

				if(rent->stop != 0){err_msg(16); break;}
				get_line_no();
				open_window(17,22,36,8,f_black,b_cyan,205,b_lcyan,f_black);
				cputs("  1. Change cue stick # ?\n\r");
				cputs("  2. Change start time ?\n\r");
				cputs("  3. Change stop time ?\n\r");
				cputs("  4. Change rate ?\n\r");
				cputs("  5. Exit - no change -\n\r");
				cputs("  Enter selection number.");
				cue_buf[0]='\0';
				reads(1,cue_buf,0,1,0,1);
				close_window(0);
				switch (cue_buf[0])
				{
				case '1':
				{
					cue_change_sw=1;
					cue_sw=get_cue_no();
                    cue_change_sw=0;
					if(cue_sw) break;
					get_cue_amt(3);  /*locate cue stick record */
					cue_ptr->cue_no=n_cue;
					break;
				}
				case '2':
				{
					chng_cue_start = 1;
					pool_str();
					chng_cue_start = 0;
						/* convert structure to type time_t */
					cue_ptr->cue_start = mktime(today2);
					_setcursortype(_SOLIDCURSOR);
					break;
				}
				case '3':
				{
					while(1)
					{
					if(cue_ptr->cue_stop==0)
					{
						err_msg(17);
						break;
					}
					open_window(17,22,40,7,f_black,b_white,205,b_lcyan,f_black);
					cputs(" Restart clocked out cue stick.\n\r");
					cputs("  1. Restart with previous stop time?\n\r");
					cputs("  2. Restart with current time?\n\r\n\r");
					cputs("  Enter selection number.");
					hstart=0;
					rentstop=0;
					cue_buf[0]='\0';
					reads(1,cue_buf,0,1,0,1);
					close_window();
					if(cue_buf[0]=='1')
					{
						hstart =cue_ptr->cue_stop;
						restart_cues(hstart,rentstop);    /*hstart,rent->stop*/
						break;
					}
					if(cue_buf[0] == '2')
					{
						time(&hstart);
						restart_cues(hstart,rentstop);    /*hstart,rent->stop*/
						break;
                    }
					continue;
                    }
					break;
				}
				case '4':
				{
					open_window(17,22,36,5,f_black,b_white,205,b_lcyan,f_black);
					cputs("\n\r Enter correct rate.");
					cue_rate=0;
					while(cue_rate == 0)
					{
						gotoxy(22,2);
						cputs("   ");
						gotoxy(22,2);
						s_cue_rate[0]='\0';
						reads(4,s_cue_rate,0,1,0,1);
						cue_rate=atof(s_cue_rate);
						if(cue_rate<10)
						{
							gotoxy(22,2);
							cprintf("%3.2f",cue_rate);
						}
						else
						{
							err_msg(14);
							cue_rate=0;
						}
					}

					get_cue_amt(3);  /*locate cue stick record */
					cue_ptr->cue_rate=cue_rate;
					close_window();
					break;
				}
				case '5':
				break;

			}

		}
	}
}

get_line_no()
{
	while(1)
	{
			open_window(17,20,40,6,f_lcyan,b_black,205,b_lcyan,f_black);
			cputs("\n\r Enter the line # of the cue stick\n\r");
			cputs(" you want to delete or change. ->");
			cue_buf[0]='\0';
			reads(2,cue_buf,0,1,0,1);
			cue_line_no = atoi(cue_buf);
			close_window(0);
			get_cue_amt(3);  /*locate cue stick record */
			if((count_lines<cue_line_no)||(cue_line_no==0))	 {err_msg(15); continue; }
			break;
    }
return 0;
}
edit_cues()
{
	int x;
	open_window(1,1,80,25,f_black,b_white,205,f_red,b_black);
	cue_lay();
	x =1;
	tot_cue_amt =0;
	for(cue_ptr =cue,cnt =0,cline =7;cnt<200;cnt++,cue_ptr++)
	{
		if(cue_ptr->cue_no ==0) break;
		if(cue_ptr->flag==1)continue; /*deleted record */
		if(cue_ptr->cue_cust == rent->cust)
		{
		cline += 1;
		if(cline>15)      /* 15 */
		{
			cline=15;
				open_window(20,2,22,4,fcolor,hcolor,205,fcolor,hcolor);
				textcolor(fcolor+8);
				cputs(" Press any key\n\r");
				cputs(" to view next line.");
				getch();
				fflush( stdin );
				textcolor(fcolor);
				close_window(0);
			window(11,9,68,16);
			gotoxy(1,8);
			cprintf("\n\r");           /*scrool window */
			window(2,2,78,24);
			gotoxy( 15,15 ); cputs("�");
			gotoxy( 22,15 ); cputs("�");
			gotoxy( 29,15 ); cputs("�");
			gotoxy( 37,15 ); cputs("�");
			gotoxy( 45,15 ); cputs("�");
			gotoxy( 55,15 ); cputs("�");
			gotoxy( 61,15 ); cputs("�");
		}
			/*S0 cue restarted */
				if(cue_ptr->flag==2)
					S0='*';
				else
					S0=' ';
			/*S1  line no*/
				itoa(x++,S1,10);
			/*S2 cue no.*/
				itoa(cue_ptr->cue_no,S2,10);
			/*S3 cust no.*/
				itoa(rent->cust,S3,10);
			/*S4 cue start time */
				get_time(cue_ptr->cue_start);              /* convert start time */
				sprintf(S4,"%.5s%.2s", asctime( today ) + 11,ampm); /* format start tm*/
				if(S4[0]=='0')
					if(S4[1]=='0')
						{S4[0] = '1'; S4[1] = '2';}
			/*S5 cue stop time */

				if(cue_ptr->cue_stop !=0)       /* if stop time has been entered */
				{

					get_time(cue_ptr->cue_stop);           /* convert stop time */
					sprintf(S5,"%.5s%.2s",asctime( today ) + 11,ampm);  /*format stop time*/
					if(S5[0]=='0')
						if(S5[1]=='0')
							{S5[0] = '1'; S5[1] = '2';}
				}
				else                         /* if no stop time */
				{
				strcpy(S5,"\0");             /* print blank */
				}

			/*S6 cue time used */
				if(cue_ptr->cue_stop != 0)          /* if stop time emtered */
				{
					cue_time_used =  difftime(cue_ptr->cue_stop,cue_ptr->cue_start) ;
										/* compute time used by line */
				}                                     /*    with stop time */
				else                      /* if no stop time */
				{                         /* compute time used with current time */
					cue_time_used = difftime(time(&hstop),cue_ptr->cue_start );
				}
				mins = 0;
				hrs = 0;

				/*_________ convert total seconds to hours,minutes & seconds ________*/
				if (cue_time_used >= 60L)
				{
				   divtm =ldiv( cue_time_used,60L);     /* divide by seconds */
				   mins = divtm.quot;
				   if(mins >= 60L)
				   {
					   divtm = ldiv(mins,60L);      /* divide by minutes */
					   hrs =divtm.quot;
					   mins = divtm.rem;
			   }
				}
/*				if(rent->freeze=='3') S6[0]='\0';
				else*/
				sprintf(S6,"%2ldhr %2ldmn\0",hrs,mins);    /*format time used*/

			/*S7 cue rate */

				sprintf(S7,"%2.2f",cue_ptr->cue_rate );      /*format rate*/

			/*S8 cue amt due */
				 compute_cue_amt();
				 tot_cue_amt += costpp;
				 cue_prt_flds();

		}
	}
	gotoxy(26,18);
	textcolor(f_blue);
	cprintf(" Billed to table # %2d ",rent->table);
	textcolor(f_black);
	sprintf(S9,"%3.2f",tot_cue_amt);
	gotoxy((6-strlen(S9)+62),17);
	cputs(S9);                                                                  gotoxy(49,23);

return 0;
}

cue_prt_flds()
{
gotoxy( 11,cline ); putch(S0);
gotoxy( 12,cline ); cputs(S1);     /*cline starts at 7*/
gotoxy( 18,cline ); cputs(S2);
gotoxy( 24,cline ); cputs(S3);
gotoxy( 30,cline ); cputs(S4);
gotoxy( 38,cline ); cputs(S5);
gotoxy( 46,cline ); cputs(S6);
gotoxy( 56,cline ); cputs(S7);
gotoxy( (6-strlen(S8)+62),cline ); cputs(S8);

return 0;
}
