#include "simple_shell.h"
/**
 * stringchr - finds characters in strings
 * @str: string
 * @chars: characters to locate
 * Return: returns a pointer
*/
char *stringchr(char *str, char chars)
{
	char *ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == chars)
		{
			return (ptr);
		}
		ptr++;
	}
	return (NULL);
}
/**
 * stringspn - a function that gets length of a substring
 * @str: a string
 * @take: substring
 * Return: number of bytes
*/
int stringspn(char *str, char *take)
{
	char *p;
	char *q;

	p = str;
	while (*p)
	{
		q = take;

		while (*q)
		{
			if (*p == *q)
				break;
			q++;
		}

		if (*q == '\0')
		{
			break;
		}
		p++;
	}

	return (p - str);
}
/**
 * strcompare - a function to compare two strings
 * @str: string to compare
 * @str1: string to compare
 * Return: returns the difference between strings
*/
int strcompare(char *str, char *str1)
{
	int i;

	while (str[i] && str1[i] && str[i] == str1[i])
	{
		i++;
	}
	return (str[i] - str1[i]);
}
/**
 * strncompare - a function to compare two strings
 * @str: a string to compare
 * @str1: a string to compare
 * @num: size in bytes
 * Return: return the difference between the two strings
*/
int strncompare(const char *str, const char *str1, size_t num)
{
	const char *ptr;

	ptr = str;
	while (*ptr && *ptr == *str1 && num > 0)
	{
		ptr++;
		str1++;
		num--;
	}

	if (num == 0)
	{
		return (0);
	}
	return (*ptr - *str1);
}
/**
 * seg_fault - a function that handles seg fault
 * @a: a character
*/
void seg_fault(char a)
{
	(void)a;
	char *p;

	p = "$ ";
	signal(SIGINT, seg_fault);
	write(STDIN_FILENO, p, 2);
}
