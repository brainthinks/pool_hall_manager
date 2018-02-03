/**************************************************************************
* THIS PROGRAM WILL CREATE A HEX FILE FROM ANY FILE REQUESTED. THE HEX    *
* FILE CAN THEN BE PRINTED OR VIEWED WITH AN EDITER.                      *
***************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include <dos.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#include<graph.h>
#include <signal.h>
#include<windows.h>
main()
{
    FILE *infile, *outfile;
    char inpath[_MAX_PATH], outpath[_MAX_PATH];
    char drive[_MAX_DRIVE], dir[_MAX_DIR];
    char fname[_MAX_FNAME], ext[_MAX_EXT];
    char answ;
    int  in, size, cnt=0,rec_no=1,o=0,svsw = 0;
    unsigned int t,sav[16];
    long i = 0L;
	 char prtc[16];
	 char buff[80];
/****************** code segment ***********************************/
	_clearscreen(_GCLEARSCREEN);
	open_window(1,1,79,25,3,3L,205,0,3);

	open_window(2,17,50,3,8,8L,219,0,0);      /* SHADOW BOX */
	open_window(1,15,50,3,1,7L,205,4,7);

	_outtext("            LIUNA HEX DUMP TO FILE");

	open_window(10,17,50,10,8,8L,219,0,0);    /* SHADOW BOX */
	open_window(9,15,50,10,7,1L,196,7,1);
retry:
	_outtext( "Enter input file name: " );
	gets( inpath );
	strcpy( outpath, inpath );
	if( (infile = fopen( inpath, "rb" )) == NULL )
	{
		open_window(13,13,40,4,14,4L,32,4,4);
		_outtext( "Can't open input file" );
		_outtext( "\nRe_enter file name ( Y or N ) ?");
		answ = getch();
		if(answ == 'y' || answ == 'Y')
		{
			close_window(0);
			_clearscreen(_GWINDOW);
			goto retry;
		}
		close_window(1);
		exit( 1 );
	}
	_splitpath( outpath, drive, dir, fname, ext );
	strcpy( ext, "hx" );
	for(t=0;t<sizeof(drive);t++)
		drive[t] = 0;
	for(t=0;t<sizeof(dir);t++)
		dir[t] = 0;
	_makepath( outpath, drive, dir, fname, ext );
	outfile = fopen( outpath, "wb" );
	sprintf(buff, "\nCreating %s from %s . . .\n", outpath, inpath );
	_outtext(buff);
	_settextcolor(18);
	_outtext(" \n\n    Program running.");
	_settextcolor(7);
	_outtext("\n\n  Press any key to terminate.");
	 /*_outtext( "(B)yte or (W)ord: " );
	size = getche();*/
 /*******************************************************************/
	while( !kbhit() )
	{
		if( (size == 'W') || (size == 'w') )
		{
			in = getw( infile );
			if( (in == EOF) && (feof( infile ) || ferror( infile )) )
				break;
			fprintf( outfile, " %.4X", in );
			if( !(++i % 8) )
				putw( 0x0D0A, outfile );        /* New line      */
		}
		else
		{
			in = fgetc( infile );
			if( (in == EOF) && (feof( infile ) || ferror( infile )) )
				break;
			sav[o++] = in;
			if ( isprint(in) ) {prtc[cnt++] = in;} else
				{prtc[cnt++] = 0;}
			if( !(++i % 16) )
			{
				for(o=0;o<16;o++)
				{
					if (sav[o] > 0)
					svsw = 1;
				}
				if (svsw == 1)
				{
					for(cnt=0;cnt<16;cnt++)       /* Write characters */
					fprintf(outfile,"  %c",prtc[cnt]);
					fprintf(outfile,"     REC. # %-5d",rec_no);
					fputc( 13, outfile );           /* New line      */
					fputc( 10, outfile );
					for(cnt=0;cnt<16;cnt++)        /* Write hex */
					fprintf(outfile," %.2X",sav[cnt]);
					fputc( 13, outfile );           /* New line      */
					fputc( 10, outfile );
				}
				++rec_no;
				svsw = 0;
				cnt = 0;
				o = 0;
			}
		}
	}
	fclose( infile );
	fclose( outfile );
	close_window(1);
	 exit( 0 );
}

