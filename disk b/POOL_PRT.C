/*
	THIS MODULE SETS UP, WITH CALCULATIONS, THE TABLE RENTAL SCREEN
*/
#include<conio.h>
#include<stdlib.h>
#include<time.h>

char htrans[] = "              ";


	char extern F1[3];           /*   table   */
	char extern F2[9];           /*   start   */
	char extern F3[9];           /*   stop    */
	char extern F4[12];          /*   used    */
	char extern F5[3];           /*   # of players */
	char extern F6[6];           /*   rate    */
	char extern F7[10];          /*   total cost (line) */
	char extern F8[7];           /*   per player cost (line)  */
	char extern F9[11];          /*   trans   */
	char extern F15[2];          /* no of employees */
	extern struct tm *today;
	char extern ampm[3];
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
		long prev;
		char freeze;
		int new_table;
		int no_emp;
	}rental_s;

	extern struct  rental *rent;   /* RENTAL RECORD POINTER */
	long extern idx[12000];        /* MEMORY AREA INDEX ARRAY */
	long extern  *index;     /* INDEX POINTER */
	long extern next_avail;
	long extern histr[81];         /* MEMORY AREA HISTORY ARRAY */
	long extern *hist ;     /* HISTORY POINTER */
	int extern line,bypass;
	int extern clear_sw;
	int extern emp_sw[51],tb_no;
prt_detail()
{
	float thre =3600;
	int xx,nickel=0;
	char  *stopstring;
	char far *pdest;
	char tb_nos[3],s_players[3];
	long t_used;
		long hstop,hrs,mins;
		ldiv_t  divtm;
		float extern t_cost;
		float cost_pp;
		float t_cost_l,sec_rate,t_sec;

	/*F1 TABLE # */
		sprintf(F1,"%2d\0",rent->table);      /* format table no. */

	/*F2 START TIME */
		get_time(rent->start);              /* convert start time */
		sprintf(F2,"%.5s%.2s", asctime( today ) + 11,ampm); /* format start tm*/
		if(F2[0]=='0')
			if(F2[1]=='0')
				{F2[0] = '1'; F2[1] = '2';}

	/*F3 STOP TIME */
		if(rent->stop >0L)                  /* if stop time has been entered */
		{
			get_time(rent->stop);           /* convert stop time */
			sprintf(F3,"%.5s%.2s",asctime( today ) + 11,ampm);  /*format stop time*/
			if(F3[0]=='0')
				if(F3[1]=='0')
					{F3[0] = '1'; F3[1] = '2';}
		}
		else                         /* if no stop time */
		{
		strcpy(F3,"\0");             /* print blank */
		}

	/*F4 TIME USED */
		if(rent->stop > 0L)          /* if stop time emtered */
		{
			t_used =  difftime(rent->stop,rent->start) ;     /* compute time used by line */
		}                                          /*    with stop time */
		else                      /* if no stop time */
		{                         /* compute time used with current time */
			t_used = difftime(time(&hstop),rent->start );
		}
		mins = 0;
		hrs = 0;

		/*_________ convert total seconds to hours,minutes & seconds ________*/
		if (t_used >= 60L)
		{
		   divtm =ldiv( t_used,60L);     /* divide by seconds */
		   mins = divtm.quot;
		   if(mins >= 60L)
		   {
			   divtm = ldiv(mins,60L);      /* divide by minutes */
			   hrs =divtm.quot;
			   mins = divtm.rem;
		   }
		}
		if(rent->freeze=='3') F4[0]='\0';
		else
		sprintf(F4,"%2ld hr %2ld mn\0",hrs,mins);    /*format time used*/

	/*F5 # OF PLAYERS */
		sprintf(F5,"%1d\0",rent->no_ply );                    /*format no players*/

	/*F15 # OF EMPLOYEES */
		sprintf(F15,"%1d",rent->no_emp);

	/*F6 RATE */
		sprintf(F6,"%2.2f\0",rent->rate );                  /*format rate*/

	/*F7 AMOUNT DUE (line) & F8 COST PER PLAYER (LINE) */
		sec_rate = rent->rate / thre;       /* compute rate per second */
		t_cost_l =  (sec_rate * t_used);
		cost_pp = (t_cost_l / rent->no_ply);
		sprintf(F8,"%3.2f",cost_pp);        /* load edit field */
		for(xx=0;F8[xx]!='.';xx++);
		/*_____________ round to nearest nickel ___________________*/
		if(F8[xx+2] == '0');
		else
		{
			if(F8[xx+2] > '0' && F8[xx+2] < '6') F8[xx+2]= '5';
					else  { F8[xx+2]  = '0'; nickel = 1;}
		}
		cost_pp = atof(F8);                 /* convert to two deimal places */
		if (nickel == 1) { cost_pp += .10; nickel = 0; }
										/* tot cost = player cost * no players */
		/*_____________________________________________________________*/
		sprintf(F8,"%3.2f",cost_pp);        /* load print field */
		t_cost_l = cost_pp * (rent->no_ply - rent->no_emp) ;
		sprintf(F7,"%3.2f",t_cost_l);       /* load print field */
		t_cost_l = atof(F7);                /* convert to two decimal places */
		if(!clear_sw && rent->freeze < '2')
			t_cost += t_cost_l;
		if(rent->freeze == '3'){ F7[0] = '\0'; F8[0] = '\0'; }
	/*F9  TRANSACTION CODE */
		trans_cd();
		sprintf(F9,"%s\0",htrans );                     /*format trans code*/
		if(bypass)
		{
			gotoxy( 4,line ); cputs(F1);
			gotoxy( 8,line ); cputs(F2);
			gotoxy( 16,line ); cputs(F3);
			gotoxy( 25,line ); cputs(F4);
			gotoxy( 39,line ); cputs(F5);
			if(rent->freeze == '3')
			{
				gotoxy( 43,line );
				cputs("Deleted see next line.");
			}
			else
			{
				gotoxy( 43,line ); cputs(F6);
				gotoxy( 50,line ); cputs(F7);
				gotoxy( 59,line ); cputs(F8);
			}
			gotoxy( 66,line ); cputs(F9);
		if(rent->no_emp)
			   { gotoxy( 78,line ); cputs(F15);}
		}

	/*    cputs(" %d",rent->employee);    used for testing */
		return(0);
}
/***************** Transaction code lookup ************************/
trans_cd()
{
	strcpy(htrans,"          ");
	switch(rent->trans)
	{
		case  1:
			{
			strcpy(htrans,"START");
			break;
			}
		case  2:
			strcpy(htrans,"PLAYERS");
			break;
		case 3:
			strcpy(htrans,"TABLE");
			break;

		case 4:
			strcpy(htrans,"RE-START");
			break;

		case 5:
			strcpy(htrans,"EMPLOYEE");
			break;

		case 6:
			strcpy(htrans,"CORRECTED");
			break;
		case 7:
			strcpy(htrans,"RATE-CHNG");
			break;
		case 8:
			strcpy(htrans,"EMP-CHNG");
			break;

	 }
return 0;
}

