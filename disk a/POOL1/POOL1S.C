/*
		THIS MODULE DISPLAYS THE MAIN MENU
*/


#include<graph.h>
/**************** PRINT MAIN MENU**********************************/
pool1s()
{
	int extern hcolor;
	int extern fcolor;
	char extern na_buff[4][49];
	_clearscreen(_GCLEARSCREEN);
	/*
	printf("Background = %d , Forground = %d ",fcolor,hcolor);
	*/
	open_window(5,15,50,6,hcolor,(long)fcolor,205,hcolor,fcolor);

	_settextposition( 1, (48 - strlen(na_buff[0])) /2 );
	_outtext(na_buff[0]);
	_outtext("\n");
	_settextposition( 2, (48 - strlen(na_buff[1])) /2 );
	_outtext(na_buff[1]);
	_outtext("\n");
	_settextposition( 3, (48 - strlen(na_buff[2])) /2 );
	_outtext(na_buff[2]);
	_outtext("\n");
	_settextposition( 4, (48 - strlen(na_buff[3])) /2 );
	_outtext(na_buff[3]);

	_settextwindow(1,1,24,80);
	_settextcolor(fcolor);
	_setbkcolor((long)hcolor);
	_settextposition(14,18);
	_outtext("        1. Table rental menu.                    ");
	_settextposition(16,18);
	_outtext("        2. Employer menu.                        ");
	_settextposition(18,18);
	_outtext("        3. Exit this program.                    ");
	_settextposition(20,18);
	_outtext("     Enter selection number. °");
	_settextposition(20,47);

}

