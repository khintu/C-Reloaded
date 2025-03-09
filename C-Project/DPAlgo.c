#include <stdio.h>
#include <math.h>
#include <c-project.h>

static void reverseDP(char str[], int i, int j)
{
	char tmp;
	if (i >= j)
		return;
	else {
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		reverseDP(str, i + 1, j - 1);
	}
	return;
}

void reverseStringDP(char str[])
{
	int len = StrLen(str);
	reverseDP(str, 0, len - 1);
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
	static double Memo[110] = { 0.0, 1.0 };

	if (n > 2)
		if (Memo[n - 1] == 0)
			Memo[n - 1] = FibonacciDPf(n - 1) + FibonacciDPf(n - 2);	
	return Memo[n - 1];
}

double FibonacciDPphi(unsigned n)
{
	return (powerf(1.618033988749895f, n) - powerf(.618033988749895f, n))/ 2.236067f;
}

unsigned long climbingStaircaseSteps(unsigned n)
{
	static unsigned long Memo[101] = { 0, 1, 2 };
	if (n > 2)
		if (Memo[n] == 0)
			Memo[n] = climbingStaircaseSteps(n - 1) + climbingStaircaseSteps(n - 2);
	return Memo[n];
}

void DynamicProgramming(int argc, char* argv[])
{
	unsigned i;
	char str[] = "abcefg";

#if 0
	reverseStringDP(str);
	printf("%s\n", str);
	printf("Fibonacci Series Golden Ratio (phi)= \n");
	for (i = 1; i <= 100; ++i)
		printf((i%100 != 0)?"%llu, ":"%llu\n", FibonacciDP(i));
		//printf((i % 100 != 0) ? "[%u]%f, " : "[%u]%f\n", i, FibonacciDPf(i));
		//printf((i % 100 != 0) ? "%f, " : "%f\n", FibonacciDPf(i + 1) / FibonacciDPf(i));
	for (i = 1; i <= 100; ++i)
		//printf((i % 100 != 0) ? "[%u]%g, " : "[%u]%g\n", i, FibonacciDPphi(i-1));
		printf((i % 100 != 0) ? "%llu, " : "%llu\n", (unsigned long long)ceil(FibonacciDPphi(i - 1)));
#endif
	printf("Climbing Staircase Steps all ways= \n");
	for (i = 1; i <= 100; ++i)
		printf((i%100)?"%lu, ":"%lu\n", climbingStaircaseSteps(i));
	return;
}