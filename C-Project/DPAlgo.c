#include <stdio.h>
#include <math.h>
#include <c-project.h>

static void reverseDP(char str[], int i, int j)
{
	if (i >= j)
		return;
	else {
		str[i] = str[i] ^ str[j];
		str[j] = str[i] ^ str[j];
		str[i] = str[i] ^ str[j];
		reverseDP(str, i + 1, j - 1);
	}
	return;
}

void reverseStringDP(char str[], int len)
{
	//int len = StrLen(str);
	reverseDP(str, 0, len - 2);
	return;
}

unsigned long long FibonacciDP(unsigned n)
{
	static unsigned long long Memo[100] = { 0, 1 };

	if (n > 2)
		if (Memo[n-1] == 0)
			Memo[n-1] = FibonacciDP(n - 1) + FibonacciDP(n - 2);
	return Memo[n-1];
}

double FibonacciDPf(unsigned n)
{
	static double Memo[100] = { 0.0, 1.0 };

	if (n > 2)
		if (Memo[n - 1] == 0)
			Memo[n - 1] = FibonacciDPf(n - 1) + FibonacciDPf(n - 2);	
	return Memo[n - 1];
}

double FibonacciDPphi(unsigned n)
{
	return (powerf(1.618033988749895f, n) - powerf(.618033988749895f, n))/ 2.236067f;
}

/* Top-Down Memoization using recursion */
unsigned long long climbingStaircaseStepsTDn(unsigned n)
{
	static unsigned long long Memo[100] = { 1, 1 };
	if (n > 1)
		if (Memo[n] == 0)
			Memo[n] = climbingStaircaseStepsTDn(n - 1) + climbingStaircaseStepsTDn(n - 2);
	return Memo[n];
}

/* Bottom-up Tabulation using iteration */
unsigned long long climbingStaircaseStepsBUp(unsigned n)
{
	unsigned long long Table[100] = { 1, 1 };
	unsigned i;
	for (i = 2 ; i <= n ; ++i)
			Table[i] = Table[i - 1] + Table[i - 2];
	return Table[n];
}

unsigned long long towersOfHanoiTDn(unsigned n)
{
	if (n == 1)
		return 1;
	else
		return 2 * towersOfHanoiTDn(n - 1) + 1;
}

unsigned long long towersOfHanoiBUp(unsigned n)
{
	unsigned long long Table[100] = { 0, 1 };
	unsigned i;
	for (i = 2; i <= n; ++i)
		Table[i] = 2 * Table[i - 1] + 1;
	return Table[n];
}

/* Climbing Stairs all unordered ways, Top-Down */
unsigned long long climbingStaircaseSteps2TDn(unsigned n)
{
	static unsigned long long Memo[100] = { 1, 1 };
	if (n > 1)
		if (Memo[n] == 0)
			Memo[n] = 1 + climbingStaircaseSteps2TDn(n - 2);
	return Memo[n];
}

/* Climbing Stairs all unordered ways, Bottom-Up */
unsigned long long climbingStaircaseSteps2BUp(unsigned n)
{
	unsigned long long Table[100] = { 1, 1 };
	unsigned i;
	for (i = 2; i <= n; ++i)
		Table[i] = 1 + Table[i - 2];
	return Table[n];
}

void DynamicProgramming(int argc, char* argv[])
{
	unsigned i;
#if 0
	char str[] = "abcefg";
	//char str[] = "ab";
	reverseStringDP(str, sizeof(str));
	printf("%s\n", str);
	printf("Fibonacci Series/Golden Ratio (phi)= \n");
	for (i = 1; i <= 50; ++i)
		printf((i%50)?"%llu, ":"%llu\n", FibonacciDP(i));
		//printf((i % 50) ? "[%u]%f, " : "[%u]%f\n", i, FibonacciDPf(i));
		//printf((i % 50) ? "%f, " : "%f\n", FibonacciDPf(i + 1) / FibonacciDPf(i));
	for (i = 1; i <= 50; ++i)
		//printf((i % 50) ? "[%u]%g, " : "[%u]%g\n", i, FibonacciDPphi(i-1));
		printf((i % 50) ? "%llu, " : "%llu\n", (unsigned long long)ceil(FibonacciDPphi(i - 1)));
	//printf("size of long = %zu\n", sizeof(unsigned long long));
	printf("Climbing Staircase Steps all distinct ways= \n");
	for (i = 1; i <= 50; ++i)
		printf((i % 50) ? "%llu, " : "%llu\n", climbingStaircaseStepsTDn(i));
	for (i = 1; i <= 50; ++i)
		printf((i % 50) ? "%llu, " : "%llu\n", climbingStaircaseStepsBUp(i));
	for (i = 1; i <= 50; ++i)
		printf((i % 50) ? "%f, " : "%f\n", \
						((float)(climbingStaircaseStepsTDn(i + 1))) / ((float)climbingStaircaseStepsTDn(i)));
	printf("Towers of Hanoi Steps= \n");
	for (i = 1; i <= 50; ++i)
		printf((i % 50) ? "%llu, " : "%llu\n", towersOfHanoiTDn(i));
	for (i = 1; i <= 50; ++i)
		printf((i % 50) ? "%llu, " : "%llu\n", towersOfHanoiBUp(i));
	for (i = 1; i <= 50; ++i)
		printf((i % 50) ? "%f, " : "%f\n", \
			((float)(towersOfHanoiTDn(i + 1))) / ((float)towersOfHanoiTDn(i)));
#endif
	printf("Climbing Stairs all unordered ways= \n");
	for (i = 1; i <= 50; ++i)
		printf((i % 50) ? "%llu, " : "%llu\n", climbingStaircaseSteps2TDn(i));
	for (i = 1; i <= 50; ++i)
		printf((i % 50) ? "%llu, " : "%llu\n", climbingStaircaseSteps2BUp(i));
	for (i = 1; i <= 50; ++i)
		printf((i % 50) ? "%f, " : "%f\n", \
			((float)(climbingStaircaseSteps2BUp(i + 1))) / ((float)climbingStaircaseSteps2BUp(i)));
	return;
}