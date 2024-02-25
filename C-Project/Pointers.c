#include <stdio.h>
#include <ctype.h>
#include <c-project.h>

#define SIZE	5

int getInt(int *pn)
{
	int c, sign;

	while ((isspace(c = getch())))
		;
	if (!isdigit(c) && c != '.' && c != '+' && c != '-')
	{
		ungetch(c);		/* it's not a number */
		return 0;
	}
	sign = c == '-' ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = *pn * 10 + c - '0';
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return 0;
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