/*
	THIS MODULE CONTAINS MISC SUPPORT FUNCTIONS FOR THE POOL_RAT MODULE
*/
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
extern struct rate_rec           /******* rate table record **********/
{
	int from;
	int to;
	int day_of_week;
	long r_start;
	long r_stop;
	float rate[6];
}rate_tab[100] ;
extern struct rate_rec2           /******* input rate table record **********/
{
	int from;
	int to;
	int day_of_week;
	long r_start;
	long r_stop;
	float rate[6];
}rate_tab2[100] ;
extern struct rate_rec3       /******* output rate table record **********/
{
	int from;
	int to;
	int day_of_week;
	long r_start;
	long r_stop;
	float rate[6];
}rate_tab3[100] ;

struct rate_store   /******* rate table record **********/
{
	int from;
	int to;
	int day_of_week;
	long r_start;
	long r_stop;
	float rate[6];

}store ;
extern struct rate_rec3 *tab3;      /* pointer to table records */
extern struct rate_rec3 *h_tab3;      /* pointer to table records */

extern struct rate_rec2 *tab2;      /* pointer to table records */
extern struct rate_rec *ttab;      /* pointer to table records */
extern struct rate_rec *next_tab;
FILE *rate_ptr2;
int sort_sw;

/****************** SORT work RATE TABLE **************************/
rate_sort()
{
	sort_sw=1;
	while(sort_sw)
	{
		ttab= rate_tab;
		memcpy(&store,ttab++,sizeof(rate_tab[0]));
		sort_sw=0;
		while(store.day_of_week >0)
		{
			   while(ttab->day_of_week >0)
			{
				if(ttab->from<store.from)
				{
					move();
					continue;
				}
				 if(ttab->from>store.from)
				 {
					save();
					continue;
				 }

				if(ttab->day_of_week<store.day_of_week)
				{
					move();
					continue;
				}
				 if(ttab->day_of_week>store.day_of_week)
				 {
					save();
					continue;
				 }
				 if(ttab->r_start < store.r_start)
				 {
					move();
					continue;
				 }
				 else
				 {
					save();
					continue;
				 }

			 }
			 save();
			 break;
		 }
	}
return 0;
}
move()
{
	memcpy(ttab-1,ttab,sizeof(rate_tab[0]));
	++ttab;
	sort_sw=1;
return 0;
}

save()
{

	memcpy(ttab-1,&store,sizeof(rate_tab[0]));
	memcpy(&store,ttab++,sizeof(rate_tab[0]));
return 0;
}
/****************** SORT output RATE TABLE **************************/
rate_sort3()
{
	sort_sw=1;
	while(sort_sw)
	{
		tab3= rate_tab3;
		memcpy(&store,tab3++,sizeof(rate_tab[0]));
		sort_sw=0;
		while(store.day_of_week >0)
		{
			   while(tab3->day_of_week >0)
			{
				if(tab3->from<store.from)
				{
					move3();
					continue;
				}
				 if(tab3->from>store.from)
				 {
					save3();
					continue;
				 }

				if(tab3->day_of_week<store.day_of_week)
				{
					move3();
					continue;
				}
				 if(tab3->day_of_week>store.day_of_week)
				 {
					save3();
					continue;
				 }
				 if(tab3->r_start < store.r_start)
				 {
					move3();
					continue;
				 }
				 else
				 {
					save3();
					continue;
				 }

			 }
			 save3();
			 break;
		 }
	}
return 0;
}
move3()
{
	memcpy(tab3-1,tab3,sizeof(rate_tab[0]));
	++tab3;
	sort_sw=1;
return 0;
}

save3()
{

	memcpy(tab3-1,&store,sizeof(rate_tab[0]));
	memcpy(&store,tab3++,sizeof(rate_tab[0]));
return 0;
}

/******************** write updated rates to disk *********************/
data_out()
{
	rate_sort3();
	tab3=rate_tab3;
	if(tab3->day_of_week < 1)   /* if no entries - delete disk file */
	{
	system("del rate.tab");
	}
	else
	{

		if(( rate_ptr2=fopen ("rate.tab" ,"wb") ) != '\0')
		{
			fwrite(tab3,sizeof(rate_tab),1,rate_ptr2);
			fclose(rate_ptr2);
		}
		else
		{
			printf("disk write error");
			exit(0);
		}
	}
return 0;
}

/***************** read rates table from disk ************************/
data_in()
{
	int extern r_row,ctl_key;


	tab2=rate_tab2;
	if(( rate_ptr2=fopen ("rate.tab" ,"rb") ) != '\0')
	{
		fread(tab2,sizeof(rate_tab),1,rate_ptr2);
		fclose(rate_ptr2);
	}
	else
		return(1);
return 0;
}
/******************** edit table rates ***************************/
edit_rates()
{
	int ck_sw =0;

	ttab=rate_tab;
	if(ttab->day_of_week != 1) { tb_err(1); return(0); }
	if(ttab->r_start != 0000L) { tb_err(2) ; return(0);}
	if(!ttab->r_stop > ttab->r_start) { tb_err(4); return(0); }
	if(ttab->r_stop != 2400L) ck_sw = 1;
	if((ttab+1)->day_of_week==1)  ck_sw = 1;
	++ttab;
	while(1)                /* TEST 'DE' RECORD TIMES */
	{
		if (ck_sw == 1)
		{
			if(ttab->day_of_week != 1) { tb_err(2); return(0); }
			if(ttab->r_start != (ttab-1)->r_stop) { tb_err(3); return(0); }
			if(!ttab->r_stop > ttab->r_start) { tb_err(4); return(0); }
			if(ttab->r_stop == 2400L && (ttab+1)->day_of_week!=1)
				{ck_sw = 0; ++ttab; break; }
			++ttab;
			continue;
		}
		break;
	}

	while(1)          /*  test  remaining days of week */
	{
		if(!ttab->day_of_week > 0) break;
			if(!ttab->r_stop > ttab->r_start) { tb_err(4); return(0); }
			 if(ttab->day_of_week ==   (ttab-1)->day_of_week)
				if(ttab->r_start < (ttab-1)->r_stop) { tb_err(5); return(0); }
			++ttab;
			continue;
	}
	return(1);
}
/**************** rate table errors ****************************/
tb_err(int x)
{
	int extern b_red,b_black,b_yellow,b_white,b_grey,b_cyan,b_blue,b_bwhite;
	int extern b_green,b_lblue,b_lcyan,b_lmagenta,b_lgreen,b_lred,b_brown;
	int extern f_red,f_black,f_yellow,f_white,f_grey,f_cyan,f_blue,f_bwhite;
	int extern f_green,f_lblue,f_lcyan,f_lmagenta,f_lgreen,f_lred,f_brown;

	int extern fcolor;
	char press_any[] = {"Press any key to continue."};
	char err_buf[80];
	int extern hcolor ;
	switch (x)
	{
		case 1:
			strcpy(err_buf,"There are no default entries. After pressing any key, Press F1 for help.");
			break;
		case 2:
			strcpy(err_buf,"DEFAULT times must cover a total 24 hour day, From 00:00AM to 12:00AM.");
			break;

		case 3:
			strcpy(err_buf,"DEFAULT start times must be the same as previos stop time.");
			break;
		case 4:
			strcpy(err_buf,"Stop time must be later than start time.");
			break;
		case 5:
			strcpy(err_buf,"Start time prior to previos stop time for same day.");
			break;

	}
	open_window(1,(80-strlen(err_buf)+2)/2,strlen(err_buf)+2,5,\
				f_yellow,b_red,32,b_red,f_red);
	gotoxy(((strlen(err_buf)+2) - strlen("E R R O R  !!"))/2,1);
	cputs("E R R O R  !!");
	gotoxy(((strlen(err_buf)+2) - strlen(err_buf))/2,2);
	cputs(err_buf);
	gotoxy(((strlen(err_buf)+2) - strlen(press_any))/2,3);
	cputs(press_any);
	getch();
	fflush( stdin );
	close_window(0);
	window(3,7,76,19);
	textcolor(fcolor);
	textbackground(hcolor);
return 0;
}
