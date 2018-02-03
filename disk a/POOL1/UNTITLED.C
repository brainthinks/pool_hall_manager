
/* TIMES.C illustrates various time and date functions including:
 *      time            ftime           ctime       asctime
 *      localtime       gmtime          mktime      tzset
 *      _strtime        _strdate        strftime
 *
 * Also the global variable:
 *      tzname
 */

#include <time.h>
#include <stdio.h>
#include <sys\types.h>
#include <sys\timeb.h>
#include <string.h>

void main()
{
	char tmpbuf[128], ampm[] = "AM";
	time_t ltime;
	struct timeb tstruct;
	struct tm *today, *gmt, xmas = { 0, 0, 12, 25, 11, 88 };

	/* Set time zone from TZ environment variable. If TZ is not set,
	 * PST8PDT is used (Pacific standard time, daylight savings).
	 */
	tzset();

	/* Display DOS-style date and time. */
	_strtime( tmpbuf );
	printf( "DOS time:\t\t\t\t%s\n", tmpbuf );
	_strdate( tmpbuf );
	printf( "DOS date:\t\t\t\t%s\n", tmpbuf );

	/* Get UNIX-style time and display as number and string. */
	time( &ltime );
	printf( "Time in seconds since GMT 1/1/70:\t%ld\n", ltime );
	printf( "UNIX time and date:\t\t\t%s", ctime( &ltime ) );

	/* Display GMT. */
	gmt = gmtime( &ltime );
	printf( "Greenwich Mean Time:\t\t\t%s", asctime( gmt ) );

	/* Convert to time structure and adjust for PM if necessary. */
	today = localtime( &ltime );
	if( today->tm_hour > 12 )
	{
		strcpy( ampm, "PM" );
		today->tm_hour -= 12;
	}
	/* Note how pointer addition is used to skip the first 11 characters
	 * and printf is used to trim off terminating characters.
	 */
	printf( "12-hour time:\t\t\t\t%.8s %s\n",
			asctime( today ) + 11, ampm );

	/* Print additional time information. */
	ftime( &tstruct );
	printf( "Plus miliseconds:\t\t\t%u\n", tstruct.millitm );
	printf( "Zone difference in seconds from GMT:\t%u\n", tstruct.timezone );
	printf( "Time zone name:\t\t\t\t%s\n", tzname[0] );
	printf( "Daylight savings:\t\t\t%s\n", tstruct.dstflag ? "YES" : "NO" );

	/* Make time for noon on Christmas, 1988. */
	if( mktime( &xmas ) != (time_t)-1 )
		printf( "Christmas\t\t\t\t%s\n", asctime( &xmas ) );

	/* Use time structure to build a customized time string. */
	today = localtime( &ltime );

	/* Use strftime to build a customized time string. */
	strftime( tmpbuf, 128, "Today is %A, day %d of %B in the year %Y.\n", today );
	printf( tmpbuf );
}




