#include "simple_shell.h"
/**
 * _shellenv - Prints the current environment.
 * @arg: An array of arguments passed to the shell.
 * @fnt: A double pointer to the beginning of args.
 * Return: 0, -1 on error case
 */
int _shellenv(char **arg, char **fnt)
{
	(void)fnt;
	(void)arg;
	int i;
	char c;

	c = '\n';
	if (!envron)
	{
		return (-1);
	}
	for (i = 0; envron[i]; i++)
	{
		write(STDOUT_FILENO, envron[i], str_length(envron[i]));
		write(STDOUT_FILENO, &c, 1);
	}
	return (0);
}

/**
 * _shellsetenv - Changes or adds an environmental variable to the PATH.
 * @arg: An array of arguments passed to the shell.
 * @fnt: A double pointer to the beginning of args.
 * Return: 0 , -1 if an error occurs
 */
int _shellsetenv(char **arg, char **fnt)
{
	(void)fnt;
	char **_envar, **_newenv, *_newval;
	size_t s;
	int i;

	_envar = NULL;
	if (!arg[0] || !arg[1])
	{
		return (_crterr(arg, -1));
	}
	_newval = malloc(str_length(arg[0]) + 1 + str_length(arg[1]) + 1);
	if (!_newval)
	{
		return (_crterr(arg, -1));
	}
	stringcopy(_newval, arg[0]);
	stringconcat(_newval, "=");
	stringconcat(_newval, arg[1]);

	_envar = get_env(arg[0]);
	if (_envar)
	{
		free(*_envar);
		*_envar = _newval;
		return (0);
	}
	for (s = 0; envron[s]; s++)
		;
	_newenv = malloc(sizeof(char *) * (s + 2));
	if (!_newenv)
	{
		free(_newval);
		return (_crterr(arg, -1));
	}

	for (i = 0; envron[i]; i++)
	{
		_newenv[i] = envron[i];
	}
	free(envron);
	envron = _newenv;
	envron[i] = _newval;
	envron[i + 1] = NULL;

	return (0);
}

/**
 * _shellunsetenv - Deletes an environmental variable from the PATH.
 * @arg: An array of arguments passed to the shell.
 * @fnt: A double pointer to the beginning of args.
 * Return: 0, -1 in case of error
 */
int _shellunsetenv(char **arg, char **fnt)
{
	(void)fnt;
	char **envar, **_newenv;
	size_t s;
	int count, count2;

	if (!arg[0])
	{
		return (_crterr(arg, -1));
	}
	envar = get_env(arg[0]);
	if (!envar)
	{
		return (0);
	}

	for (s = 0; envron[s]; s++)
		;

	_newenv = malloc(sizeof(char *) * s);
	if (!_newenv)
	{
		return (_crterr(arg, -1));
	}
	for (count = 0, count2 = 0; envron[count]; count++)
	{
		if (*envar == envron[count])
		{
			free(*envar);
			continue;
		}
		_newenv[count2] = envron[count];
		count2++;
	}
	free(envron);

	envron = _newenv;
	envron[s - 1] = NULL;

	return (0);
}
