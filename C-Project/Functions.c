#include <stdio.h>
#include <ctype.h>
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

#define MAXVAL	100	/* max depth of value stack */
#define MAXOP		100	/* max size of operand or operator */
#define NUMBER	'0'	/* Signal that a number was found */
#define PRNTTOP	'P' /* Command for printing top of stack */
#define DUPLTOP	'D' /* Command for duplicating top of stack */
#define SWPTOP2	'W' /* Command for duplicating top of stack */
#define CLRSTK	'C' /* Command for duplicating top of stack */
#define BUFSIZE	100

int sp = 0;					/* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;				/* next free position in buf */
int signFlag = FALSE; /* Sign field in getoperator */

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

void reversePolishCalc(void)
{
	int type;
	double op1, op2;
	char s[MAXOP];

	while ((type = getoperator(s)) != EOF)
	{
		switch (type)
		{
		case NUMBER:
			push2(Atof(s));
			break;
		case '+':
			push2(pop2() + pop2());
			break;
		case '*':
			push2(pop2() * pop2());
			break;
		case '-':
			if (signFlag != TRUE)
			{
				op2 = pop2();
				op1 = pop2();
				push2(op1 - op2);
			}
			break;
		case '/':
			op2 = pop2();
			op1 = pop2();
			if (op2 != 0.0)
				push2(op1 / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop2();
			op1 = pop2();
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
		case '\n':
			printf("\t%.8g\n", pop2());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return;
}