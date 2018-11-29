/**
 * utmplib.c - functions to buffer reads from utmp file
 *
 * 	functions are
 * 		utmp_open( filename ) - open file
 * 			return -1 on error
 * 		utmp_next( )		  - return pointer to next struct
 * 			return NULL on eof
 * 		utmp_close( )		  - close file
 * 			
 * 		reads NRECS per read and then doles them out from the buffer
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>
#include <unistd.h>
#include "utmplib.h"

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)		
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NRECS * UTSIZE];		/* storage  */
static int num_recs;						/* num stored  */
static int cur_rec;							/* next to go  */
static int fd_utmp = -1;					/* read from  */

int utmp_reload(void);

int utmp_open(char *filename) 
{
	fd_utmp = open(filename, O_RDONLY);
	num_recs = cur_rec = 0;
	return fd_utmp;
}

struct utmp *utmp_next(void)
{
	struct utmp *recp;
	if (fd_utmp == -1) 			/* error */
		return NULLUT;
	if (cur_rec == num_recs && utmp_reload() == 0)		/* no more */
		return NULLUT;

	recp = (struct utmp*)&utmpbuf[cur_rec * UTSIZE];
	cur_rec++;
	return recp;
}


/**
 * int utmp_reload( ) - read next bunch of records into buffer
 */
int utmp_reload(void)
{
	int amt_read;
	amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
	num_recs = amt_read / UTSIZE;
	cur_rec = 0;
	return num_recs;
}

/**
 * void utmp_close( ) - close file opened
 */
void utmp_close(void)
{
	if (fd_utmp != -1)
			close(fd_utmp);
}



