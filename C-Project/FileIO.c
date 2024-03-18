#include <stdio.h>
#include <errno.h>
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