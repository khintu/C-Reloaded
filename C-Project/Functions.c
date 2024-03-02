#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <c-project.h>

int findLinesMatchgPattrn(char p[])
{
	int found;
	char line[MAXLINE];

	found = 0;
	while(getline4(line, MAXLINE) > 0)
		if (strindex(line, p) >= 0)
		{
			printf("%s", line);
			found++;
		}
	return found;
}

int getline4(char s[], int lim)
{
	int i, c;

	i = 0; c = '\0';
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return i;
}

int strindex(char s[], char t[])
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; ++i)
	{
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

int strrindex(char s[], char t[])
{
	int i, fndi, rmi, lt;
	
	lt = stringLength(t);
	for (i = 0, fndi = 0, rmi = -1; s[i] != '\0'; )
	{
		if ((fndi = strindex(s + i, t)) >= 0)
		{
			rmi = fndi + i;
			i = rmi + lt;
		}
		else
			++i;
	}
	return rmi;
}

double Atof(char s[])
{
	double val, power;
	int sign, i;

	for (i = 0; isspace(s[i]); ++i)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		++i;
	for (val = 0.0; isdigit(s[i]); ++i)
		val = val * 10.0 + s[i] - '0';
	if (s[i] == '.')
		++i;
	for (power = 1.0; isdigit(s[i]); ++i)
	{
		val = val * 10.0 + s[i] - '0';
		power *= 10.0;
	}
	return sign * val / power;
}

double atofE(char s[])
{
	double val, power;
	int sign, i, valE;
	
	for (i = 0; isspace(s[i]); ++i)
		;
	// Deconstruct mantissa
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		++i;
	for (val = 0.0; isdigit(s[i]); ++i)
		val = val * 10.0 + s[i] - '0';
	if (s[i] == '.')
		++i;
	for (power = 1.0; isdigit(s[i]); ++i)
	{
		val = val * 10.0 + s[i] - '0';
		power *= 10.0;
	}
	val *= sign / power;
	// Deconstruct exponent
	if (s[i] == 'e' || s[i] == 'E')
		++i;
	sign = (s[i] == '-') ? -1 : 1, ++i;

	for (valE = 0; isdigit(s[i]); ++i)
		valE = valE * 10 + s[i] - '0';
	val *= powerf(10, valE*sign);
	return val;
}

int sp = 0;					/* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;				/* next free position in buf */
int signFlag = FALSE; /* Sign field in getoperator */
int spVar = 0;			/* next free stack position on varS */
int varS[MAXVAL];	/* variable stack */

/* Hint: sp value is from 1..MAXVAL, not from 0..MAXVAL-1. 
	It cannot show top value, pop push for that */

void clearStck(void)
{
	sp = 0;
	return;
}

void printTopStck(void)
{
	if (sp >= 1 && sp <= MAXVAL)
		printf("%.8g\n", val[sp - 1]);
	else
		printf("Stack Top Error sp=%d\n", sp);
	return;
}

void dupTopStck(void)
{
	if (sp >= 1 && sp <= MAXVAL)
		push2(val[sp - 1]);
	else
		printf("Stack Dup Error sp=%d\n", sp);
	return;
}

void swpTop2Stck(void)
{
	if (sp >= 1 && sp <= MAXVAL && sp >= 2)
	{
		double tmp = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = tmp;
	}
	else
		printf("Stack Swap Error sp=%d\n", sp);
	return;
}

/* push f onto value stack */
void push2(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, cant push %g\n", f);
	return;
}
/* pop and return top value from stack */
double pop2(void)
{
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* push f onto variable stack */
void push3(char c)
{
	if (spVar < MAXVAL)
		varS[spVar++] = c;
	else
		printf("error: var stack full, cant push %c\n", c);
	return;
}

/* pop and return top value from variables */
char pop3(void)
{
	if (spVar > 0)
		return varS[--spVar];
	else
	{
		printf("error: var stack empty\n");
		return NUL;
	}
}

/* get a (possibly push back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back into input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* get next operator or numeric operand */
int getoperator(char s[])
{
	int i, c, ac;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
	{
		if (signFlag == TRUE)
			signFlag = FALSE;
	}
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
	{
		if (c == '-') /* post processing for sign */
		{
			if (isdigit(ac = getch()))
				signFlag = TRUE;
			ungetch(ac);
		}
		return c;  /* not a number, operator */
	}
	i = 0;
	if (signFlag == TRUE) /* put sign on number */
	{
		int tmp = s[0];
		s[0] = '-';
		s[1] = tmp;
		s[2] = '\0';
		i = 1;
	}
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0'; /* clamp the first non-digit with NUL */
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

/* Get input one full line at a time */
int getoperator2(char s[])
{
	int i, c;
	static int nli;
	static char nl[MAXLINE];

	while (nl[nli] != NUL || (getline4(nl, MAXLINE) > 0 && !(nli = 0)))
	{
		while ((s[0] = c = nl[nli++]) == ' ' || c == '\t')
			;
		s[1] = '\0';
		if (!isdigit(c) && c != '.')
			return c;

		i = 0;
		if (isdigit(c)) /* collect integer part */
			while (isdigit(s[++i] = c = nl[nli++]))
				;
		if (c == '.') /* collect fraction part */
			while (isdigit(s[++i] = c = nl[nli++]))
				;
		s[i] = '\0'; /* clamp the first non-digit with NUL */
		return NUMBER;
	}
	return EOF;
}

void reversePolishCalc(int argc, char* argv[])
{
	int type;
	double op1, op2;
	char s[MAXOP];
	double var[26] = {0.0f};	/* 26 single letter lower case variables */

	while ((type = getoperator3(s, &argc, &argv)) != EOF)
	{
		if (islower(type))
		{
			if (sp >= 1 && sp <= MAXVAL) /* Case 1: assign to variable */
			{
				var[type - 'a'] = pop2(); /* Remove from val stack, as we moved val[sp] to var[a-z] */
			}
			push3(type); /* Case 2: use value of variable */
			continue;
		}
		switch (type)
		{
		case NUMBER:
			push2(Atof(s));
			break;
		case '+':
			if (spVar >= 1 && spVar <= MAXVAL)
			{
				op2 = var[pop3() - 'a'];
				op1 = var[pop3() - 'a'];
				push2(op1 + op2);
			}
			else
				push2(pop2() + pop2());
			break;
		case '*':
			if (spVar >= 1 && spVar <= MAXVAL)
			{
				op2 = var[pop3() - 'a'];
				op1 = var[pop3() - 'a'];
				push2(op1 * op2);
			}
			else
				push2(pop2() * pop2());
			break;
		case '-':
			if (signFlag != TRUE)
			{
				if (spVar >= 1 && spVar <= MAXVAL)
				{
					op2 = var[pop3() - 'a'];
					op1 = var[pop3() - 'a'];
				}
				else 
				{
					op2 = pop2();
					op1 = pop2();
				}
				push2(op1 - op2);
			}
			break;
		case '/':
			if (spVar >= 1 && spVar <= MAXVAL)
			{
				op2 = var[pop3() - 'a'];
				op1 = var[pop3() - 'a'];
			}
			else
			{
				op2 = pop2();
				op1 = pop2();
			}
			if (op2 != 0.0)
				push2(op1 / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '%':
			if (spVar >= 1 && spVar <= MAXVAL)
			{
				op2 = var[pop3() - 'a'];
				op1 = var[pop3() - 'a'];
			}
			else
			{
				op2 = pop2();
				op1 = pop2();
			}
			if (op2 != 0.0)
				push2(((int)op1 % (int)op2));
			else
				printf("error: zero divisor in mod operator\n");
			break;
		case PRNTTOP:
			printTopStck();
			break;
		case DUPLTOP:
			dupTopStck();
			break;
		case SWPTOP2:
			swpTop2Stck();
			break;
		case CLRSTK:
			clearStck();
			break;
		case SINFX:
			op1 = pop2();
			push2(sin((PI / 180.0f) * op1)); /* Convert degree into radians */
			break;
		case EXPFX:
			op1 = pop2();
			push2(exp(op1));
			break;
		case POWFX:
			op2 = pop2();
			op1 = pop2();
			push2(pow(op1, op2));
			break;
		case '\n':
			printf("\t%.8g, %c\n", (sp >= 1 && sp <= MAXVAL) ? pop2() : 0.0f \
														, (spVar >= 1 && spVar <= MAXVAL) ? pop3() : 'X');
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return;
}

/* printDecimal - print n in decimal */
void printDecimal(int n)
{
	if (n < 0)
	{
		putchar('-');
		n = -n;
	}
	if (Abs(n / 10))
		printDecimal(Abs(n / 10));
	putchar(Abs(n % 10) + '0');
	return;
}

/* Using Recursion(Postfix) to avoid reversing the string of integer number */
void Itoa2(int n, char s[])
{
	static int i;

	if (n < 0)
	{
		s[i++] = '-';
		n = -n;
	}
	if (Abs(n / 10))
		Itoa2(Abs(n / 10), s);
	s[i++] = Abs(n % 10) + '0';
	return;
}

#define swap(t, x, y)	{\
												t tmp;\
												tmp = x, x = y, y = tmp;\
											}

#define paste(front, back)	(front ## back)


void testSwapMacro(void)
{
	int a = 22, b = 44;
	swap(int, a, b);
	printf("a=%i, b = %i, p = %i\n", a, b, paste(123,431));
	return;
}

#define SWAPV(i, j)	{\
											int temp;\
											temp = v[i];\
											v[i] = v[j];\
											v[j] = temp;\
										}
/*
	Each partition is only looking for the Pivot and 
	sub-partitioning by left of pivot and right of pivot as
	lesser than and greater than respectively wrt pivot. There
	is no real interchange happening as is typical in sorting
	algorithms. But because of recursion we are seeing the same
	result by pivoting instead of sorting.
*/
void QuickSort(int v[], int left, int right)
{
	int i, pivot;

	if (left >= right)
		return;
	SWAPV(left, (left + right) / 2); /* Take an arbitrary index to pivot on. */
	pivot = left; /* Scan left to right moving items < on left of pivot */
	for (i = left + 1; i <= right; ++i) /* and > on right of pivot. */
	{
		if (v[i] < v[left]) /* move the pivot to the correct position in v. */
		{
			pivot+=1; /* create space for v[i] left of pivot. */
			SWAPV(pivot, i); /* store the lesser v[i] in pivot. */
		}
	}
	SWAPV(left, pivot); /* move the last less v[i] from pivot to extreme left */
	QuickSort(v, left, pivot-1); /* still lesser while not sorted. */
	QuickSort(v, pivot + 1, right);
	return;
}