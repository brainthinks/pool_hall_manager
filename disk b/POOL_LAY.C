/*
		THIS MODULE DISPLAYS THE TABLE RENTAL SCREEN
*/
#include<conio.h>
extern struct  rental *rent;   /* RENTAL RECORD POINTER */
extern	struct rental           /* MEMORY AREA RECORD LAYOUT ARRAY*/
	{
		int cust;                /*2 BYTES */
	}rental_s;





/************ PRINT LAYOUT ****************************************/

prt_layout()
{
	gotoxy( 3,3 ); cputs ("TABLE");
	gotoxy( 9,3 ); cputs ("START");
	gotoxy( 17,3 ); cputs ("STOP");
	gotoxy( 29,3 ); cputs ("TIME");
	gotoxy( 37,3 ); cputs ("# OF RENTAL");
	gotoxy( 50,3 ); cputs ("AMT.");
	gotoxy( 57,3 ); cputs ("COST");
	gotoxy( 62,3 ); cputs ("PER");
	gotoxy( 77,3 ); cputs (" #");
	gotoxy( 5,4 ); cputs ("#");
	gotoxy( 9,4 ); cputs ("TIME");
	gotoxy( 17,4 ); cputs ("TIME");
	gotoxy( 29,4 ); cputs ("USED");
	gotoxy( 37,4 ); cputs ("PLYR");
	gotoxy( 42,4 ); cputs ("RATE");
	gotoxy( 50,4 ); cputs ("DUE");
	gotoxy( 58,4 ); cputs ("PLAYER");
	gotoxy( 67,4 ); cputs ("ACTION    EMP");
	gotoxy( 2,5 ); cputs ("ÚÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄ¿");
	gotoxy( 2,6 ); cputs ("³");
	gotoxy( 7,6 ); cputs ("³");
	gotoxy( 15,6 ); cputs ("³");
	gotoxy( 23,6 ); cputs ("³");
	gotoxy( 37,6 ); cputs ("³");
	gotoxy( 41,6 ); cputs ("³");
	gotoxy( 48,6 ); cputs ("³");
	gotoxy( 57,6 ); cputs ("³");
	gotoxy( 65,6 ); cputs ("³");
	gotoxy( 76,6 ); cputs ("³");
	gotoxy( 80,6 ); cputs ("³");
	gotoxy( 2,7 ); cputs ("³");
	gotoxy( 7,7 ); cputs ("³");
	gotoxy( 15,7 ); cputs ("³");
	gotoxy( 23,7 ); cputs ("³");
	gotoxy( 37,7 ); cputs ("³");
	gotoxy( 41,7 ); cputs ("³");
	gotoxy( 48,7 ); cputs ("³");
	gotoxy( 57,7 ); cputs ("³");
	gotoxy( 65,7 ); cputs ("³");
	gotoxy( 76,7 ); cputs ("³");
	gotoxy( 80,7 ); cputs ("³");
	gotoxy( 2,8 ); cputs ("³");
	gotoxy( 7,8 ); cputs ("³");
	gotoxy( 15,8 ); cputs ("³");
	gotoxy( 23,8 ); cputs ("³");
	gotoxy( 37,8 ); cputs ("³");
	gotoxy( 41,8 ); cputs ("³");
	gotoxy( 48,8 ); cputs ("³");
	gotoxy( 57,8 ); cputs ("³");
	gotoxy( 65,8 ); cputs ("³");
	gotoxy( 76,8 ); cputs ("³");
	gotoxy( 80,8 ); cputs ("³");
	gotoxy( 2,9); cputs ("³");
	gotoxy( 7,9 ); cputs ("³");
	gotoxy( 15,9 ); cputs ("³");
	gotoxy( 23,9 ); cputs ("³");
	gotoxy( 37,9 ); cputs ("³");
	gotoxy( 41,9 ); cputs ("³");
	gotoxy( 48,9 ); cputs ("³");
	gotoxy( 57,9 ); cputs ("³");
	gotoxy( 65,9 ); cputs ("³");
	gotoxy( 76,9 ); cputs ("³");
	gotoxy( 80,9 ); cputs ("³");
	gotoxy( 2,10 ); cputs ("³");
	gotoxy( 7,10 ); cputs ("³");
	gotoxy( 15,10 ); cputs ("³");
	gotoxy( 23,10 ); cputs ("³");
	gotoxy( 37,10 ); cputs ("³");
	gotoxy( 41,10 ); cputs ("³");
	gotoxy( 48,10 ); cputs ("³");
	gotoxy( 57,10 ); cputs ("³");
	gotoxy( 65,10 ); cputs ("³");
	gotoxy( 76,10 ); cputs ("³");
	gotoxy( 80,10 ); cputs ("³");
	gotoxy( 2,11 ); cputs ("³");
	gotoxy( 7,11 ); cputs ("³");
	gotoxy( 15,11 ); cputs ("³");
	gotoxy( 23,11 ); cputs ("³");
	gotoxy( 37,11 ); cputs ("³");
	gotoxy( 41,11 ); cputs ("³");
	gotoxy( 48,11 ); cputs ("³");
	gotoxy( 57,11 ); cputs ("³");
	gotoxy( 65,11 ); cputs ("³");
	gotoxy( 76,11 ); cputs ("³");
	gotoxy( 80,11 ); cputs ("³");
	gotoxy( 2,12 ); cputs ("³");
	gotoxy( 7,12 ); cputs ("³");
	gotoxy( 15,12 ); cputs ("³");
	gotoxy( 23,12 ); cputs ("³");
	gotoxy( 37,12 ); cputs ("³");
	gotoxy( 41,12 ); cputs ("³");
	gotoxy( 48,12 ); cputs ("³");
	gotoxy( 57,12 ); cputs ("³");
	gotoxy( 65,12 ); cputs ("³");
	gotoxy( 76,12 ); cputs ("³");
	gotoxy( 80,12 ); cputs ("³");
	gotoxy( 2,13 ); cputs ("³");
	gotoxy( 7,13 ); cputs ("³");
	gotoxy( 15,13 ); cputs ("³");
	gotoxy( 23,13 ); cputs ("³");
	gotoxy( 37,13 ); cputs ("³");
	gotoxy( 41,13 ); cputs ("³");
	gotoxy( 48,13 ); cputs ("³");
	gotoxy( 57,13 ); cputs ("³");
	gotoxy( 65,13 ); cputs ("³");
	gotoxy( 76,13 ); cputs ("³");
	gotoxy( 80,13 ); cputs ("³");
	gotoxy( 2,14 ); cputs ("³");
	gotoxy( 7,14 ); cputs ("³");
	gotoxy( 15,14 ); cputs ("³");
	gotoxy( 23,14 ); cputs ("³");
	gotoxy( 37,14 ); cputs ("³");
	gotoxy( 41,14 ); cputs ("³");
	gotoxy( 48,14 ); cputs ("³");
	gotoxy( 57,14 ); cputs ("³");
	gotoxy( 65,14 ); cputs ("³");
	gotoxy( 76,14 ); cputs ("³");
	gotoxy( 80,14 ); cputs ("³");
	gotoxy( 2,15 ); cputs ("³");
	gotoxy( 7,15 ); cputs ("³");
	gotoxy( 15,15 ); cputs ("³");
	gotoxy( 23,15 ); cputs ("³");
	gotoxy( 37,15 ); cputs ("³");
	gotoxy( 41,15 ); cputs ("³");
	gotoxy( 48,15 ); cputs ("³");
	gotoxy( 57,15 ); cputs ("³");
	gotoxy( 65,15 ); cputs ("³");
	gotoxy( 76,15 ); cputs ("³");
	gotoxy( 80,15 ); cputs ("³");
	gotoxy( 2,16 ); cputs ("³");
	gotoxy( 7,16 ); cputs ("³");
	gotoxy( 15,16 ); cputs ("³");
	gotoxy( 23,16 ); cputs ("³");
	gotoxy( 37,16 ); cputs ("³");
	gotoxy( 41,16 ); cputs ("³");
	gotoxy( 48,16 ); cputs ("³");
	gotoxy( 57,16 ); cputs ("³");
	gotoxy( 65,16 ); cputs ("³");
	gotoxy( 76,16 ); cputs ("³");
	gotoxy( 80,16 ); cputs ("³");
	gotoxy( 2,17 ); cputs ("³");
	gotoxy( 7,17 ); cputs ("³");
	gotoxy( 15,17 ); cputs ("³");
	gotoxy( 23,17 ); cputs ("³");
	gotoxy( 37,17 ); cputs ("³");
	gotoxy( 41,17 ); cputs ("³");
	gotoxy( 48,17 ); cputs ("³");
	gotoxy( 57,17 ); cputs ("³");
	gotoxy( 65,17 ); cputs ("³");
	gotoxy( 76,17 ); cputs ("³");
	gotoxy( 80,17 ); cputs ("³");
	gotoxy( 2,18 ); cputs ("ÀÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÁÄÄÄÙ");

	gotoxy( 60,19 ); cputs ("CUSTOMER NUMBER");
	gotoxy( 76,19 ); printf ("%i",rent->cust);
	return 0;
}

