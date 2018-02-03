/*Dale & Debbie Grey, home -- 373-5570   business -- 645-3913*/
/************* Main pool program module. ***************************

   Link with pool1s          MAIN MENU
   Link with pool2s          RENTAL MENU
   Link with pool3s          EMPLOYER MENU
   Link with pool4s          PAGE 2 OF RENTAL MENU
   Link with pool_cio        CLOCK TABLES IN/OUT
   Link with pool_clk        DISPLAY RUNNING CLOCK
   Link with pool_csh        MODULE FOR CASH RECIEPTS REPORT
   Link with pool_emp        EMPLOYEE RECORD UPDATE
   Link with pool_lay        SCREEN LAYOUT FOR RENTED TABLES
   Link with pool_na         UPDATE BUSINESS NAME & ADR
   Link with pool_p2         LODGIC FOR SECOND PAGE OF RENTAL MENU
   Link with pool_prt        SET UP PRINT AND DO CALULATIONS-TABLE RENTAL
   Link with pool_pw         PASSWORD MODULES
   Link with pool_rat        UPDATE RATE SCHUDLE
   Link with pool_rex        MISC RATE ROUTINES
   Link with rate_prt        LAYOUT RATE SCHEDULE
   Link with reads           READ ALL KEYBOARD INPUT
*/
#include<graph.h>
#include<time.h>
#include<sys\timeb.h>
#include<stdio.h>
#include<windows.h>
#include<malloc.h>

#define TRUE 1
#define DEBUG 0       /* DEBUG SWITCH 0 = PRODUCTION, 1 = DEBUG */
	char c[2],d='0';
	char store_date[9],t[9] ;
	char emp_pw[5], mang_pw[5];
	char tmpbuf[128], ampm[] = "AM";
	char htime[13],buf[80],emp_nos[3];
	int bypass,page2;
	long *next_avail;
	int inv=0,emp_no=0,x=0,y=0,grp=0;
	int t_sw =0,curr_emp;
	int hcurr_emp,ex_sw;
	time_t ltime;
	struct timeb tstruct;
	struct tm *today;
	struct expire_rec
	{
		int expire;
		time_t date;
		int fill[100];
	}exp_r;
	struct rental           /* MEMORY AREA RECORD LAYOUT ARRAY*/
	{
		int cust;                /*2 BYTES */
		int table;               /*2 BYTES */
		int no_ply;              /*2 BYTES */
		float rate;              /*4 BYTES */
		int employee;            /*2 BYTES */
		int trans;               /*2 BYTES */
		time_t start;            /*4 BYTES */
		time_t stop ;            /*4 BYTES */
		long *prev;              /*4 BYTES */
		char freeze;             /*1 BYTE */
		int new_table;           /*2 BYTES */
		int no_emp;             /* 2 BYTES */
								/*29 TOTAL BYTES */
	}rental_s;
	struct videoconfig video;

	struct bits
		{
		unsigned on:1;
		}bit_tab[51];
	struct  rental *rent;   /* RENTAL RECORD POINTER */
	struct  rental *first_rent;    /* pointer to first record */
	extern struct  employee
	{
		char  name[21];
		char  passw[5];
	} emp[16];

struct rate_rec           /******* rate table record **********/
{
	int from;
	int to;
	int day_of_week;
	long r_start;
	long r_stop;
	float rate[6];
}rate_tab[100] ;
struct rate_rec *rate;      /* pointer to table records */
extern struct emp_cash
{
	int emp_no;
	int code;
	int table;
	time_t start;
	time_t stop;
	float amt;
}e_cash[60];
extern struct emp_cash *csh;

	long idx[51];          /* MEMORY AREA INDEX ARRAY */
	long *index = idx;      /* RENTAL INDEX POINTER */

	long histr[81];         /* MEMORY AREA HISTORY ARRAY */
	long *hist = histr;     /* HISTORY POINTER */
	int fcolor;
	int hcolor;            /* STORE BACK GROUND COLOR */
	int mono;
	int extern curr_emp;
	int extern amt_sw;
	 FILE  *fp, *rate_ptr, *rent_ptr;
	 int h_expire,emp_sw[51];
	 int extern clear_sw,change,tb_no;
	 int ch_p_sw,end_a=0;
	 float credit[51];
main()
{
	ch_p_sw=0;
	change=0;
	clear_sw = 0;
	bypass=1;
	page2 =0;
	amt_sw =0;
/******************** test for video monitor type *****************/
	_getvideoconfig(&video);
	check_video();
/*    printf(" Adapter = %hd  monitor = %hd mode = %hd # colors = %hd  mono = %d  ",video.adapter,video.monitor,video.mode,video.numcolors,mono);
	getch();
*/
/******************** read rate table ****************************/
	read_rate_tab();      /* read rate table */
/*********** ALOCATE MEMORY FOR RENTAL RECORD *********************/
	_setbkcolor(hcolor);
	_clearscreen(_GCLEARSCREEN);
	#if(DEBUG)
	{
	rent = (void *)_fcalloc( sizeof(rental_s) * 20, 1 );
	 if(rent==NULL)
		exit( 1 );
	}
	#else
	{
	rent = (void *)_fcalloc( sizeof(rental_s) * 1000, 1 );
	 if(rent==NULL)
		exit( 1 );
	}
	#endif
	first_rent = rent;
/************ MISC. HOUSE KEEPPING **************************************/
	 open_window(10,20,40,4,fcolor,(long)hcolor,32,fcolor,hcolor);
	_outtext("      Please wait -- retrieving files.");
	(long)next_avail = (long)rent;


			if(( fp=fopen ("a:\\pool.ovl" ,"rb") ) != '\0')
			{
				fread(&exp_r,100,1,fp);
				fclose(fp);
			}
			else {
				_clearscreen(_GCLEARSCREEN);
				printf("\n\nPOOL OVERLAY PROGRAM FILE NOT FOUND\n\nCOPY ORIGINAL FROM DISTRIBUTION DISKETTE.\n\n");
				exit(0); }

	pool_re();            /* RETREIVE EMPLOYEE FILE */
	pool_nar();           /* RETRIEVE NAME & ADDRESS */
	_settextcursor(0x0007);   /* set cursor to full */
	_strdate(store_date) ;         /* get current date */
	close_window(0);
	pool1();       /* call main menu */
}

/****************** PROCESS MAIN MENU ***************************/
pool1()
{
while(1)
{
		pool1s();           /* DISPLAY MAIN MENU */
		c[0]='\0';
		reads(1,c,0,1,0,1);
	switch(c[0])
	{
	/*------------------- SELECTED 1 RENTAL MENU --------------*/
	case  '1':
		{
			 check_expire();
			 pass_wd_e();    /* GET EMPLOYEE PASSWorD*/
			 close_window(1);
			  if (inv != 1)
				 pool2();
			 break;
		}
	/*----------------- SELECTED 2  EMPLOYER MENU ----------------*/
	case '2':
			{

				pass_wd_m();    /* GET EMPLOYER PASSWORD*/
				close_window(1);
				if (inv != 1)
					pool3();
				break;             /* GO EMPLOYER MENU */
			}
	/*----------------- SELECTED 3  EXIT PROGRAM -------------------*/
	case '3':
		{
			yn_mesg("\n    Do you want to exit this program?\n");
			if(ex_sw!=1)
			{
				close_window(1);
				_clearscreen(_GCLEARSCREEN);
				_settextcursor(0x0607);   /* set cursor to norm */
				update_cr();  /* record any left over credits */
				update_exp();    /* update expiring prog */
				yn_mesg("\n  Do you want to update monthly cash receipts ?\n");
				if(ex_sw!=1)
				{
				/*********** update rental records to disk ***************/
					if(( rent_ptr=fopen ("a:\\rent.csh" ,"ab") ) != '\0')
					{
					   rent = first_rent;
					   while(rent->cust > 0)
					   {
						 fwrite(rent,sizeof(rental_s),1,rent_ptr);
						 ++rent;
					   }
						 fclose(rent_ptr);

					}
					else
					_outtext("Disk write error on monthly receipts.");
					/******** update employee records to disk ************/
					csh = e_cash;
					if(( rent_ptr=fopen ("a:\\emp.csh" ,"ab") ) != '\0')
					{
					   while(csh->emp_no > 0)
					   {
						 fwrite(csh,sizeof(e_cash[0]),1,rent_ptr);
						 ++csh;
					   }
						 fclose(rent_ptr);

					}
					else
					_outtext("Disk write error on employee records.");

				}
				_clearscreen(_GCLEARSCREEN);
				exit(0);
			}
		}
	}
	close_window(0);
}                    /*LOOP IF INCORRECT KEY ENTERED*/
}
/********************PROCESS RENTAL MENU**************************/
pool2()
{

while(1)
{
	   _settextcursor(0x2000);   /* set cursor off */
		pool2s();         /* DISPLAY RENTAL MENU*/
						  /* PRINT TIME WHILE WAITING ON KEYBOARD*/
		while(1)
		{
			prt_time();       /* READ KEY FROM RENTAL MENU */
			if( c[0]=getch() ) break;
			getch();
		 }
	   _settextcursor(0x0007);   /* set cursor to full */

	switch(toupper(c[0]))
	{
	/*------------------- SELECTED 1 CLOCK IN/OUT -----------------*/
	case '1':
		{
			pool_cio();
			break;
		}
	/*----------- SELECTED 2 UPDATE NUMBER OF PLAYERS --------------*/
	case '2':
		{
			pool_udp();
			break;
		}
	/*------------------- SELECTED 3 REVIEW TABLE -----------------*/
	case '3':
		{
			pool_rev();
			break;
		}
	/*------------------- SELECTED 4 RESTART TABLE -----------------*/
	case '4':
		{
			pool_restart();
			break;
		}
	/*------------------- SELECTED 5 CHANGE TABLE NO. -----------------*/
	case '5':
			{
				pool_tab();
				break;
			}
	/*------------------- SELECTED 6 CHANGE PASS WORD. -----------------*/
	case '6':
			{
				hcurr_emp = curr_emp;
				_settextposition(23,52); /* turn off generated cursor */
				_outtext(" ");
				open_window(4,6,67,3,fcolor,(long)hcolor,196,fcolor,hcolor);
				_outtext("If you have made the wrong selection press return or enter key.");
				pass_wd_e();
				close_window(1);
				if(curr_emp >15)         /* reached end of table */
					curr_emp = hcurr_emp;
				if (hcurr_emp != curr_emp)
					pw_changed();
				break;
			}
	/*------------------- SELECTED 7 EMPLOYER MENU ----------------*/
	case '7':
		 {
			break;
		 }
	/*------------------- SELECTED 8 EMPLOYER MENU ----------------*/
	case '8':
			{
			_settextposition(23,52); /* turn off generated cursor */
			_outtext(" ");
			open_window(5,6,67,3,fcolor,(long)hcolor,196,fcolor,hcolor);
			_outtext("If you have made the wrong selection press return or enter key.");

			d=c[0];
			pass_wd_m();     /* GET EMPLOYER PASSWORD*/
			close_window(1);
			if (inv == 1) break;
			process_auto_rate();
			pool3();    /*GO EMPLOYER MENU*/
			break;
			}
	/*------------------- SELECTED 9 MAIN MENU-----------------------*/
	case '9':
		{
			x=0;
			ex_sw =1;
			while(x<50)
			{
				x+=1;
				if(bit_tab[x].on) { err_msg(9); ex_sw =0; break; }
			}
			if(!ex_sw) break;
			sign_out();
			return(0);
		}
	/****************** SELECTED A additional menu ********************/
	case  'A':
		{
		while(1)
		{
		   _settextcursor(0x2000);   /* set cursor off */
			pool4();        /* print 2nd page of menu */
						 /* PRINT TIME WHILE WAITING ON KEYBOARD*/
			while(1)
			{
				prt_time();       /* READ KEY FROM RENTAL MENU */
				if( c[0]=getch() ) break;
				getch();
			}
			switch(c[0])
			{
			/*--------- clear cash recpt (1) ----------------------------*/
			case '1':
				{
					pool_clr();
					end_a=1;
					break;
				}
			/*---------- time credit (2) ----------------------------------*/
			case '2':
				{
					pool_cr();
					end_a=1;
					break;
				}
			/*---------- change start time (3) -----------------------------*/
				case '3':
				{
					pool_str();
					end_a=1;
					break;
				}
			/*----------- change incorrect # of players (4) ---------------------------*/
			case '4':
				{
				ch_p_sw = 1;
				pool_udp();
				ch_p_sw =0;
				end_a=1;
				break;
				}
			/*----------- clock in employee (5) ---------------------------*/
			case '5':
				{
					pool_emp();
					end_a=1;
					break;
				}
			/*----------- promotional rates (6) ---------------------------*/
			case '6':
				{
				end_a=1;
				break;
				}
			/*----------- return to page 1 (7) ---------------------------*/
			case '7':
				{
				end_a =1;
				break;
				}

			}
		pool2s();
		if(end_a){end_a =0; break;}
		}
		}

	}
}
}
/******************** PROCESS EMPLOYER MENU ************************/
pool3()
{
while(1)
{
	_settextcursor(0x0007);   /* set cursor to full */
	pool3s();           /*DISPLAY EMPLOYER MENU*/
	c[0]='\0';
	reads(1,c,0,1,0,1);
	_settextcolor(fcolor);

	switch(c[0])
	{
	/*------------------- SELECTED 1 CASH RECEIPTS -------------------*/
	case '1':
		{
			cash();
			break;
		}
	/*------------------- SELECTED 2 UPDATE EMPLOYEE RECORDS ----------*/
	case '2':
		{
			_settextcursor(0x0607);   /* set cursor to normal */
			update_emp();   /*GO UPDATE EMPLOYEE RECORDS*/
			pool_we();      /*GO WRITE RECORDS TO DISKETTE*/
			break;
		}
	/*------------------- SELECTED 3 ENTER NAME & ADDRESS--------*/
	case '3':
		{
			_settextcursor(0x0607);   /* set cursor to normal */
			pool_naw();       /*UPDATE NAME AND ADDRESS*/
			break;
		}
	/*------------------- SELECTED 4 UPDATE RATE TABLE  -----------------*/
	case '4':
	   {
			_settextcursor(0x0607);   /* set cursor to norm */
			#if DEBUG ==0
				read_rates();
			#endif
			read_rate_tab();
			break;
	   }
	/*------------------- SELECTED 5 MAIN MENU -----------------*/
	case '5':
		 return(0);
	}
}
}
/**************** END OF FUNCTION MAIN ******************/
check_expire()
{
	time_t cur_date;
	int tm_c_er;
			if(( fp=fopen ("a:\\pool.ovl" ,"r+b") ) != '\0')
			{
				fclose(fp);
			}
			else exit(0);

	while(exp_r.expire>0)                /*check count of runs past expire */
	{
		if(exp_r.expire > 2)
		{
			_clearscreen(_GCLEARSCREEN);
			open_window(10,10,60,5,fcolor,(long)hcolor,205,fcolor,hcolor);
			_outtext("\n Your program has expired. Contact the software developer.");
			getch();
			fflush( stdin );
			close_window(0);
			exit(0);
		}
		else
		{
			open_window(10,10,60,5,fcolor,(long)hcolor,205,fcolor,hcolor);
			_outtext("\n Your program will expire. Contact the software developer.");
			getch();
			fflush( stdin );
			close_window(0);
		}
		return(0);
	}
	time(&cur_date);
	if(cur_date > exp_r.date)                   /* compare dates */
	{
		if(exp_r.expire == 0 )
		 {
		   exp_r.expire=1;
			if(( fp=fopen ("a:\\pool.ovl" ,"r+b") ) != '\0')
			{
				fwrite(&exp_r,100,1,fp);
				fclose(fp);
			}
			else {
				printf("disk write error"); exit(0); }
		}
	}
}
update_exp()
{
	if(exp_r.expire>0)                /*check count of runs past expire */
	{
		exp_r.expire +=1;
		if(( fp=fopen ("a:\\pool.ovl" ,"r+b") ) != '\0')
		{
			fwrite(&exp_r,100,1,fp);
			fclose(fp);
		}
		else
		   printf("disk write error");
	 }
}
/************************* GET TIME **********************/
get_time( long  buf)
{
		today = localtime(&buf );
		strcpy( ampm, "AM");
		if( today->tm_hour >= 12 )    strcpy( ampm, "PM" );
		if( today->tm_hour > 12 )     today->tm_hour -= 12;
}
/**************** READ RATE TABLE **************************************/
read_rate_tab()
{
	rate = rate_tab;
	memset(rate,'\0',sizeof(rate_tab));
	if(( rate_ptr=fopen ("a:\\rate.tab" ,"rb") ) != '\0')
	{

		fread(rate,sizeof(rate_tab),1,rate_ptr);
		fclose(rate_ptr);
	}
	else       /* no table available */
	{
		#if DEBUG == 0
			read_rates();
		#endif
		rate = rate_tab;
		if(( rate_ptr=fopen ("a:\\rate.tab" ,"rb") ) != '\0')
		{
			fread(rate,sizeof(rate_tab),1,rate_ptr);
			fclose(rate_ptr);
		}
	}
}
/*********************** check video adapter ***************************/
check_video()
{
	if(video.adapter == 1)    /* test for mono adapter */
	{
		mono = 1;         /* set switch = B & W monitor */
		fcolor = 7;       /* WHITE */
		hcolor = 0;       /* BLACK */
	}
	else
	{
		mono = 0;   /* set switch to color adapter */
		if(video.monitor == 1 || video.monitor == 8 )
		{
			hcolor = 0;       /* B & W monitor */
			fcolor = 7;
		}
		else
		{
			if(video.mode == 1 || video.mode == 3 || video.mode == 4)
			{                    /* color monitor */
				hcolor = 1;      /* BLUE */
				fcolor = 7;      /* WHITE */
			}
			else
			{
				mono = 1;
				hcolor = 0;       /* B & W monitor */
				fcolor = 7;
			}
		}
	}
}
/********************* yes and no mesg *******************************/
yn_mesg(char mesg[78])
{
	char c[2];
	ex_sw =0;
	while(1)
	{
		open_window(10,(80-strlen(mesg)+2)/2,strlen(mesg)+2,4,fcolor,(long)hcolor,205,fcolor,hcolor);
		_settextcolor(fcolor+8);
		_outtext(mesg);
		_outtext("  Press 'N' for no, 'Y' for yes");
		_settextcolor(fcolor);
		c[0]='\0';
		reads(1,c,0,1,0,0);
		close_window(0);
		if(toupper(c[0]) == 'Y')  break;
		if(toupper(c[0]) == 'N') { ex_sw =1; break; }
	}
}

/***************** get_times ***************************************/
get_times(char *buf,int * h_hr,int * h_mn,int *r_row,int *col_no,int err_cd,int (*time_err)(int))
{

	int x,am,pm,cd;

	while(1)
	{

		_settextposition( *r_row,*col_no );

		if( read_str(7,buf,1,1,1,0))return(1) ;

		if(buf[6] != 'M')       /* last position = M */
		{                       /* no - shift right 1 byte */
		for(x=7;x>0;buf[x]=buf[x-1],x--);
		buf[0]='0';
		}
		if(buf[2] != ':')
		{
			(*time_err)(err_cd);
			continue;
		}
		am=1;
		pm=1;
		am=  strcmp(&buf[5],"AM");
		pm=  strcmp(&buf[5],"PM");
		if (am)
			if(pm)
			{
				(*time_err)(err_cd);
				continue;
			}
		buf[2]=0;
		if(!isdigit(buf[0])) {(*time_err)(err_cd);  continue;}
		if(!isdigit(buf[1])) {(*time_err)(err_cd);  continue;}
		if(!isdigit(buf[3])) {(*time_err)(err_cd);  continue;}
		if(!isdigit(buf[4])) {(*time_err)(err_cd);  continue;}
		x=0;
		*h_hr = atol(buf);
		if (*h_hr > 12)
		{
			(*time_err)(err_cd);
			continue;
		}
		if(!pm & *h_hr < 12 ) *h_hr+=12;    /* add 12 to all pm's but 12:00pm */
		if(!am & *h_hr == 12 ) *h_hr=24;   /* add 12 to 12:00am */

		*h_mn = atoi(&buf[3]);

		if (*h_mn > 59)
		{
			(*time_err)(err_cd);
			continue;
		}

		break;
	}
	return(0);
}
/*************** call read string function ***********************/
read_str(int a,char *buf,int b,int c,int d,int e)
{
	#if DEBUG == 1
		int  ctl_key;
	 struct rate_rec *tab;      /* pointer to rate records */
	 struct rate_rec *next_tab; /* pointer to next available blank record */

	#else
		int extern ctl_key;
		extern struct rate_rec *tab;      /* pointer to rate records */
		extern struct rate_rec *next_tab; /* pointer to next available blank record */

	#endif

	ctl_key = reads(a,buf,b,c,d,e) ;

	if(ctl_key == 'H' || ctl_key == 'D' || ctl_key == ';' || ctl_key == 'B')
		if(tab==next_tab) return(1);
	if(tab==next_tab)
		if( buf[0]=='\0')
			if( ctl_key=='K')
				return(1);
	return(0);
}
