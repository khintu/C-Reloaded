#include <stdio.h>
#include <math.h>
#include <limits.h>
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
	static unsigned long long Memo[MAXDP_DEPTH] = { 0, 1 };

	if (n > 2)
		if (Memo[n-1] == 0)
			Memo[n-1] = FibonacciDP(n - 1) + FibonacciDP(n - 2);
	return Memo[n-1];
}

double FibonacciDPf(unsigned n)
{
	static double Memo[MAXDP_DEPTH] = { 0.0, 1.0 };

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
	static unsigned long long Memo[MAXDP_DEPTH] = { 1, 1 };
	if (n > 1)
		if (Memo[n] == 0)
			Memo[n] = climbingStaircaseStepsTDn(n - 1) + climbingStaircaseStepsTDn(n - 2);
	return Memo[n];
}

/* Bottom-up Tabulation using iteration */
unsigned long long climbingStaircaseStepsBUp(unsigned n)
{
	unsigned long long Table[MAXDP_DEPTH] = { 1, 1 };
	unsigned i;
	for (i = 2 ; i <= n ; ++i)
			Table[i] = Table[i - 1] + Table[i - 2];
	return Table[n];
}

/* This is simple recursion not DP, T(n) = O(2^n) */
unsigned long long towersOfHanoiTDn(unsigned n)
{
	if (n == 1)
		return 1;
	else
		return 2 * towersOfHanoiTDn(n - 1) + 1;
}

unsigned long long towersOfHanoiBUp(unsigned n)
{
	unsigned long long Table[MAXDP_DEPTH] = { 0, 1 };
	unsigned i;
	for (i = 2; i <= n; ++i)
		Table[i] = 2 * Table[i - 1] + 1;
	return Table[n];
}

/* Climbing Stairs all unordered ways, Top-Down */
unsigned long long climbingStaircaseSteps2TDn(unsigned n)
{
	static unsigned long long Memo[MAXDP_DEPTH] = { 1, 1 };
	if (n > 1)
		if (Memo[n] == 0)
			Memo[n] = 1 + climbingStaircaseSteps2TDn(n - 2);
	return Memo[n];
}

/* Climbing Stairs all unordered ways, Bottom-Up */
unsigned long long climbingStaircaseSteps2BUp(unsigned n)
{
	unsigned long long Table[MAXDP_DEPTH] = { 1, 1 };
	unsigned i;
	for (i = 2; i <= n; ++i)
		Table[i] = 1 + Table[i - 2];
	return Table[n];
}

static inline unsigned min_dp(unsigned x, unsigned y)
{
	if (x < y)
		return x;
	else
		return y;
}

static int jmp_dp(int arr[], int startIdx)
{
	int i;
	for (i = startIdx; i >= 0 ; --i)
		if (i != startIdx && arr[i] == arr[startIdx])
			return i;
	return -1;
}

/* Minimum Steps to reach a target idx, Top-Down */
unsigned minSteps2TargetTDn(int arr[], const int N, int start, int end, int n)
{
	int t, tstart = start, tend = end;
	static unsigned stepsTbl[MAXDP_DEPTH] = { 0 };
	
	if (start > end || n < start || n > end)
		return INT_MAX;
	else if (n > 0)
		stepsTbl[n] = 1 + min_dp(min_dp(minSteps2TargetTDn(arr, N, start, n - 1, n - 1), \
																		minSteps2TargetTDn(arr, N, n + 1, end, n + 1)), \
														 minSteps2TargetTDn(arr, N, tstart, tend,\
						((t = jmp_dp(arr, n)) >= 0) ? (tstart = 0, (tend = (t > 0)?n-1:N - 1), t) : (t)  ));
	return stepsTbl[n];
}

void DynamicProgramming(int argc, char* argv[])
{
	unsigned i;
	int arr[] = { 60, -23, -24, 300, 60, 22, 23, 24, 3, 300 }; /* Cycle */
	
#if 0
	int arr[] = { 60, -23, -24, 300, 60, 22, 300, 3, 45, 300 };
	int arr[] = { 60, -23, -24, 300, 60, 300, 22, 3, 45, 300 }; /* No Cycle */
	int arr[] = { 60, -23, -24, 30, 60, 22, 23, 24, 3, 300 }; /* No Cycle */
	int arr[] = { -23, -24, 60, 30, 70, 22, 23, -24, 3, 300 };	
	char str[] = "abcefg";
	//char str[] = "ab";
	reverseStringDP(str, sizeof(str));
	printf("%s\n", str);
	printf("Fibonacci Series/Golden Ratio (phi)= \n");
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		printf((i% MAXDP_DEPTH_LOOP)?"%llu, ":"%llu\n", FibonacciDP(i));
		//printf((i % MAXDP_DEPTH_LOOP)) ? "[%u]%f, " : "[%u]%f\n", i, FibonacciDPf(i));
		//printf((i % MAXDP_DEPTH_LOOP) ? "%f, " : "%f\n", FibonacciDPf(i + 1) / FibonacciDPf(i));
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		//printf((i % MAXDP_DEPTH_LOOP) ? "[%u]%g, " : "[%u]%g\n", i, FibonacciDPphi(i-1));
		printf((i % MAXDP_DEPTH_LOOP) ? "%llu, " : "%llu\n", (unsigned long long)ceil(FibonacciDPphi(i - 1)));
	//printf("size of long = %zu\n", sizeof(unsigned long long));
	printf("Climbing Staircase Steps all distinct ways= \n");
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		printf((i % MAXDP_DEPTH_LOOP) ? "%llu, " : "%llu\n", climbingStaircaseStepsTDn(i));
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		printf((i % MAXDP_DEPTH_LOOP) ? "%llu, " : "%llu\n", climbingStaircaseStepsBUp(i));
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		printf((i % MAXDP_DEPTH_LOOP) ? "%f, " : "%f\n", \
						((float)(climbingStaircaseStepsTDn(i + 1))) / ((float)climbingStaircaseStepsTDn(i)));
	printf("Towers of Hanoi Steps= \n");
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		printf((i % MAXDP_DEPTH_LOOP) ? "%llu, " : "%llu\n", towersOfHanoiTDn(i));
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		printf((i % MAXDP_DEPTH_LOOP) ? "%llu, " : "%llu\n", towersOfHanoiBUp(i));
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		printf((i % MAXDP_DEPTH_LOOP) ? "%f, " : "%f\n", \
			((float)(towersOfHanoiTDn(i + 1))) / ((float)towersOfHanoiTDn(i)));
	printf("Climbing Stairs all unordered ways= \n");
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		printf((i % MAXDP_DEPTH_LOOP) ? "%llu, " : "%llu\n", climbingStaircaseSteps2TDn(i));
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		printf((i % MAXDP_DEPTH_LOOP) ? "%llu, " : "%llu\n", climbingStaircaseSteps2BUp(i));
	for (i = 1; i <= MAXDP_DEPTH_LOOP; ++i)
		printf((i % MAXDP_DEPTH_LOOP) ? "%f, " : "%f\n", \
			((float)(climbingStaircaseSteps2BUp(i + 1))) / ((float)climbingStaircaseSteps2BUp(i)));
#endif
	for (i = 0; i < 10; ++i)
		printf("Steps for idx[%d] = %d\n", i, minSteps2TargetTDn(arr, 10, 0, i, i));
	return;
}