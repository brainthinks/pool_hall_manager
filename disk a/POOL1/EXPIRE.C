#include<time.h>
#include<stdio.h>
	struct expire_rec
	{
		int expire;
		time_t date;
	}exp_r;
	struct tm work_tm;
	struct tm *wk_ptr = 0;

	FILE *fp;
main()
{

	wk_ptr = &work_tm;
	wk_ptr->tm_sec = 0;
	wk_ptr->tm_min = 0;
	wk_ptr->tm_hour = 0;
	wk_ptr->tm_mday = 1;
	wk_ptr->tm_mon  = 0;
	wk_ptr->tm_year = 91;
	wk_ptr->tm_wday =0;
	wk_ptr->tm_yday=0;
	wk_ptr->tm_isdst =0;
	exp_r.date = mktime(wk_ptr);


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
}

