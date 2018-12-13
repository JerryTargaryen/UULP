/**
 * "utmplib.h" 
 * head file for utmplib.c source file
 */

#include <utmp.h>

int utmp_open(char *);
struct utmp *utmp_next(void);
void utmp_close(void);
