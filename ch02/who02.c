/**
 * who02.c - the second version of who program
 * open, read UTMP file, and show results
 * -suppresses empty records
 * -formats time clearly
 */
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define SHOWHOST		/*define remote machine on output*/

void show_info(struct utmp * );
void show_time(long timeval);

int main(int ac, char* av[]) {
	struct utmp  current_record;	/* read info into here */
	int utmpfd;						/* read from this descriptor */	
	int utmp_size = sizeof(current_record);

	if( (utmpfd = open(UTMP_FILE,O_RDONLY)) == -1 ) {
			perror( UTMP_FILE );	/* UTMP_FILE is in utmp.h */
			exit(1);
	}

	while( read(utmpfd,&current_record,utmp_size) == utmp_size )
			show_info(&current_record);
	close(utmpfd);
	return 0;
}

/**
 * show_info()
 * displays contents of the utmp struct in human readable form
 */

void show_info(struct utmp* utbufp) {
	if( utbufp->ut_type != USER_PROCESS )
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
