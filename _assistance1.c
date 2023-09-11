#include "simple_shell.h"

/**
 * _handline - a function that Partitions a line read from stdin as needed
 * @str: A pointer to a line read from standard input
 * @rd: The length of line.
 */
void _handline(char **str, ssize_t rd)
{
	char *prevline, *newline;
	char old, tmp, n;
	size_t count, c1;
	ssize_t newlength;

	c1 = 0;
	newlength = _getnew_str(*str);
	if (newlength == rd - 1)
	{
		return;
	}
	newline = malloc(newlength + 1);
	if (!newline)
	{
		return;
	}
	prevline = *str;
	for (count = 0; prevline[count]; count++)
	{
		tmp = prevline[count];
		n = prevline[count + 1];

		if (count != 0)
		{
			old = prevline[count - 1];
			if (tmp == ';')
			{
				if (n == ';' && old != ' ' && old != ';')
				{
					newline[c1++] = ' ';
					newline[c1++] = ';';
					continue;
				}

				else if (old == ';' && n != ' ')
				{
					newline[c1++] = ';';
					newline[c1++] = ' ';
					continue;
				}
				if (old != ' ')
				{
					newline[c1++] = ' ';
				}
				newline[c1++] = ';';
				if (n != ' ')
				{
					newline[c1++] = ' ';
				}
				continue;
			}
			else if (tmp == '&')
			{
				if (n == '&' && old != ' ')
				{
					newline[c1++] = ' ';
				}
				else if (old == '&' && n != ' ')
				{
					newline[c1++] = '&';
					newline[c1++] = ' ';
					continue;
				}
			}
			else if (tmp == '|')
			{
				if (n == '|' && old != ' ')
				{
					newline[c1++]  = ' ';
				}
				else if (old == '|' && n != ' ')
				{
					newline[c1++] = '|';
					newline[c1++] = ' ';
					continue;
				}
			}
		}
		else if (tmp == ';')
		{
			if (count != 0 && prevline[count - 1] != ' ')
			{
				newline[c1++] = ' ';
			}
			newline[c1++] = ';';
			if (n != ' ' && n != ';')
			{
				newline[c1++] = ' ';
			}
			continue;
		}
		newline[c1++] = prevline[count];
	}
	newline[c1] = '\0';

	free(*str);
	*str = newline;
}

/**
 * _getnew_str - a function Gets the new length of a partitioned line
 * @string: The line to check.
 * Return: The new length of the line.
 */
ssize_t _getnew_str(char *string)
{
	ssize_t _nlen;
	char tmp, n;
	size_t count;

	for (count = 0; string[count]; count++)
	{
		tmp = string[count];
		n = string[count + 1];

		if (tmp == '#')
		{
			if (count == 0 || string[count - 1] == ' ')
			{
				string[count] = '\0';
				break;
			}
		}
		else if (count != 0)
		{
			if (tmp == ';')
			{
				if (n == ';' && string[count - 1] != ' ' && string[count - 1] != ';')
				{
					_nlen += 2;
					continue;
				}
				else if (string[count - 1] == ';' && n != ' ')
				{
					_nlen += 2;
					continue;
				}
				if (string[count - 1] != ' ')
				{
					_nlen++;
				}
				if (n != ' ')
				{
					_nlen++;
				}
			}
			else
			{
				_operators(&string[count], &_nlen);
			}
		}
		else if (tmp == ';')
		{
			if (count != 0 && string[count - 1] != ' ')
			{
				_nlen++;
			}
			if (n != ' ' && n != ';')
			{
				_nlen++;
			}
		}
		_nlen++;
	}
	return (_nlen);
}
/**
 * _operators - Checks a line for logical operators
 * @str: A pointer to the character to check in the line
 * @nlength: Pointer to new_len in get_new_len function
 * Return: void returns nothing
 */
void _operators(char *str, ssize_t *nlength)
{
	char old, tmp, n;


	tmp = *str;
	n = *(str + 1);
	old = *(str - 1);

	if (tmp == '&')
	{
		if (n == '&' && old != ' ')
		{
			(*nlength)++;
		}
		else if (old == '&' && n != ' ')
		{
			(*nlength)++;
		}
	}
	else if (tmp == '|')
	{
		if (n == '|' && old != ' ')
		{
			(*nlength)++;
		}
		else if (old == '|' && n != ' ')
		{
			(*nlength)++;
		}
	}
}
