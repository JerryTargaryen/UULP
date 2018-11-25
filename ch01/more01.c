/**
 * more01.c - version 0.1 of more
 * read and print 24 lines then pause for a few special commands
 */

#include <stdio.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more();

int main(int ac, char *av[]) {
		FILE *fp;
		if (ac == 1)
