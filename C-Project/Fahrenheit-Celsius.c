#include <stdio.h>
#include <c-project.h>

/* print Fahrenheit-Celsius table
	for fahr = 0, 20, ..., 300 */

void FahrenheitToCelsius(void)
{
	int fahr, celsius;
	int upper, lower, step;

	lower = 0;		/* lower limit of temperature table */
	upper = 300;	/* upper limit */
	step = 20;		/* step size */

	fahr = lower;
	while (fahr <= upper)
	{
		/* Emilia's BODMAS -- Keep the numerator greater than 9
		   for keeping result real and non fraction only -- */
		celsius = (5 * (fahr - 32)) / 9;
		printf(" %3d %6d\n", fahr, celsius);
		fahr = fahr + step;
	}
	return;
}

void FahrenheitToCelsiusReal(void)
{
	float fahr, celsius;
	int upper, lower, step;

	lower = 0;		/* lower limit of temperature table */
	upper = 300;	/* upper limit */
	step = 20;		/* step size */

	fahr = (float)lower;
	while (fahr <= upper)
	{
		celsius = (5.0f / 9.0f) * (fahr - 32.0f);
		printf(" %3.0f %6.2f\n", fahr, celsius);
		fahr = fahr + step;
	}
	return;
}

void CelsiusToFahrenheit(void)
{
	int fahr, celsius;
	int upper, lower, step;

	lower = 0;		/* lower limit of temperature table */
	upper = 300;	/* upper limit */
	step = 20;		/* step size */

	celsius = lower;
	while (celsius <= upper)
	{
		fahr = (9 / 5) * (celsius) + 32;
		printf(" %3d %6d\n", celsius, fahr);
		celsius = celsius + step;
	}
	return;
}

void CelsiusToFahrenheitReal(void)
{
	float fahr, celsius;
	int upper, lower, step;

	lower = 0;		/* lower limit of temperature table */
	upper = 300;	/* upper limit */
	step = 20;		/* step size */

	celsius = (float) lower;
	while (celsius <= upper)
	{
		fahr = (9.0f / 5.0f) * (celsius) + 32.0f;
		printf(" %3.0f %6.2f\n", celsius, fahr);
		celsius = celsius + step;
	}
	return;
}

void FahrenheitToCelsiusRealCompact(void)
{
	float fahr;

	for (fahr = 0.0f; fahr <= 300.0f; fahr = fahr + 20.0f)
		printf("%3.0f %6.2f\n", fahr, (5.0f / 9.0f) * (fahr - 32.0f));
	return;
}

void FahrenheitToCelsiusCompact(void)
{
	int fahr;

	for (fahr = 0; fahr <= 300; fahr = fahr + 20)
		printf("%3d %6.2f\n", fahr, (5.0f / 9.0f) * (fahr - 32));
	return;
}

void FahrenheitToCelsiusCompactReverse(void)
{
	int fahr;

	for (fahr = 300; fahr >= 0; fahr = fahr - 20)
		printf("%3d %6.2f\n", fahr, (5.0f / 9.0f) * (fahr - 32));
	return;
}

void ChkForLeapYear(int y)
{
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		printf("%d is a leap year\n", y);
	else
		printf("%d is NOT a leap year\n", y);
	return;
}

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int DayOfYear(int year, int month, int day)
{
	int i, leap;
	
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1; i < month; ++i)
		day += daytab[leap][i];
	return day;
}

void MonthOfDay(int year, int yearday, int* pmonth, int* pda)
{
	int i, leap;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1; yearday > daytab[leap][i]; ++i)
		yearday -= daytab[leap][i];
	if (pmonth)
		*pmonth = i;
	if (pda)
		*pda = yearday;
	return;
}

char* MonthName(int n)
{
	static char* name[] = {
		"Illegal month",
		"January", "February", "March",
		"April", "May", "June", "July",
		"August", "September", "October",
		"November", "December"
	};
	return n < 1 || n > 12 ? name[0] : name[n];
}

void testMonthOfDayAndYear(void)
{
	int month, day;
	printf("%d\n", DayOfYear(2124, 3, 22));

	MonthOfDay(2124, 365, &month, &day);
	printf("%s, %u\n", MonthName(month), day);
	printf("%d\n", DayOfYear(2024, month, day));
	return;
}