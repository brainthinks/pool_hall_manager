#include<stdio.h>
#include<time.h>
#include<graph.h>
	struct rental           /* MEMORY AREA RECORD LAYOUT ARRAY*/
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
	}rental_s[1];
	struct rental *rent;
	struct tm *today;
	char hstart[8],hstop[8],ampm[3];
	FILE  *rent_ptr;
main()
{
	rent = rental_s;
	_clearscreen(_GCLEARSCREEN);

	if(( rent_ptr=fopen ("a:\\rent.csh" ,"rb") ) != '\0')
	{

	   do
	   {
	  if((   fread(rent,sizeof(rental_s),1,rent_ptr)) ==0)  break;
	  else
		 get_time(rent->start);
		sprintf(hstart,"%.5s%.2s", asctime( today ) + 11,ampm); /* format start tm*/
		if(hstart[0]=='0')
			if(hstart[1]=='0')
				{hstart[0] = '1'; hstart[1] = '2';}
		 get_time(rent->stop);
		sprintf(hstop,"%.5s%.2s", asctime( today ) + 11,ampm); /* format start tm*/
		if(hstop[0]=='0')
			if(hstop[1]=='0')
				{hstop[0] = '1'; hstop[1] = '2';}


		 printf("%3d  %2d  %1d  %3.2f  %1d %1d  %7s  %7s  %1c  %2d  %1d\n",\
			   rent->cust,rent->table,rent->no_ply,rent->rate,rent->employee,\
			   rent->trans,hstart,hstop,rent->freeze,rent->new_table,rent->no_emp);


		 }
	   while(rent->cust > 0);

		 fclose(rent_ptr);

	}
	else
	_outtext("Disk write error on monthly receipts.");

}
get_time( long  buf)
{
		today = localtime(&buf );
		strcpy( ampm, "AM");
		if( today->tm_hour >= 12 )    strcpy( ampm, "PM" );
		if( today->tm_hour > 12 )     today->tm_hour -= 12;

}
