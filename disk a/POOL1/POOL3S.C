/*
		THIS MODULE DISPLAYS THE EMPLOYER MENU
*/
#include<graph.h>

int extern fcolor;
/******************** PRINT EMPLOYER MENU *************************/
pool3s()
{
	int  extern hcolor;
	_clearscreen(_GCLEARSCREEN);
	_setbkcolor((long)fcolor);
	_settextcolor(hcolor);
	_settextposition(5,15);
	_outtext("旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커");
	_settextposition(6,15);
	_outtext("�       M A N A G E M E N T     M E N U          �");
	_settextposition(7,15);
	_outtext("읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸");
	_setbkcolor((long)hcolor);
	_settextcolor(fcolor);
	_settextposition(10,15);
	_outtext("    1. Review daily rental cash receipts.");
	_settextposition(12,15);
	_outtext("    2. Assign employee passwords.");
	_settextposition(14,15);
	_outtext("    3. Enter your business' name & address.");
	_settextposition(16,15);
	_outtext("    4. Update rate schedules.");
	_settextposition(18,15);
	_outtext("    5. Return to previous menu.");
	_settextposition(20,15);
	_outtext("  Enter selection number. �");
	_settextposition(20,41);
}

