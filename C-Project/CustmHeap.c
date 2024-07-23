#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <c-project.h>

#define CBUFSIZE	1024
#define CPERMS	0666

void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}

/* Copy input from keyboard to screen */
void CusCopyInp2Outp(void)
{
	char buf[CBUFSIZE];
	int n;
	while ((n = read(0, buf, sizeof buf)) > 0)
		write(1, buf, n);

	return ;
}

/* unbuffered single character input */
int CusGetChar8(void)
{
	char c;
	return (read(0, &c, 1) == 1)? (unsigned char)c: EOF;
}


/* buffered character input */
int CusGetChar(void)
{
	static char buf[CBUFSIZE];
	static char* bufp = buf;
	static int n = 0;

	if (n == 0) {
		n = read(0, buf, sizeof buf);
		bufp = buf;
	}
	return (--n >= 0) ? (unsigned char)*bufp++: EOF;
}

/* Cp program for copying file */
void CusCopyFile(int argc, char* argv[])
{
	int f1, f2, n;
	char buf[CBUFSIZE];

	if (argc != 3)
		error("Usage: %s <from> <to>", argv[0]);
	if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
		error("Could not open <%s>", argv[1]);
	if ((f2 = creat(argv[2], CPERMS)) == -1)
		error("Could not create <%s>i mode %03o", argv[2], CPERMS);
	while ((n = read(f1, buf, sizeof buf)) > 0)
		if (write(f2, buf, n) != n)
			error("Write error on file <%s>", argv[2]);
	return;
}

void CusEchoUnbuffered(void)
{
	int c;
	while((c = CusGetChar8()) != EOF)
		printf("%c", c);
	return ;
}

void CusEchoBuffered(void)
{
	int c;
	while((c = CusGetChar()) != EOF)
		printf("%c", c);
	return ;
}

void CusUnixSyscallLib(int argc, char* argv[])
{
	return ;
}
