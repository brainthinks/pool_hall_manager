/*********************************************************************
*   This program is used as a job control monitor for runing         *
*   the LPL application.  It opens (runtime) for all application     *
*   programs with the exception of the restore program.  Restore     *
*   must be run within dbase since it re-compiles all programs.      *
**********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
main()
{
   int  c,i;
   char d[192],restore[]="RESTORE";
   FILE *fp;
   system("D:");
   system("cd \\dbase4\\newdon");
start:
   if ( (spawnlp(P_WAIT,"runtime.exe","","/t","drun",NULL)) == -1)
   {
	perror("Error opening runtime /t drun");
	goto end;
   }
   if( fp = fopen( "dmemvar.mem", "rb" ) )
   {
      i = 0;
      while( (c = fgetc( fp )) != EOF )         /*STORE DMEMVAR TO char d*/
	     d[i++]  = c;
      for (i =0;i<192;i++)                      /*SEARCH FOR 'BACKUP'*/
      {
	 if( memcmp (restore,d+i,7) == 0 )
	    {
	       fclose( fp );
	       if ( (spawnlp(P_WAIT,"dbase.exe","","/t","restore",NULL))==-1)
	       {
		  perror("Error opening dbase /t restore");
		  goto end;
	       }
	       goto start;
	    }
      }
   end:;
   }
   else
      printf( "Error in opening file\n" );
   system("cls");

}

