/*
		THIS MODULE DISPLAYS THE TABLE RENTAL SCREEN
*/
#include<graph.h>
#include<sys\timeb.h>

 extern struct rental           /* MEMORY AREA RECORD LAYOUT ARRAY*/
	{
		int cust;                /*2 BYTES */
		int table;               /*2 BYTES */
		int no_ply;              /*2 BYTES */
		float rate;              /*4 BYTES */
		int e_pw;                /*2 BYTES */
		int trans;               /*2 BYTES */
		time_t start;            /*4 BYTES */
		time_t stop ;            /*4 BYTES */
		long *prev;              /*4 BYTES */
		char freeze;
		int new_table;
		int no_emp;
								 /*26 TOTAL BYTES */
	}rental_s;


 extern struct  rental *rent;   /* RENTAL RECORD POINTER */

/************ PRINT LAYOUT ****************************************/

prt_layout()
{
	_settextposition( 3,3 ); printf ("TABLE");
	_settextposition( 3,9 ); printf ("START");
	_settextposition( 3,17 ); printf ("STOP");
	_settextposition( 3,29 ); printf ("TIME");
	_settextposition( 3,37 ); printf ("# OF RENTAL");
	_settextposition( 3,50 ); printf ("AMT.");
	_settextposition( 3,57 ); printf ("COST");
	_settextposition( 3,62 ); printf ("PER");
	_settextposition( 3,77 ); printf (" #");
	_settextposition( 4,5 ); printf ("#");
	_settextposition( 4,9 ); printf ("TIME");
	_settextposition( 4,17 ); printf ("TIME");
	_settextposition( 4,29 ); printf ("USED");
	_settextposition( 4,37 ); printf ("PLYR");
	_settextposition( 4,42 ); printf ("RATE");
	_settextposition( 4,50 ); printf ("DUE");
	_settextposition( 4,58 ); printf ("PLAYER");
	_settextposition( 4,67 ); printf ("ACTION    EMP");
	_settextposition( 5,2 ); printf ("ÚÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄ¿");
	_settextposition( 6,2 ); printf ("³");
	_settextposition( 6,7 ); printf ("³");
	_settextposition( 6,15 ); printf ("³");
	_settextposition( 6,23 ); printf ("³");
	_settextposition( 6,37 ); printf ("³");
	_settextposition( 6,41 ); printf ("³");
	_settextposition( 6,48 ); printf ("³");
	_settextposition( 6,57 ); printf ("³");
	_settextposition( 6,65 ); printf ("³");
	_settextposition( 6,76 ); printf ("³");
	_settextposition( 6,80 ); printf ("³");
	_settextposition( 7,2 ); printf ("³");
	_settextposition( 7,7 ); printf ("³");
	_settextposition( 7,15 ); printf ("³");
	_settextposition( 7,23 ); printf ("³");
	_settextposition( 7,37 ); printf ("³");
	_settextposition( 7,41 ); printf ("³");
	_settextposition( 7,48 ); printf ("³");
	_settextposition( 7,57 ); printf ("³");
	_settextposition( 7,65 ); printf ("³");
	_settextposition( 7,76 ); printf ("³");
	_settextposition( 7,80 ); printf ("³");
	_settextposition( 8,2 ); printf ("³");
	_settextposition( 8,7 ); printf ("³");
	_settextposition( 8,15 ); printf ("³");
	_settextposition( 8,23 ); printf ("³");
	_settextposition( 8,37 ); printf ("³");
	_settextposition( 8,41 ); printf ("³");
	_settextposition( 8,48 ); printf ("³");
	_settextposition( 8,57 ); printf ("³");
	_settextposition( 8,65 ); printf ("³");
	_settextposition( 8,76 ); printf ("³");
	_settextposition( 8,80 ); printf ("³");
	_settextposition( 9,2 ); printf ("³");
	_settextposition( 9,7 ); printf ("³");
	_settextposition( 9,15 ); printf ("³");
	_settextposition( 9,23 ); printf ("³");
	_settextposition( 9,37 ); printf ("³");
	_settextposition( 9,41 ); printf ("³");
	_settextposition( 9,48 ); printf ("³");
	_settextposition( 9,57 ); printf ("³");
	_settextposition( 9,65 ); printf ("³");
	_settextposition( 9,76 ); printf ("³");
	_settextposition( 9,80 ); printf ("³");
	_settextposition( 10,2 ); printf ("³");
	_settextposition( 10,7 ); printf ("³");
	_settextposition( 10,15 ); printf ("³");
	_settextposition( 10,23 ); printf ("³");
	_settextposition( 10,37 ); printf ("³");
	_settextposition( 10,41 ); printf ("³");
	_settextposition( 10,48 ); printf ("³");
	_settextposition( 10,57 ); printf ("³");
	_settextposition( 10,65 ); printf ("³");
	_settextposition( 10,76 ); printf ("³");
	_settextposition( 10,80 ); printf ("³");
	_settextposition( 11,2 ); printf ("³");
	_settextposition( 11,7 ); printf ("³");
	_settextposition( 11,15 ); printf ("³");
	_settextposition( 11,23 ); printf ("³");
	_settextposition( 11,37 ); printf ("³");
	_settextposition( 11,41 ); printf ("³");
	_settextposition( 11,48 ); printf ("³");
	_settextposition( 11,57 ); printf ("³");
	_settextposition( 11,65 ); printf ("³");
	_settextposition( 11,76 ); printf ("³");
	_settextposition( 11,80 ); printf ("³");
	_settextposition( 12,2 ); printf ("³");
	_settextposition( 12,7 ); printf ("³");
	_settextposition( 12,15 ); printf ("³");
	_settextposition( 12,23 ); printf ("³");
	_settextposition( 12,37 ); printf ("³");
	_settextposition( 12,41 ); printf ("³");
	_settextposition( 12,48 ); printf ("³");
	_settextposition( 12,57 ); printf ("³");
	_settextposition( 12,65 ); printf ("³");
	_settextposition( 12,76 ); printf ("³");
	_settextposition( 12,80 ); printf ("³");
	_settextposition( 13,2 ); printf ("³");
	_settextposition( 13,7 ); printf ("³");
	_settextposition( 13,15 ); printf ("³");
	_settextposition( 13,23 ); printf ("³");
	_settextposition( 13,37 ); printf ("³");
	_settextposition( 13,41 ); printf ("³");
	_settextposition( 13,48 ); printf ("³");
	_settextposition( 13,57 ); printf ("³");
	_settextposition( 13,65 ); printf ("³");
	_settextposition( 13,76 ); printf ("³");
	_settextposition( 13,80 ); printf ("³");
	_settextposition( 14,2 ); printf ("³");
	_settextposition( 14,7 ); printf ("³");
	_settextposition( 14,15 ); printf ("³");
	_settextposition( 14,23 ); printf ("³");
	_settextposition( 14,37 ); printf ("³");
	_settextposition( 14,41 ); printf ("³");
	_settextposition( 14,48 ); printf ("³");
	_settextposition( 14,57 ); printf ("³");
	_settextposition( 14,65 ); printf ("³");
	_settextposition( 14,76 ); printf ("³");
	_settextposition( 14,80 ); printf ("³");
	_settextposition( 15,2 ); printf ("³");
	_settextposition( 15,7 ); printf ("³");
	_settextposition( 15,15 ); printf ("³");
	_settextposition( 15,23 ); printf ("³");
	_settextposition( 15,37 ); printf ("³");
	_settextposition( 15,41 ); printf ("³");
	_settextposition( 15,48 ); printf ("³");
	_settextposition( 15,57 ); printf ("³");
	_settextposition( 15,65 ); printf ("³");
	_settextposition( 15,76 ); printf ("³");
	_settextposition( 15,80 ); printf ("³");
	_settextposition( 16,2 ); printf ("³");
	_settextposition( 16,7 ); printf ("³");
	_settextposition( 16,15 ); printf ("³");
	_settextposition( 16,23 ); printf ("³");
	_settextposition( 16,37 ); printf ("³");
	_settextposition( 16,41 ); printf ("³");
	_settextposition( 16,48 ); printf ("³");
	_settextposition( 16,57 ); printf ("³");
	_settextposition( 16,65 ); printf ("³");
	_settextposition( 16,76 ); printf ("³");
	_settextposition( 16,80 ); printf ("³");
	_settextposition( 17,2 ); printf ("³");
	_settextposition( 17,7 ); printf ("³");
	_settextposition( 17,15 ); printf ("³");
	_settextposition( 17,23 ); printf ("³");
	_settextposition( 17,37 ); printf ("³");
	_settextposition( 17,41 ); printf ("³");
	_settextposition( 17,48 ); printf ("³");
	_settextposition( 17,57 ); printf ("³");
	_settextposition( 17,65 ); printf ("³");
	_settextposition( 17,76 ); printf ("³");
	_settextposition( 17,80 ); printf ("³");
	_settextposition( 18,2 ); printf ("ÀÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÁÄÄÄÙ");
	_settextposition( 20,2 ); printf ("TOTAL AMOUNT DUE $");
	_settextposition( 20,60 ); printf ("CUSTOMER NUMBER");

	_settextposition( 20,76 ); printf ("%i",rent->cust);
}

