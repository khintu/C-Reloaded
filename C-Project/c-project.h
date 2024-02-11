#ifndef CPROJECT_H
#define CPROJECT_H

#define SHRT_BIT	(CHAR_BIT*sizeof(short))
#define INT_BIT		(CHAR_BIT*sizeof(int))
#define LONG_BIT	(CHAR_BIT*sizeof(long))
#define LLONG_BIT	(CHAR_BIT*sizeof(long long))
#define FLT_BIT		(CHAR_BIT*sizeof(float))

#define TRUE	1
#define FALSE	0
#define MAXLINE	1024
#define TABSTOP	4
#define MAXDEPTH	128

// Chapter 1
void FahrenheitToCelsius(void);
void FahrenheitToCelsiusReal(void);
void CelsiusToFahrenheit(void);
void CelsiusToFahrenheitReal(void);
void FahrenheitToCelsiusRealCompact(void);
void FahrenheitToCelsiusCompact(void);
void FahrenheitToCelsiusCompactReverse(void);

void copyInputToOutput(void);
void countCharactersInInput(void);
void countLinesInInput(void);
void countWhitespacesInInput(void);
void replaceBlankStringWithBlank(void);
void copyInputReplaceSpecial(void);
void countWordsLinesCharsInInput(void);
void printInputOneWordPerLine(void);

void countDigitWhiteSpOther(void);
void wordsLengthsHistogram(void);
void characterLengthsHistogram(void);

int power(int base, int exp);
int powerEfficient(int base, int exp);

int getLine(char s[], int lim);
void copyString(char to[], char from[]);
int stringLength(char s[]);
int isBlankString(char s[]);
void removeTrailingBlanks(char s[]);
void reverseString(char s[]);

void printLongestInputLine(void);
void printInputLinesGreater(void);
void removeSpecialFromInput(void);
void reverseInputLine(void);

void detab(void);
void entab(void);
void foldNaive(const int nthChar);
void fold2(const int nthChar);
void fold2Recursive(char line[], const int startIdx, const int nthIdx);
void balanceTokens(void);
int pop(void);
void push(int c);
void initialize(void);

// Chapter 2
void determineRanges(void);
long powerl(int base, int exp);
unsigned long powerul(int base, int exp);
long long powerll(int base, int exp);
unsigned long long powerull(int base, int exp);
double powerf(double base, int exp);
void ChkForLeapYear(int y);
int getline3(char s[], int lim);
void copy(char to[], char from[]);
void longest(void);
int getline2(char s[], int lim);
int atoiNaive(char s[]);
int lower(int c);
int rand(void);
void srand(unsigned int seed);
int htoi(char s[]);
void squeeze(char s[], int c);
void Strcat(char s[], char t[]);
void squeeze2(char t[], char s[]);
int any(char s1[], char s2[]);
unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, const unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);
int bitcount(unsigned x);
int bitcountfaster(unsigned x);
int lowerSuccinct(int c);
void printCharArray(void);
void pluralStringCondn(void);

// Chapter 3
int binsearch(int x, int v[], int n);
int binsearchfast(int x, int v[], int n);
void countDigitWhiteSpOther2(void);
void escape(char s[], char t[]);
void escapeRev(char s[], char t[]);
int atoi2(char s[]);
void shellsort(int v[], int n);
void reverse(char s[]);
int subStringIdx(char s[], char t[]);
void expand(char s[], char t[], int tn);
void itoa(int n, char s[]);
void itob(int n, char s[], int b);
void itoaW(int n, char s[], int w);
int trim(char s[]);

#endif /* CPROJECT_H */
