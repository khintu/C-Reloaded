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
#define NUL	((char)0)
#define PI	(22.0f/7.0f)

#define Abs(exp)	(((exp) >= 0)? (exp) : -(exp))

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
int Rand(void);
void Srand(unsigned int seed);
int Htoi(char s[]);
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
void testBinSearch(void);
void countDigitWhiteSpOther2(void);
void escape(char s[], char t[]);
void escapeRev(char s[], char t[]);
void testEscapeRev(void);
int atoi2(char s[]);
void ShellSort(int v[], int n);
void testShellSort(void);
void reverse(char s[]);
int subStringIdx(char s[], char t[]);
void expand(char s[], char t[], int tn);
void Itoa(int n, char s[]);
void itob(int n, char s[], int b);
void itoaW(int n, char s[], int w);
int trim(char s[]);

// Chapter 4
int getline4(char s[], int lim);
int strindex(char s[], char t[]);
int findLinesMatchgPattrn(char p[]);
int strrindex(char s[], char t[]);
double Atof(char s[]);
double atofE(char s[]);
void reversePolishCalc(void);
int getoperator(char []);
void push2(double);
double pop2(void);
int getch(void);
void ungetch(int c);
void printTopStck(void);
void dupTopStck(void);
void swpTop2Stck(void);
void clearStck(void);
void push3(char c);
char pop3(void);
int getoperator2(char s[]);
void printDecimal(int n);
void Itoa2(int n, char s[]);
void reverseString2(char s[], int len, int i);
void testSwapMacro(void);
void QuickSort(int v[], int left, int right);

// Chapter 5
int getInt(int*);
void testGetIntFrmCmdLine(void);
int getFloat(double* pn);
void testGetFloatFrmCmdLine(void);
int StrLen(char* s);
void StrCpyArry(char* s, char* t);
void StrCpyPtr(char* s, char* t);
int StrCmpArry(char* s, char* t);
int StrCmpPtr(char* s, char* t);
void testStrCat(void);
int StrEnd(char* s, char* t);
void testStrEnd(void);
void StrNCpy(char* s, char* t, int n);
int StrNCmp(char* s, char* t, int n);
void StrNCat(char* s, char* t, int n);
void testAllStrNFunc(void);
int strindexPtr(char *s, char *t);
void BubbleSort(int v[], int n);
char* AllocChar(int n);
void AllocFree(char* p);
void SortInputLines(void);
int ReadLines(char* linePtr[], int nlines);
void WriteLines(char* linePtr[], int nlines);
void QuickSortStr(char* lineptr[], int left, int right);
int DayOfYear(int year, int month, int day);
void MonthOfDay(int year, int yearday, int* pmonth, int* pda);
void testMonthOfDayAndYear(void);
char* MonthName(int n);
void test2DArryMemoryLayout(void);

#endif /* CPROJECT_H */
