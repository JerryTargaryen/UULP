/**
 * test.c 
 * test the situation that one process open sigle file many times and execute different operations
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 20

void oops(char *, char *);
int main(int argc, char *argv[])
{
	int fd1;
	int fd2;
	int fd3;
	char buf1[BUFFSIZE];
	char buf2[BUFFSIZE];
	const char test[] = "testing 123...";

	if ((fd1 = open(argv[1],O_RDONLY)) == -1)
		oops("Cannot read", argv[1]);
	if ((fd2 = open(argv[1],O_WRONLY)) == -1)
		oops("Cannot write", argv[1]);
	if ((fd3 = open(argv[1],O_RDWR)) == -1)
		oops("Cannot read & write",argv[1]);

	if (read(fd1, buf1, BUFFSIZE) == -1)
		oops("Read error", argv[1]);
	puts(buf1);

	if (write(fd2, test, strlen(test)) == -1)
		oops("Write error", argv[1]);

	if (read(fd3, buf2, BUFFSIZE) == -1)
		oops("Read error", argv[1]);
	puts(buf2);

	if (close(fd1) == -1 ||  close(fd2) == -1 || close(fd3) == -1)
		oops("File close error", argv[1]);

	return 0;
}

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s\n", s1);
	perror(s2);
	exit(1);
}





	
