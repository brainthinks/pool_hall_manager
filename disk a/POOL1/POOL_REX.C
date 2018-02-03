/*
	THIS MODULE CONTAINS MISC SUPPORT FUNCTIONS FOR THE POOL_RAT MODULE
*/
#include<stdio.h>
#include<graph.h>
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
extern struct rate_rec *tab;      /* pointer to table records */
extern struct rate_rec *next_tab;
FILE *rate_ptr;
int sort_sw;

/****************** SORT work RATE TABLE **************************/
rate_sort()
{
	sort_sw=1;
	while(sort_sw)
	{
		tab= rate_tab;
		memcpy(&store,tab++,sizeof(rate_tab[0]));
		sort_sw=0;
		while(store.day_of_week >0)
		{
			   while(tab->day_of_week >0)
			{
				if(tab->from<store.from)
				{
					move();
					continue;
				}
				 if(tab->from>store.from)
				 {
					save();
					continue;
				 }

				if(tab->day_of_week<store.day_of_week)
				{
					move();
					continue;
				}
				 if(tab->day_of_week>store.day_of_week)
				 {
					save();
					continue;
				 }
				 if(tab->r_start < store.r_start)
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
}
move()
{
	memcpy(tab-1,tab,sizeof(rate_tab[0]));
	++tab;
	sort_sw=1;
}

save()
{

	memcpy(tab-1,&store,sizeof(rate_tab[0]));
	memcpy(&store,tab++,sizeof(rate_tab[0]));
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
}
move3()
{
	memcpy(tab3-1,tab3,sizeof(rate_tab[0]));
	++tab3;
	sort_sw=1;
}

save3()
{

	memcpy(tab3-1,&store,sizeof(rate_tab[0]));
	memcpy(&store,tab3++,sizeof(rate_tab[0]));
}

/******************** write updated rates to disk *********************/
data_out()
{
	rate_sort3();
	tab3=rate_tab3;
	if(tab3->day_of_week < 1)   /* if no entries - delete disk file */
	{
	system("del a:rate.tab");
	}
	else
	{

		if(( rate_ptr=fopen ("a:\\rate.tab" ,"wb") ) != '\0')
		{
			fwrite(tab3,sizeof(rate_tab),1,rate_ptr);
			fclose(rate_ptr);
		}
		else
		{
			printf("disk write error");
			exit(0);
		}
	}
}

/***************** read rates table from disk ************************/
data_in()
{
	int extern r_row,ctl_key;


	tab2=rate_tab2;
	if(( rate_ptr=fopen ("a:\\rate.tab" ,"rb") ) != '\0')
	{
		fread(tab2,sizeof(rate_tab),1,rate_ptr);
		fclose(rate_ptr);
	}
	else
		return(1);
}
/******************** edit table rates ***************************/
edit_rates()
{
	int ck_sw =0;

	tab=rate_tab;
	if(tab->day_of_week != 1) { tb_err(1); return(0); }
	if(tab->r_start != 0000L) { tb_err(2) ; return(0);}
	if(!tab->r_stop > tab->r_start) { tb_err(4); return(0); }
	if(tab->r_stop != 2400L) ck_sw = 1;
	if((tab+1)->day_of_week==1)  ck_sw = 1;
	++tab;
	while(1)                /* TEST 'DE' RECORD TIMES */
	{
		if (ck_sw == 1)
		{
			if(tab->day_of_week != 1) { tb_err(2); return(0); }
			if(tab->r_start != (tab-1)->r_stop) { tb_err(3); return(0); }
			if(!tab->r_stop > tab->r_start) { tb_err(4); return(0); }
			if(tab->r_stop == 2400L && (tab+1)->day_of_week!=1)
				{ck_sw = 0; ++tab; break; }
			++tab;
			continue;
		}
		break;
	}

	while(1)          /*  test  remaining days of week */
	{
		if(!tab->day_of_week > 0) break;
			if(!tab->r_stop > tab->r_start) { tb_err(4); return(0); }
			 if(tab->day_of_week ==   (tab-1)->day_of_week)
				if(tab->r_start < (tab-1)->r_stop) { tb_err(5); return(0); }
			++tab;
			continue;
	}
	return(1);
}
/**************** rate table errors ****************************/
tb_err(int x)
{
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
	open_window(1,(80-strlen(err_buf)+2)/2,strlen(err_buf)+2,5,fcolor,(long)hcolor,32,hcolor,fcolor);
	_settextposition(1,((strlen(err_buf)+2) - strlen("E R R O R  !!"))/2);
	_outtext("E R R O R  !!");
	_settextposition(2,((strlen(err_buf)+2) - strlen(err_buf))/2);
	_outtext(err_buf);
	_settextposition(3,((strlen(err_buf)+2) - strlen(press_any))/2);
	_outtext(press_any);
	getch();
	fflush( stdin );
	close_window(0);
	_settextwindow(7,3,19,76);
}
