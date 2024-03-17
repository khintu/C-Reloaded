#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <c-project.h>

char glbLine[MAXLINE];

/* 
	getchar() is a blocking call, it wont return until the
	entire input from stdin has been read by it. Then it 
	returns the input stream one character at a time as
	an int and returns EOF on ^C not on newline. newline
	is used for unblocking it and making it return to user
	code. newline is also returned with the rest of the
	characters. On ^C it unblocks but returns only EOF not
	the	input text stream.
	Ctl-C interrupt causes -1 EOF return from getchar() if
	not handled the next call to getchar() will terminate
	the program with exit code 3221225786 (0xc000013a).
*/

void copyInputToOutput(void)
{
	int c;
	while ((c = getchar()) != EOF)
	{
		putchar(c);
	}
	//printf("\nValue of EOF expression %d\n", c = (getchar() != EOF));
	//printf("\nValue of EOF %d\n", EOF);
	return;
}

void countCharactersInInput(void)
{
	long nc = 0;
	int c;

	while ((c = getchar()) != EOF)
	{
		/* includes newlines */
		++nc;
	}
	printf("\n%ld\n", nc);
	return;
}

void countLinesInInput(void)
{
	int nl = 0, c;

	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
			++nl;
	}
	printf("\n%d\n", nl);
	return;
}

void countWhitespacesInInput(void)
{
	/* Count tabs, blanks and newlines */
	int nt = 0, nb = 0, nl = 0, c;

	while ((c = getchar()) != EOF)
	{
		if (c == '\t')
			++nt;
		else if (c == ' ')
			++nb;
		else if (c == '\n')
			++nl;
	}
	printf("Tabs %d, Blanks %d, Newlines %d\n", nt, nb, nl);
	return;
}

void replaceBlankStringWithBlank(void)
{
	int c, start = FALSE;
	while ((c = getchar()) != EOF)
	{
		if (c == ' ' && start == FALSE)
		{
			start = TRUE;
			putchar(c);
		}
		else if (start == TRUE && c == ' ') 
			continue;
		else
		{
			start = FALSE;
			putchar(c);
		}
	}
	return;
}

void copyInputReplaceSpecial(void)
{
	int c;
	
	while ((c = getchar()) != EOF)
	{
		if (c == '\t')
		{
			putchar('\\');
			putchar('t');
		}
		/* TBD - Terminal is not returning backspace */
		else if (c == '\b')
		{
			putchar('\\');
			putchar('b');
		}
		else if (c == '\\')
		{
			putchar('\\');
			putchar('\\');
		}
		else
			putchar(c);
	}
	return;
}

#define IN	1	/* inside a word */
#define OUT	0	/* outside a word */
void countWordsLinesCharsInInput(void)
{
	int nw, nl, nc, state, c;

	state = OUT;
	nw = nl = nc = 0;
	while ((c = getchar()) != EOF)
	{
		++nc;
		if (c == '\n')
			++nl;
		if (c == '\n' || c == '\t' || c == ' ')
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			++nw;
		}
	}
	printf("Words %d, Lines %d, Characters %d\n", nw, nl, nc);
	return;
}

void printInputOneWordPerLine(void)
{
	int state = OUT, c;
	
	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\t' || c == '\n')
		{
			if (state == IN)
				putchar('\n');
			state = OUT;		
		}
		else if (state == OUT)
				state = IN;

		if (state == IN)
			putchar(c);
	}
	return;
}

void wordsLengthsHistogram(void)
{
	int i, nw, windex, state, c;
	// 20 word count limit
	int wlen[20];

	for (i = 0; i < 20; ++i)
		wlen[i] = 0;

	state = OUT;
	nw = windex = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == '\n' || c == '\t' || c == ' ')
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			windex = nw;
			++wlen[windex];
			++nw;
		}
		else
			++wlen[windex];
	}

	for (i = 0; i < 20; ++i)
	{
		int j;
		printf("word %2d count %3d ", i + 1, wlen[i]);
		for (j = 0; j < wlen[i]; ++j)
			putchar('#');
		printf("\n");
	}
	return;
}
#undef IN
#undef OUT

void countDigitWhiteSpOther(void)
{
	int i, c, nwhite = 0, nother = 0;
	int ndigit[10];

	for (i = 0; i < 10; ++i)
		ndigit[i] = 0;

	while ((c = getchar()) != EOF)
	{
		if (c >= '0' && c <= '9')
			++ndigit[c - '0'];
		else if (c == '\t' || c == '\n' || c == ' ')
			++nwhite;
		else
			++nother;
	}

	for (i = 0; i < 10; ++i)
		printf("%d count %d\n", i, ndigit[i]);
	printf("whitespace %d, other %d\n", nwhite, nother);

	return;
}

void characterLengthsHistogram(void)
{
	int i, j, c;
	int nucase[26], nlcase[26], ndigit[10];

	for (i = 0; i < 26; ++i)
		nucase[i] = nlcase[i] = 0;
	for (i = 0; i < 10; ++i)
		ndigit[i] = 0;

	while ((c = getchar()) != EOF)
	{
		if (c >= 'A' && c <= 'Z')
			++nucase[c - 'A'];
		else if (c >= 'a' && c <= 'z')
			++nlcase[c - 'a'];
		else if (c >= '0' && c <= '9')
			++ndigit[c - '0'];
	}
	for (i = 0; i < 26; ++i)
	{
		printf("%c count %3d ", i + 'A', nucase[i]);
		for (j = 0; j < nucase[i]; ++j)
			putchar('#');
		printf("\n");
	}
	for (i = 0; i < 26; ++i)
	{
		printf("%c count %3d ", i + 'a', nlcase[i]);
		for (j = 0; j < nlcase[i]; ++j)
			putchar('#');
		printf("\n");
	}
	for (i = 0; i < 10; ++i)
	{
		printf("%c count %3d ", i + '0', ndigit[i]);
		for (j = 0; j < ndigit[i]; ++j)
			putchar('#');
		printf("\n");
	}
	return;
}

/* 
	return lenght of line, EOF is zero return, '\n'
	is return value of input line + '\n' character,
	return array is always '\0' terminated.
*/
int getLine(char s[], int lim)
{
	int i, c;

	if (lim <= 2)
	{
		printf("getLine: Input buffer t00 small\n");
		s[0] = '\0';
		return 0;
	}

	for (i = 0, c = 0; \
		i < lim - 2 && (c = getchar()) != EOF && c != '\n'; \
		++i)
		s[i] = c;

	if (c != EOF)
	{
		s[i] = '\n';
		++i; // from index to length
	}
	s[i] = '\0';
	return i;
}

void printLongestInputLine(void)
{
	int len, max = 0;
	char line[MAXLINE];
	char longest[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0)
		if (len > max)
		{
			max = len;
			copyString(longest, line);
		}
	if (max > 0)
		printf("max length %d, string <%s>\n", max, longest);
	return;
}

void printInputLinesGreater(void)
{
	int len;
	char line[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0)
		if (len > 80)
		{
			printf("max length %d, string <%s>\n", len, line);
		}
	return;
}

void removeSpecialFromInput(void)
{
	int len;
	char line[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0)
	{
		if (TRUE == isBlankString(line))
			continue;
		removeTrailingBlanks(line);
		printf("%s\n", line);
	}
	return;
}

void reverseInputLine(void)
{
	int len;
	char line[MAXLINE];

	while ((len = getLine(line, MAXLINE)) > 0)
	{
		reverseString(line);
		printf("%s\n", line);
	}
	return;
}

int getline3(char s[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

int getline2(char s[], int lim)
{
	int c, i = 0;
		
	while (1)
	{
		if (i < lim - 1)
			if ((c = getchar()) != EOF)
				if (c != '\n') {
					s[i] = c; ++i;
				}
				else
					break;
			else
				break;
		else
			break;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void longest(void)
{
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;
	while((len = getline2(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0)
		printf("%s", longest);
	return;
}

void printLowerToUpper(int argc, char* argv[])
{
	int c;

	if (strstr(argv[0], "Upper") != NULL)
		while ((c = getchar()) != EOF)
			putchar(toupper(c));
	else if (strstr(argv[0], "Lower") != NULL)
		while ((c = getchar()) != EOF)
			putchar(tolower(c));
	else
		printf("Unrecognized program name\n");
	return;
}

void printInputToOutput(void)
{
	int c, ln;

	ln = 0;
	while ((c = getchar()) != EOF)
	{
		if (isgraph(c) || isspace(c))
			putchar(c);
		else
			printf("%x", c);
		
		if (++ln == 10) /* line length is 10 */
		{
			putchar('\n');
			ln = 0;
		}
	}
	return;
}