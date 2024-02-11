#include <stdio.h>
#include <string.h>
#include <c-project.h>

void copyString(char to[], char from[])
{
	int i;
	for (i = 0; (to[i] = from[i]) != '\0'; ++i)
		;
	return;
}

int stringLength(char s[])
{
	int i = 0;
	while (s[i] != '\0')
		++i;
	return i;
}

int isBlankString(char s[])
{
	if (stringLength(s) > 0 && s[0] == '\n')
		return TRUE;
	return FALSE;
}

#define IN	1
#define OUT	0
void removeTrailingBlanks(char s[])
{
	int i = 0, state = OUT, iIn = -1;
	while (s[i] != '\0')
	{
		if (state == OUT && (s[i] == '\t' || s[i] == ' '))
		{
			state = IN;
			iIn = i;
		}
		else if (state == IN && (s[i] != '\t' && s[i] != ' ' && s[i] != '\n'))
			state = OUT;
		++i;
	}
	if (iIn >= 0 && state == IN)
		s[iIn] = '\0';
	return;
}
#undef IN
#undef OUT

void reverseString(char s[])
{
	int i, ri, len;
	char tmp;

	len = stringLength(s);
	i = 0; ri = len - 1;
	while (s[i] != '\0' && i < (len/2))
	{
		tmp = s[i];
		s[i] = s[ri];
		s[ri] = tmp;
		++i;--ri;
	}
	return;
}

void initialize(void)
{
	extern int itop;
	itop = -1;
}

int pop(void)
{
	extern int stack[];
	extern int itop;
	int c;
	if (itop >= 0)
	{
		c = stack[itop];
		--itop;
		return c;
	}
	return -1;
}

void push(int c)
{
	extern int stack[];
	extern int itop;
	if (itop <= MAXDEPTH - 2)
	{
		++itop;
		stack[itop] = c;
	}
	return;
}

void copy(char to[], char from[])
{
	int i = 0;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

void Strcat(char s[], char t[])
{
	int i, j;
	i = j = 0;
	while (s[i] != '\0')
		i++;
	while ((s[i++] = t[j++]) != '\0')
		;
	return;
}

/* 
	the swap will continue till half the way in the 
	input string, where the iteration will stop as 
	i becomes equal or greater than j. Loop will break
	when i > j or i == j, in even and odd strlen cases
	respectively.
 */
void reverse(char s[])
{
	int c, j, i;
	for (i = 0, j = (int)strlen(s) - 1;\
		i < j;\
		++i, --j)
		c = s[i], s[i] = s[j], s[j] = c;
	return;
}

/* Returns the first occurence of t in s or 
	returns -1 for no match or empty string */
int subStringIdx(char s[], char t[])
{
	int i, j, sl, tl, found;

	sl = stringLength(s);
	tl = stringLength(t);
	for (i = 0; i < sl; ++i)
	{
		for (found = 0, j = 0; j < tl; ++j)
			if (i + j < sl && s[i + j] == t[j])
				found++;
		
		if (tl != 0 && found == tl)
			return i;
	}
	return -1;
}