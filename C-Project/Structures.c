#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
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
	else if (c == '/' && ac != '*') /* Not a keyword, return like before */
	{
		ungetch(ac);
		*w = NUL;
		return c;
	}

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
		else if (strconst == TRUE && *w == '"')
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
void keywordCountingProgram(void)
{
	int n;
	char word[MAXWORD] = { 0 };

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

/* Pointer to structure arithmetic and structure padding/packing */

/* Count C keywords; pointer version */
void keywordCountingProgram2(void)
{
	char word[MAXWORD] = { 0 };
	struct key* p;

	while(kcpGetWord(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
		{
			if ((p = kcpBinSearch2(word, keytab, NKEYS)) != NULL)
				p->count++;
		}

	for (p = keytab; p < keytab + NKEYS; ++p)
		if (p->count > 0)
			printf("%4d %s\n", p->count, p->word);
	return;
}

/* find word in tab[0]...tab[n-1] */
struct key* kcpBinSearch2(char* word, struct key* tab, int n)
{
	struct key* low = &tab[0];
	struct key* high = &tab[n]; /* 1st past the end is ok not illegal */
	struct key* mid;

	while (low < high)
	{
		/* All pointer arithmetic is in steps of sizeof(type) not single byte leading
		   to direct indexing into the array with each pointer */
		mid = low + (high - low) / 2; /* !! two pointers can only be sub'd not add'd !! */
		if (strcmp(word, mid->word) > 0)
			low = mid + 1;
		else
			high = mid;
	}
	if (strcmp(word, low->word) == 0)
		return low;
	return NULL;
}

/* Binary Tree - search and store all words from input in a ordered tree */

struct tnode {	/* the tree node */
	char* word;		/* points to text */
	int count;		/* number of occurences */
	struct tnode* left;	/* self-referential left child pointer */
	struct tnode* right;/* self-referential right child pointer */
};

/* addtree: add a node with w, at or below p */
struct tnode* BinTreeAddNode(struct tnode* p, char* w)
{
	int cond;

	if (p == NULL) /* Base case */
	{
		p = (struct tnode*)malloc(sizeof(struct tnode));
		if (p)
		{
			p->word = (char*)malloc(sizeof(char) * (strlen(w) + 1));
			if (p->word)
			{
				strcpy(p->word, w);
			}
			p->count = 1;
			p->left = p->right = NULL;
		}
	}
	else if ((cond = strcmp(w, p->word)) == 0) /* only 3 condn >, ==, < */
		p->count++;
	else if (cond < 0)
		p->left = BinTreeAddNode(p->left, w);
	else
		p->right = BinTreeAddNode(p->right, w);
	return p;
}

/* treeprint: in-order print of tree */
void BinTreePrint(struct tnode* p)
{
	if (p != NULL)
	{
		BinTreePrint(p->left);
		printf("%4d %s\n", p->count, p->word);
		BinTreePrint(p->right);
	}
	return;
}

/* word frequency count */
void WordFreqCount(void)
{
	struct tnode* root;
	char word[MAXWORD];

	root = NULL;
	while (kcpGetWord(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
		{
			root = BinTreeAddNode(root, word);
		}
	BinTreePrint(root);
	return;
}

/* Program to read C prog. and print alphabetically groups of similar variables
 in the first 6 or userdefined N number of characters. */
void GroupOfNamesIdentInNCmp(int argc, char* argv[])
{
	int c, ncount;

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		switch (c = *++argv[0])
		{
		case 'f':
			ncount = 1;
			break;
		default:
			printf("PrintVars: Illegal option %c\n", c);
			break;
		}		
	}
	if (argc != 1)
	{
		printf("Usage: PrintVars -f <NumOfCmp>\n");
	}
	else
	{
		ncount = atoi(argv[0]);
		PrintGroupsOfVarsNSizd(ncount);
	}
	return;
}

/* List of groups of word with a common 1st N characters */
struct lnode {
	struct tnode* root;
	struct lnode* next;
};

struct lnode* LstAddWrdToWordGrp(char *word, int ncount, struct lnode *group)
{
	struct lnode* p;
	//struct tnode* root;
	int found = FALSE;

	/* Create new group if word not found */
	for (p = group; p != NULL ; p = p->next)
	{
		if (strncmp(word, p->root->word, ncount) == 0)
		{
			p->root = BinTreeAddNode(p->root, word);
			found = TRUE;
			return group;
		}
	}
	if (!found)
	{
		if (!group)
		{
			group = (struct lnode*)malloc(sizeof(struct lnode));
			if (group)
			{
				group->root = NULL;
				group->next = NULL;
			}
			p = group;
		}
		else
		{
			for (p = group; p->next != NULL; p = p->next)
				;
			p->next = (struct lnode*)malloc(sizeof(struct lnode));
			if (p->next)
			{
				p->next->root = NULL;
				p->next->next = NULL;
			}
			p = p->next;
		}
		p->root = BinTreeAddNode(p->root, word);
	}
	return group;
}

void PrintGroupsOfVarsNSizd(int ncount)
{
	struct lnode* groups;
	
	char word[MAXWORD];
	
	groups = NULL;
	while (kcpGetWordBetter(word, MAXWORD) != EOF)
	{
		if (!((word[0] == '/' && word[1] == '*') || \
					 word[0] == '\"' || \
					 kcpBinSearch(word, keytab, NKEYS) != -1) \
				&& isalpha(word[0]))
		{
			groups = LstAddWrdToWordGrp(word, ncount, groups);
		}
	}
	for (struct lnode* p = groups; p != NULL; p = p->next)
	{
		printf("%c>>Next Group\n", p == groups ? NUL : '\n');
		BinTreePrint(p->root);
	}
	return;
}

/* Cross Referencer for printing all words in a document's list
	 of line numbers on which it occurs, remove noise words */
char* noiseWords[] =
{
	"and",
	"if",
	"is",
	"of",
	"or",
	"the",
	"to"
};

#define NNOISE	(sizeof(noiseWords) / sizeof(noiseWords[0]))

/* binseaarch: find word in sorted noiseWords[NNOISE] */
int CRBinSearch(char* word, char* noise[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high)
	{
		mid = (low + high) / 2;
		if (strcmp(word, noise[mid]) > 0)
			low = mid + 1;
		else
			high = mid;
	}
	if (strcmp(word, noise[low]) == 0)
		return low;
	return -1;
}

struct CRList {
	int lineNo;
	struct CRList* next;
};

struct CRTree {
	char* word;
	struct CRList* list;
	struct CRTree* left, * right;
};

struct CRList* CRListAddLn(struct CRList* p, int lineNo)
{
	struct CRList* q = NULL;

	if (p == NULL)
	{
		p = (struct CRList*)malloc(sizeof(struct CRList));
		if (p)
		{
			p->lineNo = lineNo;
			p->next = NULL;
		}
	}
	else
	{
		for (q = p; q->next != NULL; q = q->next)
			;
		q->next = (struct CRList*)malloc(sizeof(struct CRList));
		if (q->next)
		{
			q = q->next;
			q->lineNo = lineNo;
			q->next = NULL;
		}
	}
	return p;
}

/* addtree: add a node with w, at or below p */
struct CRTree* CRTreeAddNode(struct CRTree* p, char* w, int lineNo)
{
	int cond;

	if (p == NULL) /* Base case */
	{
		p = (struct CRTree*)malloc(sizeof(struct CRTree));
		if (p)
		{
			p->word = (char*)malloc(sizeof(char) * (strlen(w) + 1));
			if (p->word)
			{
				strcpy(p->word, w);
			}
			p->list = CRListAddLn(NULL, lineNo);
			p->left = p->right = NULL;
		}
	}
	else if ((cond = strcmp(w, p->word)) == 0) /* only 3 condn >, ==, < */
		p->list = CRListAddLn(p->list, lineNo);
	else if (cond < 0)
		p->left = CRTreeAddNode(p->left, w, lineNo);
	else
		p->right = CRTreeAddNode(p->right, w, lineNo);
	return p;
}

/* treeprint: in-order print of tree */
void CRTreePrint(struct CRTree* p)
{
	struct CRList* q = NULL;
	if (p != NULL)
	{
		CRTreePrint(p->left);
		printf("%s ", p->word);
		for (q = p->list; q != NULL; q = q->next)
			printf("%d%c", q->lineNo, q->next == NULL ? '\n': ',');
		CRTreePrint(p->right);
	}
	return;
}

/* getword: get next word or character from input */
int CRGetWord(char* word, int lim)
{
	int c;
	char* w = word;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c != EOF) /* write to buffer */
		*w++ = c;
	if (!isalpha(c)) /* keyword starts with alpha not digit, return digit or EOF */
	{
		*w = NUL;
		return c;
	}
	for (; --lim > 0; w++) /* Only after word is confirmed from above */
		if (!isalnum(*w = getch()))
		{
			ungetch(*w);
			break;
		}
	*w = NUL;
	return word[0];
}

/* Main program to read from input document to cross-reference */
void CrossReferencerProgam(void)
{
	struct CRTree* root;
	char word[MAXWORD];
	int lineNo = 1;

	root = NULL;
	while (CRGetWord(word, MAXWORD) != EOF)
	{
		if (word[0] == '\n')
			lineNo++;
		else if (CRBinSearch(word, noiseWords, NNOISE) != -1)
		{
			continue;
		}
		else if (isalpha(word[0]))
		{
			root = CRTreeAddNode(root, word, lineNo);
		}
	}
	CRTreePrint(root);
	return;
}