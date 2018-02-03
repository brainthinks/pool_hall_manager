

#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
	struct expire_rec
	{
		int expire;
		time_t date;
		time_t cur_date;
		int fill[100];
	}exp_r;
	struct tm work_tm;
	struct tm *wk_ptr = 0;
	char dy[5],mo[5],yr[5],answ[3];

	int e_mo,e_dy,e_yr;
	FILE *fp;
main()
{
	while(1)
	{
		clrscr();
		gotoxy(1,5);
		cputs("   Enter expiration month? ");
		mo[0]=3;
		cgets(mo);
		cputs("\n\n\n\r   Enter expiration day? ");
		dy[0]=3;
		cgets(dy);
		cputs("\n\n\n\r   Enter expiration year? ");
		yr[0]=3;
		cgets(yr);
		cputs("\n\n\n\r   Is the above correct?  Enter Y or N ");
		answ[0]=2;
		cgets(answ);
		if(toupper(answ[2]) =='Y' )
			break;
	}
	cputs("\n\n\r   Place diskette for update of expiration date in drive a:");
	cputs("\n\n\r  Press any key to continue.");
	getch();


							/* E X P I R A T I O N   D A T E  */

	wk_ptr = &work_tm;
	wk_ptr->tm_sec = 0;
	wk_ptr->tm_min = 0;
	wk_ptr->tm_hour = 0;
	wk_ptr->tm_mday = atoi(&dy[2]);           /* day */
	wk_ptr->tm_mon  = (atoi(&mo[2]))-1;           /* month -1 /*
	wk_ptr->tm_year = atoi(&yr[2]);          /* year */
	wk_ptr->tm_wday =0;
	wk_ptr->tm_yday=0;
	wk_ptr->tm_isdst =0;
	exp_r.date = mktime(wk_ptr);
	time(&exp_r.cur_date);
	exp_r.expire=0;
	if(( fp=fopen ("a:\\pool.ovl" ,"w+b") ) != '\0')
	{
		fwrite(&exp_r,100,1,fp);
		fclose(fp);
	}
	else
	{
		if(( fp=fopen ("a:\\pool.ovl" ,"a+b") ) != '\0')
		{
			fwrite(&exp_r,100,1,fp);
			fclose(fp);
		}
		else
		   printf("disk error");
	}
return 0;
}

