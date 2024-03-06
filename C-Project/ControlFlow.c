#include <stdio.h>
#include <ctype.h>
#if defined __WINDOWS__
#include <math.h>
#elif defined __LINUX__
#include <stdlib.h>
#endif
#include <string.h>
#include <c-project.h>

int binsearch(int x, int v[], int n)
{
	int low, mid, high;

	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}
/* 
	Copy mid less than or equal to x into high.
	Then move either high to low or low to high
	with each binary partition of sorted array
	at the end of which the matched result is
	stored in low. On exit from loop decode the
	result from low by single if case.
*/
int binsearchfast(int x, int v[], int n)
{
	int low, mid, high;

	low = 0;
	high = n - 1;
	while (low < high)
	{
		mid = (low + high) / 2;
		if (x > v[mid])
			low = mid + 1;
		else
			high = mid;
	}
	if (x == v[low])
		return low;
	return -1;
}

void testBinSearch(void)
{
	int i;
	int sorted[50] = { 100,110,120,130,200,210,220,230,240,300,
						310,312,313,314,315,316,326,333,343,353,
						357,365,367,377,380,386,390,400,410,415,
						420,422,426,430,435,440,444,445,450,455,
						460,461,462,463,464,465,470,472,474,479
	};
	for (i = 0; i < 10000000; ++i)
	{
		binsearchfast(sorted[i % 50], sorted, 50);
	}
	printf("Found %s\n", binsearchfast(100, sorted, 50) >= 0 ? "Yes" : "No");
	return;
}

void countDigitWhiteSpOther2(void)
{
	int c, i, nwhites, nothers, ndigits[10];

	nwhites = nothers = 0;
	for (i = 0; i < 10; ++i)
		ndigits[i] = 0;
	while ((c = getchar()) != EOF)
	{
		switch (c)
		{
		case ' ':
		case '\n':
		case '\t':
			nwhites++;
			break;
		case '0': case '1': case '2': case '3':case '4':
		case '5': case '6': case '7': case '8': case '9':
			ndigits[c - '0']++;
			break;
		default:
			nothers++;
			break;
		}
	}
	printf("digits =");
	for (i = 0; i < 10; ++i)
		printf(" %d", ndigits[i]);
	printf(", white spaces = %d, others = %d\n", nwhites, nothers);
	return;
}

// Copy t to s and replace escape chars to visible \n,etc.
void escape(char s[], char t[])
{
	int i, j;

	for (i = 0, j = 0; t[i] != '\0'; ++i, ++j)
	{
		switch (t[i])
		{
		case '\n':
			s[j] = '\\';
			s[++j] = 'n';
			break;
		case '\t':
			s[j] = '\\';
			s[++j] = 't';
			break;
		default:
			s[j] = t[i];
			break;
		}
	}
	s[j] = '\0';
	return;
}

// Copy t to s and replace visible \n,etc. to real escape chars 
void escapeRev(char s[], char t[])
{
	int i, j;

	for (i = 0, j = 0; t[i] != '\0'; ++i, ++j)
	{
		switch (t[i])
		{
		case '\\':
			switch(t[i + 1]){
			case 'n':
				s[j] = '\n';
				++i;
				break;
			case 't':
				s[j] = '\t';
				++i;
				break;
			default:
				s[j] = t[i];
				break;
			}
			break;
		default:
			s[j] = t[i];
			break;
		}
	}
	s[j] = '\0';
	return;
}

void testEscapeRev(void)
{
	char s[MAXLINE], t[MAXLINE];
	getLine(s, MAXLINE);
	escapeRev(t, s);
	printf("%s\n", t);
	return;
}

int atoi2(char s[])
{
	int i, n, sign;

	for (i = 0; isspace(s[i]); ++i)
		;
	
	sign = s[i] == '-' ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		++i;

	for (n = 0; isdigit(s[i]); ++i)
		n = 10 * n + (s[i] - '0');
	return n*sign;
}

/* 
* This is simple InsertionSort with a outer gap loop. The
* gap starts as a half of n value, then keeps reducing with
* each iteration by a factor of 2. O(n^1.25), better than
* InsertionSort which is O(n^2).
*/
void ShellSort(int v[], int n)
{
	int gap, i, j, tmp;
	
	for (gap = n / 2; gap > 0; gap /= 2)
		for (i = gap; i < n; ++i)
			for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
				tmp = v[j], v[j] = v[j + gap], v[j + gap] = tmp; /* Swap for each position of scan, same as shifting for one element at a time */
	return;
}

/* The process or step of comparison and then swapping gets 
	the elements ordered. With each outer iteration the inner
	iteration slowly brings all the elements into their correct
	positions. O(n^2) */
void BubbleSort(int v[], int n)
{
	int i, tmp, isSwp;

	do
	{
		isSwp = FALSE;
		for (i = 0; i < n - 1; ++i) /* inner loop */
			if (v[i] > v[i + 1])
				tmp = v[i], v[i] = v[i + 1], v[i + 1] = tmp, isSwp = TRUE;
	} while (isSwp == TRUE); /* Outer loop */
	return;
}

/*
Work from Right to Left, pick up key and keep scanning
for elements those are greater than key and shift them into
the current position of key, so on and so forth as you scan.
Then insert key into the blank position of previous greater
element, once the test condition fails.
*/
void InsertionSort(int v[], int n)
{
	int key, i, j;

	for (i = 1; i < n; ++i)
	{
		key = v[i];
		/* Modify 2nd condition from v[j] > key
			 to v[j] < key for descending output */
		for (j = i - 1; j >= 0 && v[j] > key; --j)
			v[j + 1] = v[j];
		v[j + 1] = key; /* blank elements index */
	}
	return;
}

void testShellSort(void)
{
	int i;
	int v[11] = { 400,10,3,70,0,44,390,210,100,33,21 };
	ShellSort(v, 11);
	//InsertionSort(v, 11);
	//BubbleSort(v, 11);
	//QuickSort(v, 0, 10);
	for (i = 0; i < 11; ++i)
		printf("%d%c", v[i], i < 10 ? ',' : '\n');
	return;
}

#define ALPHAL	"a-z"
#define ALPHAU	"A-Z"
#define DIGIT	"0-9"
void expand(char s[], char t[], int tn)
{
	int i, j, k, sl, si;

	sl = stringLength(s);
	j = 0; i = 0;
	while (i < sl && j < tn-1)
	{
		if ((si = subStringIdx(&s[i], ALPHAL)) > -1 && si == 0)
		{			
			for (k = 0; j < tn - 1 && k < 26; k++)
			{
				t[j++] = 'a' + k;
			}
			i += 3;
			continue;
		}
		if ((si = subStringIdx(&s[i], ALPHAU)) > -1 && si == 0)
		{
			for (k = 0; j < tn - 1 && k < 26; k++)
			{
				t[j++] = 'A' + k;
			}
			i += 3;
			continue;
		}
		if ((si = subStringIdx(&s[i], DIGIT)) > -1 && si == 0)
		{
			for (k = 0; j < tn - 1 && k < 10; k++)
			{
				t[j++] = '0' + k;
			}
			i += 3;
			continue;
		}
		if (j < tn - 1)
			t[j++] = s[i++];
	}
	t[j] = '\0';
	return;
}

/* Bug - the largest negative integer in 32 bit signed int
	is bigger than the largest positive integer which is 2^31-1.
	Thus on using the number -2^31 it overflows as a positive 
	number which is a range from 0 to 2^31-1. The fix is to 
	treat the mod & div operator as absolute values those that
	would fit into the positive valid range of integer.
*/
void Itoa(int n, char s[])
{
	int i, sign;
	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = Abs(n % 10) + '0'; // Read LSB using mod
	} while (Abs(n /= 10) > 0);  // Remove LSB using div or shift right
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	return;
}

void itob(int n, char s[], int b)
{
	int i, sign, mod;
	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		mod = Abs(n % b);
		if (b >= 10 && b <= 16)
		{
			switch (mod) {
			case 10:
				s[i++] = 'A';
				break;
			case 11:
				s[i++] = 'B';
				break;
			case 12:
				s[i++] = 'C';
				break;
			case 13:
				s[i++] = 'D';
				break;
			case 14:
				s[i++] = 'E';
				break;
			case 15:
				s[i++] = 'F';
				break;
			default:
				s[i++] = mod + '0';
				break;
			}
		}
		else
		{
			s[i++] = mod + '0';
		}
	} while (Abs(n /= b) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	return;
}

void itoaW(int n, char s[], int w)
{
	int i, sign;
	char W[MAXLINE] = "";

	if ((sign = (n < 0)) == 1)
		n = -n;

	if ((sign && w >= 2) || (w >= 1 && !sign))
	{
		i = 0;
		do {
			s[i++] = Abs(n % 10) + '0';
		} while (Abs(n /= 10) > 0);
		if (sign)
			s[i++] = '-';
		s[i] = '\0';
		reverse(s);
			
		w -= stringLength(s);
		if (w >= 0) {
			for (i = 0; i < w; ++i)
				W[i] = ' ';
			W[i] = '\0';
			Strcat(W + i, s);
		}
		else
		{
			w = Abs(w);
			i = 0;
			if (sign) // preserve sign bit
			{
				w++;
				W[0] = '-';
				W[1] = '\0';
				i = 1;
			}
			copyString(W + i, s + w);
		}
		copyString(s, W);
	}
	return;
}

int trim(char s[])
{
	int n;

	for (n = (int)strlen(s) - 1; n >= 0; n--)
		if (!isspace(s[n]))
			break;
	s[n + 1] = '\0';
	return n;
}