#include <stdio.h>
#include <c-project.h>

int power(int base, int exp)
{
	int i, p = 1;
	for (i = 1; i <= exp; ++i)
		p = p * base;
	return p;
}

long powerl(int base, int exp)
{
	int i;
	long p = 1;
	for (i = 1; i <= exp; ++i)
		p = p * base;
	return p;
}

unsigned long powerul(int base, int exp)
{
	int i;
	unsigned long p = 1;
	for (i = 1; i <= exp; ++i)
		p = p * base;
	return p;
}

long long powerll(int base, int exp)
{
	int i;
	long long p = 1;
	for (i = 1; i <= exp; ++i)
		p = p * base;
	return p;
}

unsigned long long powerull(int base, int exp)
{
	int i;
	unsigned long long p = 1;
	for (i = 1; i <= exp; ++i)
		p = p * base;
	return p;
}

double powerf(double base, int exp)
{
	double p;
	int sign;

	sign = (exp >= 0) ? 1 : -1;
	exp = Abs(exp);
	for (p = 1.0; exp > 0; --exp)		
		p = (sign >= 0) ? p * base : p / base;
	return p;
}

int powerEfficient(int base, int exp)
{
	int p;
	for (p = 1 ; exp > 0; --exp)
		p = p * base;
	return p;
}
