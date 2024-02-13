#include <stdio.h>
#include <ctype.h>
#include <c-project.h>

int findLinesMatchgPattrn(char p[])
{
	int found;
	char line[MAXLINE];

	found = 0;
	while(getline4(line, MAXLINE) > 0)
		if (strindex(line, p) >= 0)
		{
			printf("%s", line);
			found++;
		}
	return found;
}

int getline4(char s[], int lim)
{
	int i, c;

	i = 0; c = '\0';
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return i;
}

int strindex(char s[], char t[])
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; ++i)
	{
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

int strrindex(char s[], char t[])
{
	int i, fndi, rmi;
	
	for (i = 0, fndi = 0, rmi = -1; s[i] != '\0'; ++i)
	{
		fndi = strindex(s + i, t);
		if (fndi >= 0)
			rmi = fndi + i;
	}
	return rmi;
}

double atof(char s[])
{
	double val, power;
	int sign, i;

	for (i = 0; isspace(s[i]); ++i)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		++i;
	for (val = 0.0; isdigit(s[i]); ++i)
		val = val * 10.0 + s[i] - '0';
	if (s[i] == '.')
		++i;
	for (power = 1.0; isdigit(s[i]); ++i)
	{
		val = val * 10.0 + s[i] - '0';
		power *= 10.0;
	}
	return sign * val / power;
}