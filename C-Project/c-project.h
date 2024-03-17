#ifndef CPROJECT_H
#define CPROJECT_H

#define STRKEY(key)	#key

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

#define ABS(exp)	(((exp) >= 0)? (exp) : -(exp))
#define MIN(a, b)	((a) < (b) ? (a) : (b))
#define MAX(a, b)	((a) > (b) ? (a) : (b))

/* Reverse Polish Calculator definitions */
#define MAXVAL	100	/* max depth of value stack */
#define MAXOP		100	/* max size of operand or operator */
#define NUMBER	'0'	/* Signal that a number was found */
#define PRNTTOP	'T' /* Command for printing top of stack */
#define DUPLTOP	'D' /* Command for duplicating top of stack */
#define SWPTOP2	'W' /* Command for duplicating top of stack */
#define CLRSTK	'C' /* Command for duplicating top of stack */
#define SINFX		'S' /* math sin function x radians */
#define EXPFX		'E'	/* math exp function x */
#define POWFX		'P' /* math power function x,y */
#define BUFSIZE	100 /* max pushback buffer for reading ahead from getchar */


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
void reversePolishCalc(int argc, char *argv[]);
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
int findLinesMatchgPattrn2(int argc, char* argv[]);
int findLinesMatchgPattrn3(int argc, char* argv[]);
void InsertionSort(int v[], int n);
int getoperator3(char s[], int *argc, char* *argv[]);
void detab2CmdLine(int argc, char* argv[]);
void detab2(int tabStop);
void entab2CmdLine(int argc, char* argv[]);
void entab2(int tabStop);
void detab2CmdLine2(int argc, char* argv[]);
void detab3(int tabStop, int mCol, int nCol);
void entab2CmdLine2(int argc, char* argv[]);
void entab3(int tabStop, int mCol, int nCol);
void TailCmdLine(int argc, char *argv[]);
void TailPrintLastNLines(int nLines);
void AppendStrToBuffer(char* dbuf[], char line[], int* dbIn, int nLines);
void SortInputLines2(int argc, char* argv[]);
void QuickSort2(void* v[], int left, int right, int (*cmp)(void*, void*));
int numcmp(char*, char*);
int numcmp2(char* s1, char* s2);
void swap(void* v[], int i, int j);
int StrCmpRev(char* s, char* t);
int StrCaseCmp(char* s, char* t);
int StrDirCmp(char* s, char* t);
int StrDirCaseCmp(char* s, char* t);
void QuickSort3(void* v[], int left, int right, int (*cmp)(void*, void*, int), int field);
int StrFieldCmp(char* s, char* t, int field);
int numcmpField(char* s1, char* s2, int field);
int numcmp2Field(char* s1, char* s2, int field);
int StrFieldCmpRev(char* s, char* t, int field);
int StrFieldCaseCmp(char* s, char* t, int field);
int StrFieldDirCmp(char* s, char* t, int field);
int StrFieldDirCaseCmp(char* s, char* t, int field);
void RecursiveDescentParser(void);
void ParserDcl(void);
void ParserDirDcl(void);
int ParserGetToken(void);
void RDPUnDcl(void);

// Chapter 6
void testStructuresDecl(void);
struct point makePoint(int x, int y);
struct point addPoint(struct point p1, struct point p2);
int ptInRect(struct point pt, struct rect r);
struct rect canonRect(struct rect r);
void testPtr2Struct(void);
void keywordCountingProgram(void);
int kcpGetWord(char* word, int lim);
int kcpBinSearch(char* word, struct key tab[], int n);
int kcpGetWordBetter(char* word, int lim);
void keywordCountingProgram2(void);
struct key* kcpBinSearch2(char* word, struct key* tab, int n);
struct tnode* BinTreeAddNode(struct tnode* p, char* w);
void BinTreePrint(struct tnode* p);
void WordFreqCount(void);
void GroupOfNamesIdentInNCmp(int argc, char* argv[]);
void PrintGroupsOfVarsNSizd(int ncount);
struct lnode* LstAddWrdToWordGrp(char* word, int ncount, struct lnode* group);
int CRBinSearch(char* word, char* noise[], int n);
struct CRTree* CRTreeAddNode(struct CRTree* p, char* w, int lineNo);
void CRTreePrint(struct CRTree* p);
void CrossReferencerProgam(void);
int CRGetWord(char* word, int lim);
void WordFreqCount2(void);
void BinTreePrint2(struct tnode* p);
char* StrDup(char* s);
struct FSLNode* FSAddWordToLst(struct FSLNode* lst, char* word);
struct FSTNode* FSAddWordToTree(struct FSTNode* root, struct FSLNode* lst);
void FSTreePrint(struct FSTNode* p);
void FreqSortedInput(void);
unsigned HHashFunc(char* s);
struct HList* HLookUp(char* s);
struct HList* HInstall(char* name, char* defn);
void HUnDef(char* name);
void HMacroProcessor(void);
int HGetWord(char* word, int lim);

// Chapter 7
void printLowerToUpper(int argc, char* argv[]);
void printInputToOutput(void);
void minprintf(char* fmt, ...);

#endif /* CPROJECT_H */