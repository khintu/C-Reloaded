#include <stdio.h>
#include <c-project.h>

// Single stack of char(s) with top index
int itop;
int stack[MAXDEPTH];

#if 0
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
#endif
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

// Balancing tokens '',"",(),[],{},/* */, in a C program
// Simple syntax checking. State machine with stack, solu.
/*enum STATE_MACH {
	START_STATE = 0,
	SINGLE_QUOTE_IN,
	SINGLE_QUOTE_OUT,
	DOUBLE_QUOTE_IN,
	DOUBLE_QUOTE_OUT,
	BRACE_IN,
	BRACE_OUT,
	SQRBRKT_IN,
	SQRBRKT_OUT,
	PARNTHS_IN,
	PARNTHS_OUT,
	FINAL_STATE
};

void balanceTokens(void)
{
	int ln = 0, cn, c, i;
	enum STATE_MACH sm = START_STATE;
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
				if (itop >= 0)
				{
					if (stack[itop] != '\'')
					{
						sm = SINGLE_QUOTE_IN;
						push(line[i]);
					}
					else
					{
						sm = SINGLE_QUOTE_OUT;
						c = pop();
					}
				}
			}
			// Token 2
			else if (line[i] == '\"')
			{
				sm = DOUBLE_QUOTE_IN;
				push(line[i]);
			}
			// Token 3
			else if (line[i] == '{')
			{
				sm = BRACE_IN;
				push(line[i]);
			}
			// Token 4
			else if (line[i] == '}')
			{
				sm = BRACE_OUT;
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
				if (sm == START_STATE)
				{
					sm = SQRBRKT_IN;
					push(line[i]);
				}
				else
				{
					printf("Error: unbalanced %c at ln %d, col %d\n", \
						line[i], ln, cn);
					return;
				}
			}
			// Token 6
			else if (line[i] == ']')
			{
				if (sm == SQRBRKT_IN)
				{
					sm = SQRBRKT_OUT;
				}
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
				sm = PARNTHS_IN;
				push(line[i]);
			}
			// Token 8
			else if (line[i] == ')')
			{
				sm = PARNTHS_OUT;
				c = pop();
			}
			// Everything else
			else
			{
				// Do something intelligent or nothing
				sm = START_STATE;
			}

			// Post processing section
		}
	}
	if (itop > -1)
	{
		printf("Balancing error: stack unwind\n");
		for (i = 0; (c = pop()) >= 0 ; ++i)
			printf("%c\n", c);
	}
	return;
}
*/

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
