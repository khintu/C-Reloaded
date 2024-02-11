#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <c-project.h>

char glbLine[MAXLINE];

void doNothingMain(int signum)
{
	//printf("Hello from signal handler %d\n", signum);
	return;
}

int main()
{
	//int i;
	char line[MAXLINE] = "ab0-9cdef0-9klm";
	char line2[MAXLINE];

	clock_t t1, t2;
	t1 = clock();
	signal(SIGINT, doNothingMain);

	//--- Chapter 1 ---
	printf("hello, world\n");
	//printf("Fahrenheit To Celsius\n");
	//FahrenheitToCelsiusRealCompact();
	//printf("Celsius To Fahrenheit\n");
	//CelsiusToFahrenheit();
	//FahrenheitToCelsiusCompactReverse();

	//copyInputToOutput();
	//countCharactersInInput();
	//countLinesInInput();
	//countWhitespacesInInput();
	//replaceBlankStringWithBlank();
	//copyInputReplaceSpecial();
	//countWordsLinesCharsInInput();
	//printInputOneWordPerLine();
	//countDigitWhiteSpOther();
	//wordsLengthsHistogram();
	//characterLengthsHistogram();

	//for (i = 0; i <= 10; ++i)
	//	printf("Base %d Exp %2d Result %5d\n", 3, i, power(3, i));
	//for (i = 0; i <= 10; ++i)
	//	printf("Base %d Exp %2d Result %5d\n", 2, i, powerEfficient(2, i));

	//printf("line lenght %d, line <%s>,\n", getLine(line, MAXLINE), line);
	//printLongestInputLine();
	//printInputLinesGreater();
	//removeSpecialFromInput();
	//reverseInputLine();

	//detab();
	//entab();
	//fold2(5);
	//balanceTokens();

	//--- Chapter 2 ---
	//determineRanges();
	//putchar('\a');
	//ChkForLeapYear(6400);
	//longest();
	//printf("%d\n", atoiNaive("123"));
	//putchar(lower('S'));

	/*srand(112);
	for (i = 0; i < 10; ++i)
		printf("%d\n", rand());*/
	/*i = htoi("0xffff");
	printf("%d", i);*/

	/*squeeze(line, 'd');
	printf("%s\n", line);*/
	/*Strcat(line, "defop");
	printf("%s\n", line);*/

	/*squeeze2(line, " a");
	printf("%s\n", line);*/

	/*i = any(line, " a");
	printf("%d\n", i);*/
	
	//printf("%x\n", getbits(0xf7, 5, 3));
	//printf("%x\n", setbits(0xFF, 5, 3, 0xF6));
	//printf("%x\n", invert(0xFF, 5, 3));
	//printf("%x\n", rightrot(0xFFFFFFF0, 3));
	//printf("%x\n", bitcount(0x00));
	//printf("%x\n", bitcountfaster(0x06));

	//putchar(lowerSuccinct('s'));
	//printCharArray();
	//pluralStringCondn();
	
	//--- Chapter 3 ---
	//do {
	//	//int i;
	//	int sorted[50] = { 100,110,120,130,200,210,220,230,240,300,
	//						310,312,313,314,315,316,326,333,343,353,
	//						357,365,367,377,380,386,390,400,410,415,
	//						420,422,426,430,435,440,444,445,450,455,
	//						460,461,462,463,464,465,470,472,474,479
	//					};
	//	//for (i = 0; i < 10000000; ++i)
	//	{			
	//		//binsearchfast(sorted[i%50], sorted, 50);
	//	}
	//	printf("Found %s\n",binsearchfast(100, sorted, 50) >=0 ? "Yes" : "No");
	//} while (0);
	//countDigitWhiteSpOther2();
	
	/*do {
		char s[MAXLINE], t[MAXLINE];
		getLine(s, MAXLINE);
		escapeRev(t, s);
		printf("%s\n", t);
	} while (0);*/

	//printf("%d\n", atoi2(" -127e34"));

	/*do {
		int i;
		int v[10] = { 400,10,3,70,0,44,390,210,100,33 };
		shellsort(v, 10);
		for (i = 0; i < 10; ++i)
			printf("%d%s", v[i], i < 9 ? "," : "\n");
	} while (0);*/

	/*reverse(line);
	printf("%s\n", line);*/
	
	//printf("%d\n", subStringIdx("abc", "x"));

	expand(line, line2, MAXLINE);
	printf("%s\n%s\n", line, line2);

	// ---Runtime Analysis ---
	t2 = clock();
	printf("Runtime = %ld - %ld = %ld\n", t2, t1, t2 - t1);
	return 0;
}
