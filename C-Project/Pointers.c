#include <stdio.h>
#include <ctype.h>
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