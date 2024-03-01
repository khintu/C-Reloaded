#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <c-project.h>


void doNothingMain(int signum)
{
	//printf("Hello from signal handler %d\n", signum);
	return;
}

void UnitTestMain(int argc, char* argv[])
{
	int i = 0;
	//char line[MAXLINE] = "ab0-9cdef0-9klm  ";
	char line[MAXLINE] = "am i ckuld i do you wkuld\n";
	//char line2[MAXLINE] = "";
	char line2[MAXLINE] = { 0 };
	char line3[MAXLINE] = "abcdefg";
#ifdef __LINUX__
	i += stringLength(line);
	i += stringLength(line2);
#endif
	
	//--- Chapter 1 ---
	printf("hello, world\n");
	printf("Fahrenheit To Celsius\n");
	FahrenheitToCelsiusRealCompact();
	printf("Celsius To Fahrenheit\n");
	CelsiusToFahrenheit();
	FahrenheitToCelsiusCompactReverse();

	copyInputToOutput();
	countCharactersInInput();
	countLinesInInput();
	countWhitespacesInInput();
	replaceBlankStringWithBlank();
	copyInputReplaceSpecial();
	countWordsLinesCharsInInput();
	printInputOneWordPerLine();
	countDigitWhiteSpOther();
	wordsLengthsHistogram();
	characterLengthsHistogram();

	for (i = 0; i <= 10; ++i)
		printf("Base %d Exp %2d Result %5d\n", 3, i, power(3, i));
	for (i = 0; i <= 10; ++i)
		printf("Base %d Exp %2d Result %5d\n", 2, i, powerEfficient(2, i));

	printf("line lenght %d, line <%s>,\n", getLine(line, MAXLINE), line);
	printLongestInputLine();
	printInputLinesGreater();
	removeSpecialFromInput();
	reverseInputLine();

	detab();
	entab();
	fold2(5);
	balanceTokens();

	//--- Chapter 2 ---
	determineRanges();
	putchar('\a');
	ChkForLeapYear(6400);
	longest();
	printf("%d\n", atoiNaive("123"));
	putchar(lower('S'));

	Srand(112);
	for (i = 0; i < 10; ++i)
		printf("%d\n", Rand());

	i = Htoi("0xffff");
	printf("%d", i);

	squeeze(line, 'd');
	printf("%s\n", line);
	Strcat(line, "defop");
	printf("%s\n", line);

	squeeze2(line, " a");
	printf("%s\n", line);

	i = any(line, " a");
	printf("%d\n", i);
	
	printf("%x\n", getbits(0xf7, 5, 3));
	printf("%x\n", setbits(0xFF, 5, 3, 0xF6));
	printf("%x\n", invert(0xFF, 5, 3));
	printf("%x\n", rightrot(0xFFFFFFF0, 3));
	printf("%x\n", bitcount(0x00));
	printf("%x\n", bitcountfaster(0x06));

	putchar(lowerSuccinct('s'));
	printCharArray();
	pluralStringCondn();
	
	//--- Chapter 3 ---
	
	testBinSearch();
	countDigitWhiteSpOther2();
	testEscapeRev();
	printf("%d\n", atoi2(" -127e34"));
	testShellSort();
	reverse(line);
	printf("%s\n", line);
	printf("%d\n", subStringIdx("abc", "x"));
	expand(line, line2, MAXLINE);
	printf("%s\n%s\n", line, line2);
	itob(power(-2, 31), line2, 11);
	printf("%s\n", line2);
	itoaW(-1234567, line2, 1);
	printf("%s\n", line2);
	trim(line);
	printf("%s#\n", line);

	// --- Chapter 4 ---
	findLinesMatchgPattrn("ould\n");
	if ((i = strrindex(line, "ould")) >= 0)
	{
		printf("%d\n", i);
	}
	printf("%.6f\n", Atof("-.112734"));
	printf("%g\n", atofE("-.112734E-6"));
	reversePolishCalc();
	printDecimal(-powerEfficient(2, 31));
	putchar('\n');
	Itoa2(-powerEfficient(2, 31), line3);
	printf("%s\n", line3);
	reverseString2(line3, stringLength(line3), 0);
	printf("%s\n", line3);
	testSwapMacro();

	// --- Chapter 5 ---
	testGetIntFrmCmdLine();
	testGetFloatFrmCmdLine();
	printf("%i\n", StrLen("a$b#"));
	printf("%i\n", StrCmpArry("abc", "abc"));
	printf("%i\n", StrCmpPtr("abc", "abc"));
	testStrEnd();
	testAllStrNFunc();
	printf("%d\n", strindexPtr("would", "kould"));
	testShellSort();
	SortInputLines();
	testMonthOfDayAndYear();
	test2DArryMemoryLayout();
	findLinesMatchgPattrn2(argc, argv);
	return;
}

int main(int argc, char *argv[])
{
	clock_t t1, t2;
	t1 = clock();
	signal(SIGINT, doNothingMain);

	// ---Main Function to Execute ---
	for (int ic = 1; ic < argc ; ++ic)
	{
		//printf("%s%s", *++argv,  argc > 1 ? " " : "");
		//printf(argc > 1 ? "%s " : "%s", *++argv);
		printf("%s%s", argv[ic], ic < argc -1 ? " " : "");
	}
	printf("\n");

	//UnitTestMain(argc, argv); /* Put Your Code below */
	return findLinesMatchgPattrn3(argc, argv);

	// ---Runtime Analysis ---
	t2 = clock();
	printf("Runtime = %ld - %ld = %ld\n", t2, t1, t2 - t1);
	return 0;
}