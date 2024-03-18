#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <c-project.h>

void FileCopy(FILE* ifp, FILE* ofp)
{
	int c;

	while ((c = getc(ifp)) != EOF)
	{
		putc(c, ofp);
	}
	return;
}

void ConcatenateFiles(int argc, char* argv[])
{
	FILE* fp;

	if (argc == 1) /* no args, copy standard input */
		FileCopy(stdin, stdout);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL)	{
				printf("Error opening file %s\n", *argv);
				return;
			}
			else {
				FileCopy(fp, stdout);
				fclose(fp);
			}
	return;
}

void ConcatenateFiles2(int argc, char* argv[])
{
	FILE* fp;
	char* prog = argv[0];

	if (argc == 1)
		FileCopy(stdin, stdout);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
				exit(1);
			}
			else {
				FileCopy(fp, stdout);
				fclose(fp);
			}
	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2);
	}
	exit(0);
}