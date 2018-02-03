#include<graph.h>
#include<time.h>
#include<windows.h>
#include<process.h>
main()
{
pool_dat();
getch();
}
pool_dat()
{
	time_t hdate;
	char buf[26],answ;

	while(1)
	{
		_clearscreen(_GCLEARSCREEN);
		time(&hdate);
		strcpy(buf, asctime (localtime (&hdate)) ) ;
		open_window(8,18,46,15,7,0L,205,7,0);
		_outtext(" Before running this program, the date\n");
		_outtext(" and time must be correct.\n");
		_outtext(" The date and time currently stored in the\n");
		_outtext(" computer is:\n\n ");
		_outtext(buf);
		_outtext(" ---------------------------\n");
		_outtext(" Please note, the time is displayed using\n");
		_outtext(" the 24 hour clock. Ex: 18:00 = 6:00PM.\n\n");

		_outtext(" Is this date and time correct ?\n");
		_outtext(" Enter YES or NO.");
		answ = getch();
		close_window(0);
		if(toupper(answ) == 'Y') break;
		if(toupper(answ) != 'N') continue;
		_settextposition(8,1);
		system("date");
		_outtext("\n\n\n Note: Time must be entered using the 24 hour clock.\n");
		_outtext(" Example: 6:00pm must be entered as 18:00.\n\n");
		system("time");
		}
		execl("poolmain.exe","poolmain.exe",NULL);


}

