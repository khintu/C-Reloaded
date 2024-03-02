#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <c-project.h>

#define SIZE	5

int getInt(int *pn)
{
	int c, ac, sign;

signSpcFnd:
	while ((isspace(c = getch())))
		;
	if (!isdigit(c) && c != '.' && c != '+' && c != '-')
	{
		ungetch(c);		/* it's not a number */
		return 0;
	}
	sign = c == '-' ? -1 : 1;
	if (c == '+' || c == '-')
	{
		if (isspace(ac = getch()))
		{
			ungetch(c);
			goto signSpcFnd;
		}
		c = ac;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = *pn * 10 + c - '0';
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

void testGetIntFrmCmdLine(void)
{
	int n, array[SIZE] = { 0 };

	for (n = 0; n < SIZE && getInt(&array[n]) != EOF; ++n)
		;
	for (n = 0; n < SIZE; ++n)
		printf("%d%c", array[n], (n % SIZE == SIZE - 1) ? '\n' : ',');
	return;
}

int getFloat(double* pn)
{
	int c, ac, sign;
	double pwr;

signSpcFnd:
	while ((isspace(c = getch())))
		;
	if (!isdigit(c) && c != '.' && c != '+' && c != '-')
	{
		ungetch(c);		/* it's not a number */
		return 0;
	}
	sign = c == '-' ? -1 : 1;
	if (c == '+' || c == '-')
	{
		if (isspace(ac = getch()))
		{
			ungetch(c);
			goto signSpcFnd;
		}
		c = ac;
	}
	for (*pn = 0.0f; isdigit(c); c = getch())
		*pn = *pn * 10.0f + c - '0';
	if (c == '.')
	{
		for (pwr = 1.0f, c = getch(); isdigit(c); c = getch(), pwr*=10.0f)
			*pn = *pn * 10.0f + c - '0';
		*pn /= pwr;
	}
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

void testGetFloatFrmCmdLine(void)
{
	int n;
	double array[SIZE] = { 0.0f };

	for (n = 0; n < SIZE && getFloat(&array[n]) != EOF; ++n)
		;
	for (n = 0; n < SIZE; ++n)
		printf("%.10g%c", array[n], (n % SIZE == SIZE - 1) ? '\n' : ',');
	return;
}

int StrLen(char* s)
{
	int l;
	for (l = 0; *s++ != NUL; ++l)
		;
	return l;
}

void StrCpyArry(char* s, char* t)
{
	int i;

	i = 0;
	while ((s[i] = t[i]) != NUL)
		i++;
	return;
}

void StrCpyPtr(char* s, char* t)
{
	while (*s++ = *t++)
		;
	return;
}

int StrCmpArry(char* s, char* t)
{
	int i;

	for (i = 0; s[i] == t[i]; ++i)
		if (s[i] == NUL)
			return 0;
	return s[i] - t[i];
}

int StrCmpPtr(char* s, char* t)
{
	for (; *s == *t; ++s, ++t)
		if (*s == NUL)
			return 0;
	return *s - *t;
}

void StrCatPtr(char* s, char* t)
{
	s += StrLen(s);
	StrCpyPtr(s, t);
	return;
}

void testStrCat(void)
{
	char s[8] = "abc#";
	char t[5] = "def";
	
	StrCatPtr(s, t);
	printf("%s\n", s);
	return;
}

int StrEnd(char* s, char* t)
{
	int ls, lt;
	ls = StrLen(s);
	lt = StrLen(t);
	if (ls >= lt && lt > 0)
	{
		s += ls;
		s -= lt;
		for (; *s == *t && *s; s++, t++)
			;
		if (*s == NUL)
			return 1;
	}
	return 0;
}

void testStrEnd(void)
{
	char s[8] = "abc";
	char t[8] = "abc";

	printf("%d\n", StrEnd(s, t));
	return;
}

void StrNCpy(char* s, char* t, int n)
{
	for (;(n > 0) && (*s = *t); ++s, ++t, --n)
		;
	if (n == 0 && *s != NUL)
		*s = NUL;
	return;
}

int StrNCmp(char* s, char* t, int n)
{
	for (; n > 0 && *s == *t; ++s, ++t, --n)
		;
	if (*t == NUL || n == 0)
		return 0;
	return *s - *t;
}

void StrNCat(char* s, char* t, int n)
{
	int ls;

	ls = StrLen(s);
	s += ls;
	StrNCpy(s, t, n);
	return;
}

/*	-WARNING-
		Buffer overrun check is the responsibility of the
		caller of the strN(All) functions. Allocate enough
		memory for cat/cpy operations to complete without
		corruption. 
*/
void testAllStrNFunc(void)
{
	char s[9];// = "wxyz";
	char t[8] = "abcd";

	StrNCpy(s, t, 5);
	printf("%s\n", s);

	printf("%d\n", StrNCmp(s, "aBcd", 2));

	StrNCat(s, "aBcd", 4);
	printf("%s\n", s);
	return;
}

int strindexPtr(char *s, char *t)
{
	int i, j, k;

	for (i = 0; *(s+i) != '\0'; ++i)
	{
		for (j = i, k = 0; *(t+k) != '\0' && *(s+j) == *(t+k); ++j, ++k)
			;
		if (k > 0 && *(t+k) == '\0')
			return i;
	}
	return -1;
}

/* Memory Manager - Contiguous chunks of memory as a LIFO */
#define ALLOCSIZE 10000
static char allocBuf[ALLOCSIZE];  /* Pool of contiguous memory */
static char* allocPtr = allocBuf;  /* points to next free address */

char* AllocChar(int n)
{
	if (allocBuf + ALLOCSIZE - allocPtr >= n) /* Ptr is higer address than Buf */
	{																					/* Ptr - Buf gives the allocated mem size. */
		allocPtr += n;
		return allocPtr - n;
	}
	else
		return 0;
}

void AllocFree(char* p)
{
	if (p >= allocBuf && p < allocBuf + ALLOCSIZE) /* p is always less than Ptr */
		allocPtr = p;																 /* as gauranteed by AllocChar() */
}

/* Stripped down version of UNIX Sort program */
#define MAXLINES	5000
char* linePtr[MAXLINES]; /* Array of pointers to actual strings */

void SortInputLines(void)
{
	int nlines;
	
	if ((nlines = ReadLines(linePtr, MAXLINES)) >= 0)
	{
		QuickSortStr(linePtr, 0, nlines - 1);
		WriteLines(linePtr, nlines);
	}
	else
	{
		printf("Error: Input too big to sort\n");
	}
	return;
}

int ReadLines(char* linePtr[], int maxlines)
{
	int len, nlines;
	char* p, line[MAXLINE];

	nlines = 0;
	while ((len = getline4(line, MAXLINE)) > 0)
	{
		if (nlines >= maxlines || (p = AllocChar(len)) == NULL)
			return -1;
		else
		{
			line[len - 1] = NUL; /* delete newline */
			StrCpyPtr(p, line);
			linePtr[nlines++] = p;
		}
	}
	return nlines;
}

void WriteLines(char* linePtr[], int nlines)
{
	int i;

	for (i = 0; i < nlines; ++i)
		printf("%s\n", linePtr[i]);
}

#define SWAPV(i, j) {\
											char* tmp;\
											tmp = v[i];\
											v[i] = v[j];\
											v[j] = tmp;\
										}

void QuickSortStr(char* v[], int left, int right)
{
	int i, pivot;

	if (left >= right)
		return;

	SWAPV(left, (left + right)/2);
	pivot = left;
	for (i = left + 1; i <= right; ++i)
	{
		if (StrCmpPtr(v[i], v[left]) < 0)
		{
			++pivot;
			SWAPV(pivot, i);
		}
	}
	SWAPV(left, pivot);
	QuickSortStr(v, left, pivot - 1);
	QuickSortStr(v, pivot + 1, right);
	return;
}

void test2DArryMemoryLayout(void)
{
	int a[10][20];
	int* b[10]; /* KnR Way*/
	int(*b1)[20];/* My way */

	b1 = (int (*)[20])AllocChar(10 * sizeof(int [20]));

	printf("%d\n", a[3][4]);
	printf("%d\n", b[3][4]);/* Access Violation! Bad memory layout */
	printf("%d\n", b1[3][4]);

	AllocFree((char*)b1);
	return;
}

int findLinesMatchgPattrn2(int argc, char* argv[])
{
	char line[MAXLINE];
	int found = 0;

	if (argc != 2)
		printf("Usage: find pattern\n");
	else
		while(getline4(line, MAXLINE) > 0)
			if (strstr(line, argv[1]) != NULL)
			{
				printf("%s", line);
				++found;
			}
	return found;
}

int findLinesMatchgPattrn3(int argc, char* argv[])
{
	char line[MAXLINE];
	long lineno = 0;
	int c, except = FALSE, number = FALSE, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-') /* step ++argv, then access 1st [0], char in string */
		while (c = *++argv[0]) /* stepping inside curr string ++argv[0], access 2nd char */
			switch (c)
			{
			case 'x':
				except = TRUE;
				break;
			case 'n':
				number = TRUE;
				break;
			default:
				printf("Find: illegal option %c\n", c);
				break;
			}
	if (argc != 1)
		printf("Usage: Find -x -n pattern\n");
	else
		while (getline4(line, MAXLINE) > 0)
		{
			lineno++;
			if ((strstr(line, *argv) != NULL) != except)
			{
				if (number)
					printf("%ld:", lineno);
				printf("%s", line);
				found++;
			}
		}
	return found;
}

int getoperator3(char s[], int *argc, char* *argv[])
{
	int c;
	static int last = FALSE;

	if (--*argc > 0)
	{
		if (*argc == 1)
		{
			last = TRUE;
		}
		strcpy(s, (*++ * argv));
		c = s[0];

		if (!isdigit(c) && c != '.') /* Its a variable, command or operator */
			return c;

		return NUMBER;
	}
	if (last)
	{
		last = FALSE;
		return '\n';
	}
	return EOF;
}

void detab2CmdLine(int argc, char* argv[])
{
	int c, tabStop = TABSTOP;

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		c = *++argv[0]; /* Test 1st char after '-' only, then step to next arg */
		switch (c)
		{
		case 't':
			tabStop = TRUE;
			break;
		default:
			break;
		}
	}
	if (argc == 0)
	{
		detab2(TABSTOP); /* default case */
	}
	else if (argc == 1 && tabStop == TRUE)
	{
		tabStop = atoi2(*argv);
		detab2(tabStop);
	}
	else
		printf("Usage: detab [-t <tabStop>]\n");


	return;
}

// Replace tabs with spaces
void detab2(int tabStop)
{
	int i, ri, j;
	char line[MAXLINE];
	char replaced[MAXLINE];

	while (getLine(line, MAXLINE) > 0)
	{
		for (i = 0, ri = 0; line[i] != '\0'; ++i)
			if (line[i] == '\t')
			{
				for (j = 0; j < tabStop; ++j)
				{
					if (ri < MAXLINE - 1)
						replaced[ri + j] = ' ';
				}
				ri += tabStop;
			}
			else
			{
				if (ri < MAXLINE - 1)
					replaced[ri] = line[i];
				ri += 1;
			}
		if (ri < MAXLINE)
			replaced[ri] = '\0';
		else
			// truncate out string to MAXLINE on buffer overflow
			replaced[MAXLINE - 1] = '\0';
		printf("%s", replaced);
	}
	return;
}

void entab2CmdLine(int argc, char* argv[])
{
	int c, tabStop = FALSE;

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		c = *++argv[0]; /* Test 1st char after '-' only, then step to next arg */
		switch (c)
		{
		case 't':
			tabStop = TRUE;
			break;
		default:
			break;
		}
	}
	if (argc == 0)
	{
		entab2(TABSTOP); /* default case */
	}
	else if (argc == 1 && tabStop == TRUE)
	{
		tabStop = atoi2(*argv);
		entab2(tabStop);
	}
	else
		printf("Usage: entab [-t <tabStop>]\n");

	return;
}
// Lets do integer division on space string and 
// tabstop (length of tab), find out how many tabs
// are required to fill in for the space string
// as a integer number. The remainder is the number
// of spaces to be filled in.
#define IN	1
#define OUT	0
void entab2(int tabStop)
{
	int i, ri, j, state, spcCount, tabCount;
	char line[MAXLINE];
	char replaced[MAXLINE];

	while (getLine(line, MAXLINE) > 0)
	{
		state = OUT;
		spcCount = 0;
		for (i = 0, ri = 0; line[i] != '\0'; ++i)
		{
			if (state == OUT && line[i] == ' ')
			{
				state = IN;
				++spcCount;
			}
			else if (state == OUT && line[i] != ' ')
			{
				replaced[ri] = line[i];
				++ri;
			}
			else if (state == IN && line[i] != ' ')
			{
				state = OUT;
				tabCount = spcCount / tabStop;
				for (j = 0; j < tabCount; ++j)
				{
					//replaced[ri] = '\t';
					replaced[ri] = '#';
					++ri;
					spcCount -= tabStop;
				}
				for (j = 0; j < spcCount; ++j)
				{
					//replaced[ri] = ' ';
					replaced[ri] = '$';
					++ri;
				}
				spcCount = 0;
				replaced[ri] = line[i];
				++ri;
			}
			else if (state == IN && line[i] == ' ')
			{
				++spcCount;
			}
			else
			{
				// Do nothing, since code is tight on
				// state variable being either IN or OUT
				printf("entab: Error on state\n");
			}
		}
		if (ri < MAXLINE)
			replaced[ri] = '\0';
		else
			// truncate out string to MAXLINE on buffer overflow
			replaced[MAXLINE - 1] = '\0';
		printf("%s", replaced);
	}
	return;
}
#undef IN
#undef OUT
