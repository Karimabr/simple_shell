#include "simple_shell.h"
/**
 * _getarg - a function gets a command from standard input
 * @ln: buffer to store the command
 * @exert: The return value of the last executed command
 * Return: pointer to the command
 */
char *_getarg(char *ln, int *exert)
{
	ssize_t rd;
	char *shellprompt;
	size_t num;

	num = 0;
	shellprompt = "$ ";
	if (ln)
	{
		free(ln);
	}

	rd = _getline(&ln, &num, STDIN_FILENO);
	if (rd == -1)
	{
		return (NULL);
	}
	if (rd == 1)
	{
		hst++;
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, shellprompt, 2);
		}
		return (_getarg(ln, exert));
	}
	ln[rd - 1] = '\0';

	_var_rep(&ln, exert);

	_handline(&ln, rd);

	return (ln);
}

/**
 * _callarg - Partitions operators from commands and calls them
 * @arg: An array of arguments
 * @fnt: A double pointer to the beginning of args
 * @exert: The return value of the parent process' last executed command
 * Return: The return value of the last executed command
 */
int _callarg(char **arg, char **fnt, int *exert)
{
	int _rt;
	int count;

	if (!arg[0])
	{
		return (*exert);
	}
	for (count = 0; arg[count]; count++)
	{
		if (strncompare(arg[count], "||", 2) == 0)
		{
			free(arg[count]);

			arg[count] = NULL;
			arg = _switchaliases(arg);
			_rt = _exearg(arg, fnt, exert);

			if (*exert != 0)
			{
				arg = &arg[++count];
				count = 0;
			}
			else
			{
				for (count++; arg[count]; count++)
				{
					free(arg[count]);
				}
				return (_rt);
			}
		}
		else if (strncompare(arg[count], "&&", 2) == 0)
		{
			free(arg[count]);

			arg[count] = NULL;
			arg = _switchaliases(arg);

			_rt = _exearg(arg, fnt, exert);
			if (*exert == 0)
			{
				arg = &arg[++count];
				count = 0;
			}
			else
			{
				for (count++; arg[count]; count++)
				{
					free(arg[count]);
				}
				return (_rt);
			}
		}
	}
	arg = _switchaliases(arg);
	_rt = _exearg(arg, fnt, exert);
	return (_rt);
}

/**
 * _exearg - a function that executs of a command.
 * @arg: array of arguments.
 * @fnt: double pointer to the beginning of args.
 * @exert: return value of the parent process' last executed command.
 * Return: return value of the last executed command.
 */
int _exearg(char **arg, char **fnt, int *exert)
{
	int _r;
	int (*build)(char **arg, char **fnt);
	int count;

	build = _getbuilt(arg[0]);

	if (build)
	{
		_r = build(arg + 1, fnt);

		if (_r != -3)
		{
			*exert = _r;
		}
	}
	else
	{
		*exert = _exe(arg, fnt);
		_r = *exert;
	}

	hst++;

	for (count = 0; arg[count]; count++)
	{
		free(arg[count]);
	}

	return (_r);
}

/**
 * _handleargmnt - a function gets, calls, and runs the execution of a command.
 * @exert: a value to be returned
 * Return: exit value of the last command
 */
int _handleargmnt(int *exert)
{
	int _r;
	int count;
	char **arg, *str, **fnt;

	str = NULL;
	_r = 0;
	str = _getarg(str, exert);
	if (!str)
	{
		return (EOF);
	}

	arg = _strtok_(str, " ");
	free(str);
	if (!arg)
	{
		return (_r);
	}
	if (_checkonarg(arg) != 0)
	{
		*exert = 2;
		_freearg(arg, arg);

		return (*exert);
	}

	fnt = arg;

	for (count = 0; arg[count]; count++)
	{
		if (strncompare(arg[count], ";", 1) == 0)
		{
			free(arg[count]);

			arg[count] = NULL;
			_r = _callarg(arg, fnt, exert);

			arg = &arg[++count];
			count = 0;
		}
	}
	if (arg)
	{
		_r = _callarg(arg, fnt, exert);
	}

	free(fnt);
	return (_r);
}

/**
 * _checkonarg - Checks if there are any leading
 * @arg: pointer to tokenized commands and arguments
 * Return: 0 in case of success, 2 if arguments are misplaced
 */
int _checkonarg(char **arg)
{
	char *tmp;
	size_t count;
	char *n;

	for (count = 0; arg[count]; count++)
	{
		tmp = arg[count];
		if (tmp[0] == ';' || tmp[0] == '&' || tmp[0] == '|')
		{
			if (tmp == 0 || tmp[1] == ';')
			{
				return (_crterr(&arg[count], 2));
			}
			n = arg[count + 1];
			if (n && (n[0] == ';' || n[0] == '&' || n[0] == '|'))
			{
				return (_crterr(&arg[count + 1], 2));
			}
		}
	}
	return (0);
}
