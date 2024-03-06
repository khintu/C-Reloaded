#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <c-project.h>

// Single stack of char(s) with top index
int itop;
int stack[MAXDEPTH];

extern char glbLine[];

void testGlbExtnFunc(void)
{
	extern char glbLine[];

	printf("%s", glbLine);
	return;
}

void testGlbExtnFunc2(void)
{
	printf("%s", glbLine);
	return;
}

// Replace tabs with spaces
// ri has to be less than the last index MAXLINE -1 
// as MAXLINE-1 is reserved for NUL string character
void detab(void)
{
	int i, ri, j;
	char line[MAXLINE];
	char replaced[MAXLINE];

	while (getLine(line, MAXLINE) > 0)
	{
		for (i = 0, ri = 0; line[i] != '\0'; ++i)
			if (line[i] == '\t')
			{
				for (j = 0; j < TABSTOP; ++j)
				{
					if (ri < MAXLINE - 1)
						replaced[ri + j] = ' ';
				}
				ri += TABSTOP;
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

// Lets do integer division on space string and 
// tabstop (length of tab), find out how many tabs
// are required to fill in for the space string
// as a integer number. The remainder is the number
// of spaces to be filled in.
#define IN	1
#define OUT	0
void entab(void)
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
				tabCount = spcCount / TABSTOP;
				for (j = 0; j < tabCount; ++j)
				{
					replaced[ri] = '\t';
					//replaced[ri] = '#';
					++ri;
					spcCount -= TABSTOP;
				}
				for (j = 0; j < spcCount; ++j)
				{
					replaced[ri] = ' ';
					//replaced[ri] = '$';
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

// fold line into one or more folded lines
// before nth character after last non-blank
// If strlen is < nthChar then no string break
// hence no output.
// TBD - Use recusion for partitioning/balancing
// and glbNthChar for advancing in recursion.
void foldNaive(const int nthChar)
{
	int i, j, j1, fi;
	char line[MAXLINE];
	char foldLine[MAXLINE];

	if (nthChar <= 1 || nthChar >= MAXLINE)
	{
		printf("fold() error: Limits violated, nothing to fold\n");
		return;
	}

	while (getLine(line, MAXLINE) > 0)
	{
		for (i = 0, fi = 0, j1 = 0; line[i] != '\0'; ++i)
		{
			if (i == nthChar - 1)
			{
				for (fi = i - 1; fi >= 0 && line[fi] == ' '; --fi);
				if (fi >= 0)
				{
					for (j = 0; j <= fi; ++j)
						foldLine[j] = line[j];
					foldLine[j] = '\0';
				}
				printf("%s\n", foldLine);
				j = 0;
				foldLine[j] = line[i];
				++j;
			}
			if (i >= nthChar - 1)
			{
				foldLine[j1] = line[i];
				++j1;
			}
		}
		foldLine[j1] = '\0';
		printf("%s\n", foldLine);
	}
	return;
}

// Use recusion for balancing keywords like
// brakets, braces, quotes etc. Comments are
// not nested. Treat as normal text under outer
// comment opener.
static int gNthChar;
void fold2(const int nthChar)
{
	char line[MAXLINE];


	if (nthChar <= 1 || nthChar >= MAXLINE)
	{
		printf("fold() error: Limits violated, nothing to fold\n");
		return;
	}
	while (getLine(line, MAXLINE) > 0)
	{
		gNthChar = nthChar;
		fold2Recursive(line, 0, gNthChar);
	}
	return;
}

void fold2Recursive(char line[], const int startIdx, const int nthIdx)
{
	int i, j, j1, fi;
	char foldLine[MAXLINE];

	for (i = startIdx, fi = 0, j1 = 0; line[i] != '\0'; ++i)
	{
		if (i == nthIdx - 1)
		{
			for (fi = i - 1; fi >= startIdx && line[fi] == ' '; --fi);
			if (fi >= startIdx)
			{
				for (j = 0; j <= fi - startIdx; ++j)
					foldLine[j] = line[j + startIdx];
				foldLine[j] = '\0';
			}
			printf("%s\n", foldLine);
			// non-recursive case (base case), last string to print
			if (stringLength(line + i) <= gNthChar)
			{
				j = 0;
				foldLine[j] = line[i];
				++j;
			}
			// recursive to fold
			else
			{
				fold2Recursive(line, i, i + gNthChar);
				break;
			}
		}
		// last string to print
		if (i >= nthIdx - 1)
		{
			foldLine[j1] = line[i];
			++j1;
		}
	}
	if (j1 != 0)
	{
		foldLine[j1] = '\0';
		printf("%s", foldLine);
	}
	return;
}

void balanceTokens(void)
{
	int ln = 0, cn, c, i;
	char line[MAXLINE];

	initialize();

	while (getLine(line, MAXLINE) > 0)
	{
		++ln;
		for (i = 0, cn = 0; line[i] != '\0'; ++i)
		{
			++cn;
			// Token 1
			if (line[i] == '\'')
			{
				if (itop >= 0 && stack[itop] == '\'')
				{
					c = pop();
				}
				else
				{
					push(line[i]);
				}
			}
			// Token 2
			else if (line[i] == '\"')
			{
				if (itop >= 0 && stack[itop] == '\"')
				{
					c = pop();
				}
				else
				{
					push(line[i]);
				}
			}
			// Token 3
			else if (line[i] == '{')
			{				
				push(line[i]);
			}
			// Token 4
			else if (line[i] == '}')
			{				
				if (itop >= 0 && stack[itop] == '{')
				{
					c = pop();
				}
				else
				{
					printf("Error: unbalanced %c at ln %d, col %d\n", \
						line[i], ln, cn);
					return;
				}
			}
			// Token 5
			else if (line[i] == '[')
			{
				push(line[i]);
			}
			// Token 6
			else if (line[i] == ']')
			{			
				if (itop >= 0 && stack[itop] == '[')
				{
					c = pop();
				}
				else
				{
					printf("Error: unbalanced %c at ln %d, col %d\n", \
						line[i], ln, cn);
					return;
				}
			}
			// Token 7
			else if (line[i] == '(')
			{
				push(line[i]);
			}
			// Token 8
			else if (line[i] == ')')
			{				
				if (itop >= 0 && stack[itop] == '(')
				{
					c = pop();
				}
				else
				{
					printf("Error: unbalanced %c at ln %d, col %d\n", \
						line[i], ln, cn);
					return;
				}
			}
			// Everything else
			else
			{
				// Do something intelligent or nothing
				
			}

			// Post processing section
		}
	}
	if (itop > -1)
	{
		printf("Balancing error: stack unwind\n");
		for (i = 0; (c = pop()) >= 0; ++i)
			printf("%c\n", c);
	}
	return;
}

/* Recursive Descent Parser */

#define MAXTOKEN	100

enum { NAME, PARENS, BRACKETS };

int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last token string */
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000]; /* output string */

/* Parse a declarator */
void ParserDcl(void)
{
	int ns;

	for (ns = 0; ParserGetToken() == '*'; ns++) /* count optional *'s */
		;
	ParserDirDcl();  /* DirectDcl */
	while (ns-- > 0)
		strcat(out, " pointer to");
	return;
}

/* Parse a direct declarator */
void ParserDirDcl(void)
{
	int type;

	if (tokentype == '(') /* (dcl) */
	{
		ParserDcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	}
	else if (tokentype == NAME)  /* variable name */
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");

	/* direct-dcl() And direct-dcl[] */
	while ((type = ParserGetToken()) == PARENS || type == BRACKETS)
	{
		if (type == PARENS)
			strcat(out, " function returning");
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
	return;
}

int ParserGetToken(void)
{
	int c;
	char* p = token;

	while ((c = getch()) == ' ' || c == '\t') /* Discard white spaces */
		;
	if (c == '(')  /* Returns '()' or '(' */
	{
		if ((c = getch()) == ')')
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else
		{
			ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[') /* Returns '[(a-z)*]' */
	{
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c)) /* Returns 'a-z(0-9|a-z)*' */
	{
		for (*p++ = c; isalnum(c = getch()) ; )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
		return tokentype = c;
}

void RecursiveDescentParser(void)
{
	while (ParserGetToken() != EOF)
	{
		strcpy(datatype, token); /* 1st token on line is datatype */
		out[0] = '\0';
		ParserDcl();  /* Parse rest of the line */
		if (tokentype != '\n')
			printf("RDP - syntax error\n");
		printf("RDP - %s: %s %s\n", name, out, datatype);
	}
	return;
}