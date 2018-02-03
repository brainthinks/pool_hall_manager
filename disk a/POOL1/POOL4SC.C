/*
		THIS MODULE DISPLAYS THE RENTAL MENU - PAGE 2
*/

#include<graph.h>
int extern fcolor;
int extern hcolor;
pool4()
{
		open_window(14,1,77,11,fcolor,(long)hcolor,32,fcolor,hcolor);
		_settextwindow(13,1,23,77);
		_settextposition(2,1);
		_outtext("    1. Clear table from daily         ³  5. Set table to employee player/s.");
		_settextposition(3,1);
		_outtext("       cash receipts.                 ³");
		_settextposition(4,1);
		_outtext("                                      ³     Activate promotional rental");
		_settextposition(5,1);
		_outtext("    2. Issue a credit.                ³     rates.");
		_settextposition(6,1);
		_outtext("                                      ³");
		_settextposition(7,1);
		_outtext("    3. Change incorrect table start   ³  7. Return to page 1 of rental menu.");
		_settextposition(8,1);
		_outtext("       time.                          ³");
		_settextposition(9,1);
		_outtext("                                      ³");
		_settextposition(10,1);
		_outtext("    4. Change incorrect number of     ³");
		_settextposition(11,1);
		_outtext("       players.                       ³");
}
