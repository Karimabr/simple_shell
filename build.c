#include "simple_shell.h"

/**
 * _getbuilt - Matches a command with a corresponding
 * @comnd: The command to match.
 * Return: A function pointer to the corresponding builtin.
 */
int (*_getbuilt(char *comnd))(char **arg, char **fnt)
{
	int i;

	build_t functions[] = {
		{ "exit", _shellexit },
		{ "env", _shellenv },
		{ "setenv", _shellsetenv },
		{ "unsetenv", _shellunsetenv },
		{ "cd", _shellcd },
		{ "alias", _shellalias },
		{ NULL, NULL }
	};

	for (i = 0; functions[i].nm; i++)
	{
		if (strcompare(functions[i].nm, comnd) == 0)
		{
			break;
		}
	}
	return (functions[i].f);
}

/**
 * _shellexit - Causes normal process termination
 * @arg: An array of arguments containing the exit value.
 * @fnt: A double pointer to the beginning of args.
 * Return: exit with the given status value
 */
int _shellexit(char **arg, char **fnt)
{
	int i, int_len;
	unsigned int number, maximum;

	int_len = 10;
	number = 0;
	maximum = 1 << (sizeof(int) * 8 - 1);
	if (arg[0])
	{
		if (arg[0][0] == '+')
		{
			i = 1;
			int_len++;
		}
		for (; arg[0][i]; i++)
		{
			if (i <= int_len && arg[0][i] >= '0' && arg[0][i] <= '9')
			{
				number = (number * 10) + (arg[0][i] - '0');
			}
			else
			{
				return (_crterr(--arg, 2));
			}
		}
	}
	else
	{
		return (-3);
	}
	if (number > maximum - 1)
	{
		return (_crterr(--arg, 2));
	}
	arg -= 1;

	_freearg(arg, fnt);
	_freeenviron();
	_freealiasfin(aliases);

	exit(number);
}

/**
 * _shellcd - Changes the current directory of the shellby process.
 * @arg: An array of arguments.
 * @fnt: A double pointer to the beginning of args.
 * Return: 0 in case of success or -2 or -1 in case of error
 */
int _shellcd(char **arg, char **fnt)
{
	(void)fnt;
	char **drc_inf, *_newline;
	char *old_pwd, *pwd;
	struct stat drc;

	old_pwd = NULL;
	pwd = NULL;
	_newline = "\n";
	old_pwd = getcwd(old_pwd, 0);
	if (!old_pwd)
	{
		return (-1);
	}
	if (arg[0])
	{
		if (*(arg[0]) == '-' || strcompare(arg[0], "--") == 0)
		{
			if ((arg[0][1] == '-' && arg[0][2] == '\0') || arg[0][1] == '\0')
			{
				if (get_env("OLDPWD") != NULL)
				{
					(chdir(*get_env("OLDPWD") + 7));
				}
			}
			else
			{
				free(old_pwd);
				return (_crterr(arg, 2));
			}
		}
		else
		{
			if (stat(arg[0], &drc) == 0 && S_ISDIR(drc.st_mode) && ((drc.st_mode & S_IXUSR) != 0))
			{
				chdir(arg[0]);
			}
			else
			{
				free(old_pwd);
				return (create_error(arg, 2));
			}
		}
	}
	else
	{
		if (get_env("HOME") != NULL)
		{
			chdir(*(get_env("HOME")) + 5);
		}
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		return (-1);
	}

	drc_inf = malloc(sizeof(char *) * 2);
	if (!drc_inf)
		return (-1);

	drc_inf[0] = "OLDPWD";
	drc_inf[1] = old_pwd;
	if (_shellunsetenv(drc_inf, drc_inf) == -1)
		return (-1);

	drc_inf[0] = "PWD";
	drc_inf[1] = pwd;
	if (_shellsetenv(drc_inf, drc_inf) == -1)
		return (-1);
	if (arg[0] && arg[0][0] == '-' && arg[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, str_length(pwd));
		write(STDOUT_FILENO, _newline, 1);
	}
	free(old_pwd);
	free(pwd);
	free(drc_inf);
	return (0);
}
