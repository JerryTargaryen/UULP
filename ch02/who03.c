/**
 * who03.c - the third version of who program
 * open, read UTMP file, and show results
 * -suppresses empty records
 * -formats time clearly
 * -buffer inputs (using utmplib)
 */
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "utmplib.h"

#define SHOWHOST		/*define remote machine on output*/

void show_info(struct utmp * );
void show_time(long timeval);

int main(int ac, char* av[]) {
	struct utmp *cur_utmp;	/* read info into here */
	int utmpfd;						/* read from this descriptor */	

	if ( (utmpfd = utmp_open(UTMP_FILE)) == -1 ) {
			perror( UTMP_FILE );	/* UTMP_FILE is in utmp.h */
			exit(1);
	}

	while ((cur_utmp = utmp_next()) != (struct utmp*)NULL )
			show_info(cur_utmp);

	utmp_close();
	return 0;
}

/**
 * show_info()
 * displays contents of the utmp struct in human readable form
 */

void show_info(struct utmp* utbufp) {
	if ( utbufp->ut_type != USER_PROCESS )
			return;
	printf("%-11.11s", utbufp->ut_name);
	printf(" ");
	printf("%-8.8s", utbufp->ut_line);
	printf(" ");

	show_time(utbufp->ut_time);	
#ifdef SHOWHOST
	printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
}

/**
 * show_time
 */

void show_time(long timeval) {
		char *cp;
		cp = ctime(&timeval);
		printf("%-12.12s",cp+4);
}
