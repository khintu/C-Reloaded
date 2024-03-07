#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
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

int StrCmpRev(char* s, char* t)
{
	for (; *s == *t; ++s, ++t)
		if (*s == NUL)
			return 0;
	return *t - *s;
}

int StrFieldCmpRev(char* s, char* t, int field)
{
	if (s[field] == t[field])
		return 0;

	return t[field] - s[field];
}

/* QSort Bug fix - The same string in case agnostic strcmp should
appear the same to not just to themselves but to other strings
as well. If you leave that part out other strings will on
compare see it as two different strings not the same.
See the problem as numbers instead of strings. Same digits
clump together because of comparison with themselves and
with other numbers in the array. All same strings should
clump together based on their lower case values.
*/
int StrCaseCmp(char* s, char* t)
{
	for (; tolower(*s) == tolower(*t); ++s, ++t)
		if (*s == NUL)
			return 0;
	return tolower(*s) - tolower(*t);
}

int StrFieldCaseCmp(char* s, char* t, int field)
{
	if (s[field] == t[field])
		return 0;
	return tolower(s[field]) - tolower(t[field]);
}

int StrDirCaseCmp(char* s, char* t)
{
	for (; (isalnum(*s) || isspace(*s)) && (isalnum(*t) || isspace(*t)); ++s, ++t)
	{
		if (islower(*s) == islower(*t))
		{
			if (*s == NUL)
				return 0;
		}
		else
			break;
	}
	return islower(*s) - islower(*t);
}

int StrFieldDirCaseCmp(char* s, char* t, int field)
{
	if ((isalnum(s[field]) || isspace(s[field])) && (isalnum(t[field]) || isspace(t[field])))
	{
		if (islower(s[field]) == islower(t[field]))
			return 0;
	}
	return islower(s[field]) - islower(t[field]);
}

int StrDirCmp(char* s, char* t)
{
	for (; (isalnum(*s) || isspace(*s)) && (isalnum(*t) || isspace(*t)); ++s, ++t)
	{
		if (*s == *t)
		{
			if (*s == NUL)
				return 0;
		}
		else
			break;
	}
	return *s - *t;
}

int StrFieldDirCmp(char* s, char* t, int field)
{
	if ( (isalnum(s[field]) || isspace(s[field])) && (isalnum(t[field]) || isspace(t[field])))
	{
		if (s[field] == t[field])
			return 0;
	}
	return s[field] - t[field];
}

int StrFieldCmp(char* s, char* t, int field)
{
	if (s[field] == t[field])
		return 0;

	return s[field] - t[field];
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

void detab2CmdLine2(int argc, char* argv[])
{
	int c, ac, tabStop = TABSTOP, mCol = 4, nCol = 2;

	while (--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+'))
	{
		ac = *++argv[0]; /* Test 1st char after '-' only, then step to next arg */
		if (ac == 't')
		{
			tabStop = TRUE;
		}
		else
		{
			switch (c)
			{
			case '-':
				mCol = atoi2(argv[0]);
				break;
			case '+':
				nCol = atoi2(argv[0]);
				break;
			default:
				break;
			}
		}
	}
	if (argc == 0)
	{
		detab3(TABSTOP, mCol, nCol); /* default case */
	}
	else if (argc == 1 && tabStop == TRUE)
	{
		tabStop = atoi2(*argv);
		detab3(tabStop, mCol, nCol);
	}
	else
		printf("Usage: detab -m +n [-t <tabStop>]\n");

	return;
}

// Replace tabs with spaces
void detab3(int tabStop, int mCol, int nCol)
{
	int i, ri, j, m;
	char line[MAXLINE];
	char replaced[MAXLINE];

	while (getLine(line, MAXLINE) > 0)
	{
		m = mCol;
		for (i = 0, ri = 0; line[i] != '\0'; ++i)
		{
			if (m > 0) /* Processing to begin only after mCol */
 			{
				--m; /* Just copy str as is until mCol */
				goto CopyString;
			}

			if (line[i] == '\t' && (((i+1)%nCol) == 0)) /* tab at every nCol column */
			{
				for (j = 0; j < tabStop; ++j)
				{
					if (ri < MAXLINE - 1)
						replaced[ri + j] = ' ';
				}
				ri += tabStop;
				continue;
			}
			
CopyString:
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

void entab2CmdLine2(int argc, char* argv[])
{
	int c, ac, tabStop = TABSTOP, mCol = 4, nCol = 2;

	while (--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+'))
	{
		ac = *++argv[0]; /* Test 1st char after '-' only, then step to next arg */
		if (ac == 't')
		{
			tabStop = TRUE;
		}
		else
		{
			switch (c)
			{
			case '-':
				mCol = atoi2(argv[0]);
				break;
			case '+':
				nCol = atoi2(argv[0]);
				break;
			default:
				break;
			}
		}
	}
	if (argc == 0)
	{
		entab3(TABSTOP, mCol, nCol); /* default case */
	}
	else if (argc == 1 && tabStop == TRUE)
	{
		tabStop = atoi2(*argv);
		entab3(tabStop, mCol, nCol);
	}
	else
		printf("Usage: detab -m +n [-t <tabStop>]\n");

	return;
}

// Lets do integer division on space string and 
// tabstop (length of tab), find out how many tabs
// are required to fill in for the space string
// as a integer number. The remainder is the number
// of spaces to be filled in.
#define IN	1
#define OUT	0
void entab3(int tabStop, int mCol, int nCol)
{
	int i, ri, j, state, spcCount, tabCount, m;
	char line[MAXLINE];
	char replaced[MAXLINE];

	while (getLine(line, MAXLINE) > 0)
	{
		state = OUT;
		spcCount = 0;
		m = mCol;
		for (i = 0, ri = 0; line[i] != '\0'; ++i)
		{
			if (--m > 0) /* Processing to begin only after mCol */
			{
				/* Just copy str as is until mCol */
				replaced[ri++] = line[i];
				continue;
			}

			if (state == OUT && line[i] == ' ')
			{
				state = IN;
				++spcCount;
			}
			else if (state == OUT && line[i] != ' ')
			{
				replaced[ri++] = line[i];
			}
			else if (state == IN && line[i] != ' ')
			{
				state = OUT;
				tabCount = spcCount / tabStop;
				if (tabCount % nCol != 0) /* Only for every nCol tabs */
				{
					tabCount -= (tabCount % nCol); /* Reduce tabs by remainder to fit nCol */
				}
				for (j = 0; j < tabCount; ++j)
				{
					replaced[ri++] = '\t';
					//replaced[ri++] = '#';
					spcCount -= tabStop;
				}
				for (j = 0; j < spcCount; ++j)
				{
					replaced[ri++] = ' ';
					//replaced[ri++] = '$';
				}
				spcCount = 0;
				replaced[ri++] = line[i];
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

void TailCmdLine(int argc, char* argv[])
{
	int nL, found = FALSE;
	char* pEnd = NULL;

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		/* Move past 1st char '-', to access number */
		if (!found)
		{
			nL = strtol(++argv[0], &pEnd, 10);
			if (!strlen(pEnd))
				found = TRUE;
			else
				break;
		}
		else
			break;
	}
	if (argc == 0 && found == TRUE)
	{
		TailPrintLastNLines(nL); /* Value as read from arg list */
	}
	else if (argc == 0)
	{
		TailPrintLastNLines(10); /* Default value */
	}
	else
		printf("Usage: tail [-n nLines]\n");
	
	return;
}

void TailPrintLastNLines(int nLines)
{
	int i, dbIn;
	char line[MAXLINE] = { NUL };
	char** dbuf;

	if (NULL == (dbuf = malloc(sizeof(char*) * nLines)))
	{
		printf("1.Memory allocation error\n");
		return;
	}
	for (i = 0, dbIn = 0; getline4(line, MAXLINE) > 0; ++i)
	{
		AppendStrToBuffer(dbuf, line, &dbIn, nLines);
	}
	for (i = 0; i < dbIn; ++i)
	{
		printf("%s", dbuf[i]);
		free(dbuf[i]);
	}
	free(dbuf);
	return;
}

void AppendStrToBuffer(char* dbuf[], char line[], int* dbIn, int nLines)
{
	int i;

	if (*dbIn <= nLines - 1)
	{
		if (NULL == (dbuf[*dbIn] = malloc(sizeof(char) * (strlen(line) + 1))))
		{
			printf("2.Memory allocation error\n");
			return;
		}
		strcpy(dbuf[*dbIn], line);
		++*dbIn;
	}
	else
	{
		free(dbuf[0]);
		for (i = 1; i <= nLines - 1; ++i)
		{
			dbuf[i - 1] = dbuf[i];
		}
		if (NULL == (dbuf[nLines - 1] = malloc(sizeof(char) * (strlen(line) + 1))))
		{
			printf("3.Memory allocation error\n");
			return;
		}
		strcpy(dbuf[nLines - 1], line);
	}
	return;
}

void SortInputLines2(int argc, char* argv[])
{
	int c, nlines, skip = FALSE, numeric = FALSE, reverse = FALSE,\
			nocase = FALSE, dir = FALSE, field = 0;
	int (*Callback)(void*, void*) = NULL;
	int (*Callback2)(void*, void*, int) = NULL;

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		while (c = *++argv[0]) /* Option(s) in single arg eg. -dfn vs. -d -f -n */
		{
			switch (c)
			{
			case 'f':
				nocase = TRUE;
				break;
			case 'n':
				numeric = TRUE;
				break;
			case 'r':
				reverse = TRUE;
				break;
			case 'd':
				dir = TRUE;
				break;
			case 'F':
				field = atoi(++argv[0]);
				skip = TRUE;
				break;
			default:
				printf("Usage: sort [-r] [-n] [-f] [-d] [-F<Num Starting at 1>]\n");
				return;
			}
			if (skip == TRUE) /* Skip reading the current arg, move to next */
			{
				skip = FALSE;
				break;
			}
		}
	}

	if ((nlines = ReadLines(linePtr, MAXLINES)) >= 0)
	{
		if (!field)
		{
			/* Function callback builder */
			Callback = (int (*)(void *, void *))(numeric ? \
				(reverse ? numcmp2 : numcmp) \
				:(reverse ? StrCmpRev : (nocase ? \
					dir ? StrDirCaseCmp : StrCaseCmp \
					: dir ? StrDirCmp : StrCmpPtr)));

			/* In the call to Qsort cast to void* is required to make it generic */
			QuickSort2((void**)linePtr, 0, nlines - 1, /* Cast arg1 to 'void**' */ \
				(int (*)(void*, void*))/* Cast func args to 'void*' */Callback);
		}
		else
		{
			Callback2 =(int (*)(void*, void*, int)) (numeric ? \
				(reverse ? numcmp2Field : numcmpField) \
				:(reverse ? StrFieldCmpRev : (nocase ? \
					dir ? StrFieldDirCaseCmp : StrFieldCaseCmp \
					: dir ? StrFieldDirCmp : StrFieldCmp)));
				
			QuickSort3((void**)linePtr, 0, nlines - 1, /* Cast arg1 to 'void**' */ \
				(int (*)(void*, void*, int))/* Cast func args to 'void*' */Callback2, field - 1);
		}

		WriteLines(linePtr, nlines);
	}
	else
	{
		printf("Error: Input too big to sort\n");
	}
	return;
}

void QuickSort2(void* v[], int left, int right, int (*cmp)(void*, void*))
{
	int i, pivot;

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	pivot = left;
	for (i = left + 1; i <= right; ++i)
	{
		/* Calling the caller specified comparison func. makes this Qsort generic */
		if ((*cmp)(v[i], v[left]) < 0)
		{
			swap(v, ++pivot, i);
		}
	}
	swap(v, left, pivot);
	QuickSort2(v, left, pivot - 1, cmp);
	QuickSort2(v, pivot + 1, right, cmp);
	return;
}

void QuickSort3(void* v[], int left, int right, int (*cmp)(void*, void*, int), int field)
{
	int i, pivot;

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	pivot = left;
	for (i = left + 1; i <= right; ++i)
	{
		/* Calling the caller specified comparison func. makes this Qsort generic */
		if ((*cmp)(v[i], v[left], field) < 0)
		{
			swap(v, ++pivot, i);
		}
	}
	swap(v, left, pivot);
	QuickSort3(v, left, pivot - 1, cmp, field);
	QuickSort3(v, pivot + 1, right, cmp, field);
	return;
}

/* User implemented cmp function to be passed to Qsort. */
int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if(v1 > v2)
		return 1;
	else
		return 0;
}

int numcmpField(char* s1, char* s2, int field)
{
	double v1, v2;
	char tmpStr[2] = { NUL };

	strncpy(tmpStr, s1 + field, 1);
	v1 = atof(tmpStr);
	strncpy(tmpStr, s2 + field, 1);
	v2 = atof(tmpStr);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* User implemented cmp function to be passed to Qsort. (Reverse Sort) */
int numcmp2(char* s1, char* s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return 1;
	else if (v1 > v2)
		return -1;
	else
		return 0;
}

/* Reverse sort comparion */
int numcmp2Field(char* s1, char* s2, int field)
{
	double v1, v2;
	char tmpStr[2] = { NUL };

	strncpy(tmpStr, s1 + field, 1);
	v1 = atof(tmpStr);
	strncpy(tmpStr, s2 + field, 1);
	v2 = atof(tmpStr);
	if (v1 < v2)
		return 1;
	else if (v1 > v2)
		return -1;
	else
		return 0;
}
/* Generic version of swap, works with any user-specified type */
void swap(void* v[], int i, int j)
{
	void* tmp;
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
	return;
}
