#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <c-project.h>


void determineRanges(void)
{
#if defined __WINDOWS__
	printf("Various sizes in bytes:\n "
		"char %zu, uchar %zu, short %zu, ushort %zu, int %zu, uint %zu, "
		"long %zu, ulong %zu, llong %zu, ullong %zu\n"
		", float %zu, double %zu, long double %zu\n", sizeof(char), sizeof(unsigned char), sizeof(short), \
		sizeof(unsigned short), sizeof(int), sizeof(unsigned int), sizeof(long), \
		sizeof(unsigned long), sizeof(long long), sizeof(unsigned long long), \
		sizeof(float), sizeof(double), sizeof(long double));

	printf("Various type ranges:\n");
	printf("signed char, computd %d and %d, header %d and %d\n", \
		- (power(2, CHAR_BIT - 1)), power(2, CHAR_BIT - 1) - 1, SCHAR_MIN, SCHAR_MAX);
	printf("unsigned char, computd %d and %d, header %d and %d\n", \
		0, power(2, CHAR_BIT) - 1, 0, UCHAR_MAX);

	printf("signed short, computd %d and %d, header %d and %d\n", \
		- (power(2, SHRT_BIT - 1)), power(2, SHRT_BIT - 1) - 1, SHRT_MIN, SHRT_MAX);
	printf("unsigned short, computd %d and %d, header %d and %d\n", \
		0, power(2, SHRT_BIT) - 1, 0, USHRT_MAX);

	printf("signed int, computd %d and %d, header %d and %d\n", \
		- (power(2, INT_BIT - 1)), power(2, INT_BIT - 1) - 1, INT_MIN, INT_MAX);
	printf("unsigned int, computd %u and %u, header %u and %u\n", \
		0, power(2, INT_BIT) - 1, 0, UINT_MAX);

	printf("signed long, computd %ld and %ld, header %ld and %ld\n", \
		- (powerl(2, LONG_BIT - 1)), powerl(2, LONG_BIT - 1) - 1, LONG_MIN, LONG_MAX);
	printf("unsigned long, computd %lu and %lu, header %lu and %lu\n", \
		0UL, powerul(2, LONG_BIT) - 1, 0UL, ULONG_MAX);
		
	printf("signed long long, computd %lld and %lld, header %lld and %lld\n", \
			powerll(2, LLONG_BIT - 1), powerll(2, LLONG_BIT - 1) - 1, LLONG_MIN, LLONG_MAX);
	printf("unsigned long long, computd %llu and %llu, header %llu and %llu\n", \
		0ULL, powerull(2, LLONG_BIT) - 1, 0ULL, ULLONG_MAX);

	/*printf("float, computd %f and %f, header %.100f and %f\n", \
		0.0, 0.0, FLT_MIN, FLT_MAX);
	printf("double, computd %f and %f, header %.500f and %f\n", \
		0.0, 0.0, DBL_MIN, DBL_MAX);*/
	printf("float, computd %e and %e, header %e and %e\n", \
		0.0, 0.0, FLT_MIN, FLT_MAX);
	printf("double, computd %e and %e, header %e and %e\n", \
		0.0, 0.0, DBL_MIN, DBL_MAX);
#elif defined __LINUX__
	printf("Various sizes in bytes:\n "
		"char %zu, uchar %zu, short %zu, ushort %zu, int %zu, uint %zu, "
		"long %zu, ulong %zu, llong %zu, ullong %zu\n"
		", float %zu, double %zu, long double %zu\n", sizeof(char), sizeof(unsigned char), sizeof(short), \
		sizeof(unsigned short), sizeof(int), sizeof(unsigned int), sizeof(long), \
		sizeof(unsigned long), sizeof(long long), sizeof(unsigned long long), \
		sizeof(float), sizeof(double), sizeof(long double));
	printf("Various type ranges:\n");
	printf("signed char, computd %d and %d, header %d and %d\n", \
		- (power(2, CHAR_BIT - 1)), power(2, CHAR_BIT - 1) - 1, SCHAR_MIN, SCHAR_MAX);
	printf("unsigned char, computd %d and %d, header %d and %d\n", \
		0, power(2, CHAR_BIT) - 1, 0, UCHAR_MAX);

	printf("signed short, computd %d and %d, header %d and %d\n", \
		- (power(2, SHRT_BIT - 1)), power(2, SHRT_BIT - 1) - 1, SHRT_MIN, SHRT_MAX);
	printf("unsigned short, computd %d and %d, header %d and %d\n", \
		0, power(2, SHRT_BIT) - 1, 0, USHRT_MAX);

	printf("signed int, computd %d and %d, header %d and %d\n", \
		- (power(2, INT_BIT - 1)), power(2, INT_BIT - 1) - 1, INT_MIN, INT_MAX);
	printf("unsigned int, computd %u and %u, header %u and %u\n", \
		0, power(2, INT_BIT) - 1, 0, UINT_MAX);

	printf("signed long, computd %ld and %ld, header %ld and %ld\n", \
		- (powerl(2, LONG_BIT - 1)), powerl(2, LONG_BIT - 1) - 1, LONG_MIN, LONG_MAX);
	printf("unsigned long, computd %lu and %lu, header %lu and %lu\n", \
		0UL, powerul(2, LONG_BIT) - 1, 0UL, ULONG_MAX);
		
	printf("signed long long, computd %lld and %lld, header %lld and %lld\n", \
			powerll(2, LLONG_BIT - 1), powerll(2, LLONG_BIT - 1) - 1, LLONG_MIN, LLONG_MAX);
	printf("unsigned long long, computd %llu and %llu, header %llu and %llu\n", \
		0ULL, powerull(2, LLONG_BIT) - 1, 0ULL, ULLONG_MAX);

#if 0
	/*printf("float, computd %f and %f, header %.100f and %f\n", \
		0.0, 0.0, FLT_MIN, FLT_MAX);
	printf("double, computd %f and %f, header %.500f and %f\n", \
		0.0, 0.0, DBL_MIN, DBL_MAX);*/
	printf("float, computd %e and %e, header %e and %e\n", \
		0.0, 0.0, FLT_MIN, FLT_MAX);
	printf("double, computd %e and %e, header %e and %e\n", \
		0.0, 0.0, DBL_MIN, DBL_MAX);
#endif
#endif
	return; 
}

int atoiNaive(char s[])
{
	int i, n;

	n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = n * 10 + (s[i] - '0');
	return n;
}

int lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	else
		return c;
}

unsigned long int next = 1;

/* rand: Return pseudo-random integer on 0..32767 */
int rand(void)
{
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % 32768;
}

/* srand: set seed for rand() */
void srand(unsigned int seed)
{
	next = seed;
}

/* htoi: convert hex string to decimal */
int htoi(char s[])
{
	int n, i, l;
	if ((l = stringLength(s)) < 2)
		return -1;

	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		i = 2;
	else
		i = 0;
	for (n = 0; (s[i] >= '0' && s[i] <= '9') || \
		(s[i] >= 'A' && s[i] <= 'F') || \
		(s[i] >= 'a' && s[i] <= 'f'); ++i)
	{
		n = n * 16;
		if (s[i] >= '0' && s[i] <= '9')
			n = n + s[i] - '0';
		else if (s[i] >= 'A' && s[i] <= 'F')
			n = n + s[i] - 'A' + 10;
		else if (s[i] >= 'a' && s[i] <= 'f')
			n = n + s[i] - 'a' + 10;
	}
	return n;
}

/* delete all c from s */
void squeeze(char s[], int c)
{
	int i, j;
	for (i = j = 0; s[i] != '\0'; ++i)
		if (s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
	return;
}

/* delete any c in s from t */
void squeeze2(char t[], char s[])
{
	int i, j, k, skip;
	
	for (i = 0, k = 0; t[i] != '\0'; ++i)
	{
		skip = FALSE;
		for (j = 0; s[j] != '\0'; ++j)
			if (t[i] == s[j])
			{
				skip = TRUE;
				break;
			}
		if (!skip)
			t[k++] = t[i];
	}
	t[k] = '\0';
	return;
}

int any(char s1[], char s2[])
{
	int i, j;
	for (i = 0; s1[i] != '\0'; ++i)
	{
		for (j = 0; s2[j] != '\0'; ++j)
			if (s1[i] == s2[j])
				return i;
	}
	return -1;
}

unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p - n)) & ~(~0U << n);
}

unsigned setbits(unsigned x, int p, int n, const unsigned y)
{
	unsigned z1, z2;
	int i;

	// fetch n rightmost bits of y
	z1 = y & ~(~0U << n);
	// move this mask to the correct pth bit position
	z1 <<= (p - n);

	// remove nth bits starting at p from x;
	z2 = (~0U << n);
	for (i = 0; i < p - n; ++i)
	{
		z2 <<=  1;
		z2 |= 1U;
	}
	x &= z2;

	// set y bits on mask to x
	return (x | z1);
}

unsigned invert(unsigned x, int p, int n)
{
	unsigned z1;
	int i;
	for (i = 0; i < n; ++i)
	{
		z1 = 1U;
		z1 <<= (p - 1) - i;
		x ^= z1;
	}
	return x;
}

unsigned rightrot(unsigned x, int n)
{
	int i, z1, b;
	
	b = sizeof(unsigned) * CHAR_BIT;

	for (i = 0; i < n; ++i)
	{
		z1 = 1U;
		z1 &= x;
		x >>= 1;
		z1 <<= b - 1;
		x |= z1;
	}
	return x;
}

int bitcount(unsigned x)
{
	int b;
	for (b = 0; x != 0; x >>= 1)
		if (x & 1U)
			b++;
	return b;
}

// In 2's complement number system, negation by 1
// causes the first LSB that is 1 to be 0'd and 
// remaining bits those are 0s to be inverted to 1s.
// By AND'g with original the first LSB 1 is removed 
// and replaced with 0. The remaining 1s in LSB are
// turned off through AND operator.
int bitcountfaster(unsigned x)
{
	int b;
	for (b = 0; x != 0; x &= (x - 1), b++)
		;
	return b;
}

int lowerSuccinct(int c)
{
	return (c >= 'A' && c <= 'Z')
		? c + 'a' - 'A': c;
}

// Print a newline after every 10th character or after
// last character in array. Print a space else where.
void printCharArray(void)
{
	int i;
	char line[26] = "abcdefghijklmnopqrstuvwx";

	for (i = 0; i < 26; ++i)
		printf("%6c%c", line[i], (i == 25 || i % 10 == 9) ? '\n' : ' ');

	return;
}

void pluralStringCondn(void)
{
	int i;
	for (i = 1; i <= 10; ++i)
		printf("You have %d number of item%s\n", i, i == 1 ? "" : "s");
	return;
}
