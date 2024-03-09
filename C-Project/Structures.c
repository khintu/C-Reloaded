#include <stdio.h>
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
	printf("%c\n", (*p->str)+1);
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
	{STRKEY(unsigned), 0},
	{STRKEY(void), 0},
	{STRKEY(volatile), 0},
	{STRKEY(while), 0}
};

void keywordCouintingProgram(void)
{

	return;
}