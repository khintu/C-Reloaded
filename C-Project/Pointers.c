#include <stdio.h>
#include <ctype.h>
#include <math.h>
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
	int c, ac, sign, pwr;

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
	if (c == '.')
	{
		for (pwr = 0, c = getch(); isdigit(c); c = getch(), ++pwr)
			*pn = *pn * 10 + c - '0';
		*pn /= pow(10, pwr);
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
		printf("%g%c", array[n], (n % SIZE == SIZE - 1) ? '\n' : ',');
	return;
}