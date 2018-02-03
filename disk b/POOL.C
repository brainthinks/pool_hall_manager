#include<conio.h>
#include<time.h>
#include<ctype.h>
#include<string.h>
#include<windows.h>
#include<process.h>

main()
{
pool_dat();
getch();
return 0;
}
pool_dat()
{
	time_t hdate;
	char buf[26],answ;

	while(1)
	{
		clrscr();
		time(&hdate);
		strcpy(buf, asctime (localtime (&hdate)) ) ;
		open_window(8,18,46,15,7,0,205,7,0);
		cputs(" Before running this program, the date\n\r");
		cputs(" and time must be correct.\n\r");
		cputs(" The date and time currently stored in the\n\r");
		cputs(" computer is:\n\r\n\r ");
		cputs(buf);
		cputs(" \r---------------------------\n\r");
		cputs(" Please note, the time is displayed using\n\r");
		cputs(" the 24 hour clock. Ex: 18:00 = 6:00PM.\n\r\n\r");

		cputs(" Is this date and time correct ?\n\r");
		cputs(" Enter YES or NO.");
		answ = getch();
		close_window(0);
		if(toupper(answ) == 'Y') break;
		if(toupper(answ) != 'N') continue;
		gotoxy(1,8);
		system("date");
		cputs("\n\r\n\r\n\r Note: Time must be entered using the 24 hour clock.\n\r");
		cputs(" Example: 6:00pm must be entered as 18:00.\n\r\n\r");
		system("time");
	}
	execl("poolmain.exe","poolmain.exe",0);

return 0;
}

