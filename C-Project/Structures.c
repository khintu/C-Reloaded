#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <c-project.h>

#define XMAX	100
#define YMAX	100

struct point {
	int x;
	int y;
};

struct rect {
	struct point pt1;
	struct point pt2;
};

/* makePoint: make a point from x and y components */
struct point makePoint(int x, int y)
{
	struct point tmp;
	tmp.x = x;
	tmp.y = y;
	return tmp;
}

/* addPoint: add two points */
struct point addPoint(struct point p1, struct point p2)
{
	p1.x += p2.x;
	p1.y += p2.y;
	return p1;
}

/* ptInRect: return 1 if p in rect, 0 if not */
int ptInRect(struct point pt, struct rect r)
{
	return pt.x >= r.pt1.x && pt.y >= r.pt1.y
				&& pt.x < r.pt2.x && pt.y < r.pt2.y;
}

/* canonRect: canonocalize coordinates of rectangle */
struct rect canonRect(struct rect r)
{
	struct rect temp;

	temp.pt1.x = MIN(r.pt1.x, r.pt2.x);
	temp.pt1.y = MIN(r.pt1.y, r.pt2.y);
	temp.pt2.x = MAX(r.pt1.x, r.pt2.x);
	temp.pt2.y = MAX(r.pt1.y, r.pt2.y);
	return temp;
}

void testPtr2Struct(void)
{
	struct {
		int len;
		char* str;
	} origin[2] = { {5, "Uncle"}, {5, "Aunty"} }, *p;
	p = origin;
	
	printf("%d\n", ++p->len);
	printf("%c\n", *p->str);
	printf("%c\n", *p->str++);	// increment str after accessing *str
	printf("%c\n", (*p->str)+1); // Access violation on (*p->str)++, cannot alter string literal
	printf("%c\n", *p++->str); // increments p NOT str
	printf("%c\n", *++p->str); // increments str NOT p
	printf("%c\n", *(++p)->str); // Access violation, p already at origin[1]
	return;
}

void testStructuresDecl(void)
{
	printf("%zu\n", sizeof(struct point));

	struct rect screen;
	struct point middle;

	screen.pt1 = makePoint(0, 0);
	screen.pt2 = makePoint(XMAX, YMAX);
	middle = makePoint((screen.pt1.x + screen.pt2.x) / 2,
										(screen.pt1.y + screen.pt2.y) / 2);
	printf("%d\n", ptInRect(middle, screen));
	screen = canonRect(screen);
	testPtr2Struct();
	return;
}

/* Keyword Counting Program */

#define MAXWORD	100
#define NKEYS	(sizeof(keytab)/sizeof(struct key))

struct key {
	char* word;
	int count;
} keytab[] = 
{
	{STRKEY(auto), 0},
	{STRKEY(break), 0},
	{STRKEY(case), 0},
	{STRKEY(char), 0},
	{STRKEY(const), 0},
	{STRKEY(continue), 0},
	{STRKEY(default), 0},
	{STRKEY(int), 0},
	{STRKEY(unsigned), 0},
	{STRKEY(void), 0},
	{STRKEY(volatile), 0},
	{STRKEY(while), 0}
};

/* getword: get next word or character from input */
int kcpGetWordBetter(char* word, int lim)
{
	int c, ac, strconst = FALSE, comment = FALSE;
	char* w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF) /* write to buffer */
		*w++ = c;
	if (!(isalpha(c) || c == '_' || c == '"'|| c == '/')) /* keyword starts with alpha not digit, return digit or EOF */
	{
		*w = NUL;
		return c;
	}

	if (c == '"') /* string constant starting */
		strconst = TRUE;
	else if (c == '/' && (ac = getch()) == '*') /* comment starting */
	{
		comment = TRUE;
		*w++ = ac;
	}
	else if (c == '/' && ac != '*')
		ungetch(ac);

	for (c = 0; --lim > 0 && c != EOF; w++) /* Only after word is confirmed from above */
	{
		if (!(isalnum(c = *w = getch()) || *w == '_' || strconst == TRUE || comment == TRUE))
		{
			ungetch(*w);
			break;
		}
		if (comment == TRUE)
		{
			if (*w == '*' && (ac = getch()) == '/')
			{
				comment = FALSE;
				*++w = ac;
				w++;
				break;
			}
			else if (*w == '*' && ac != '/')
				ungetch(ac);
			else if (ac == EOF)
			{
				c = EOF;
				break;
			}
		}
		if (strconst == TRUE && *w == '"')
		{
			strconst = FALSE;
			w++;
			break;
		}
	}
	*w = NUL;
	if (c == EOF)
	{
		word[0] = NUL;
		return c;
	}
	return word[0];
}

/* getword: get next word or character from input */
int kcpGetWord(char* word, int lim)
{
	int c;
	char* w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF) /* write to buffer */
		*w++ = c;
	if (!isalpha(c)) /* keyword starts with alpha not digit, return digit or EOF */
	{
		*w = NUL;
		return c;
	}
	for ( ; --lim > 0; w++) /* Only after word is confirmed from above */
		if (!isalnum(*w = getch()))
		{
			ungetch(*w);
			break;
		}
	*w = NUL;
	return word[0];
}

/* binseaarch: find word in sorted tab[NKEYS] */
int kcpBinSearch(char* word, struct key tab[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high)
	{
		mid = (low + high) / 2;
		if (strcmp(word, tab[mid].word) > 0)
			low = mid + 1;
		else
			high = mid;
	}
	if (strcmp(word, tab[low].word) == 0)
		return low;
	return -1;
}

/* Count C keywords */
void keywordCouintingProgram(void)
{
	int n;
	char word[MAXWORD];

	while (kcpGetWordBetter(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
		{
			if ((n = kcpBinSearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
		}

	for (n = 0; n < NKEYS; ++n)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	return;
}