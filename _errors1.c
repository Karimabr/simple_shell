#include "simple_shell.h"
/**
 * _err_env - Creates an error message for shellby_env errors.
 * @arg: An array of arguments passed to the command.
 * Return: The error string.
 */
char *_err_env(char **arg)
{
	char *_err, *_hststr;
	int length;

	_hststr = _atoi(hst);
	if (!_hststr)
	{
		return (NULL);
	}
	arg--;
	length = str_length(nm) + str_length(_hststr) + str_length(arg[0]) + 45;
	_err = malloc(sizeof(char) * (length + 1));
	if (!_err)
	{
		free(_hststr);
		return (NULL);
	}

	stringcopy(_err, nm);
	stringconcat(_err, ": ");
	stringconcat(_err, _hststr);
	stringconcat(_err, ": ");
	stringconcat(_err, arg[0]);
	stringconcat(_err, ": Unable to add/remove from environment\n");

	free(_hststr);
	return (_err);
}

/**
 * _err1 - Creates an error message for shellby_alias errors.
 * @arg: An array of arguments passed to the command.
 * Return: The error string.
 */
char *_err1(char **arg)
{
	char *_err;
	int length;

	length = str_length(nm) + str_length(arg[0]) + 13;
	_err = malloc(sizeof(char) * (length + 1));
	if (!_err)
	{
		return (NULL);
	}
	stringcopy(_err, "alias: ");
	stringconcat(_err, arg[0]);
	stringconcat(_err, " not found\n");

	return (_err);
}

/**
 * _errorexit - Creates an error message for shellby_exit errors.
 * @arg: An array of arguments passed to the command.
 * Return: The error string.
 */
char *_errorexit(char **arg)
{
	char *_err, *_hst_str;
	int length;

	_hst_str = _atoi(hst);
	if (!_hst_str)
	{
		return (NULL);
	}
	length = str_length(nm) + str_length(_hst_str) + str_length(arg[0]) + 27;
	_err = malloc(sizeof(char) * (length + 1));
	if (!_err)
	{
		free(_hst_str);
		return (NULL);
	}

	stringcopy(_err, nm);
	stringconcat(_err, ": ");
	stringconcat(_err, _hst_str);
	stringconcat(_err, "exit: Illegal number: ");
	stringconcat(_err, arg[0]);
	stringconcat(_err, "\n");

	free(_hst_str);
	return (_err);
}

/**
 * _errorcd - Creates an error message for shellby_cd errors.
 * @arg: An array of arguments passed to the command.
 * Return: The error string.
 */
char *_errorcd(char **arg)
{
	char *_err, *hststr;
	int length;

	hststr = _atoi(hst);
	if (!hststr)
	{
		return (NULL);
	}
	if (arg[0][0] == '-')
	{
		arg[0][2] = '\0';
	}
	length = str_length(nm) + str_length(hststr) + str_length(arg[0]) + 24;
	_err = malloc(sizeof(char) * (length + 1));
	if (!_err)
	{
		free(hststr);
		return (NULL);
	}

	stringcopy(_err, nm);
	stringconcat(_err, ": ");
	stringconcat(_err, hststr);
	if (arg[0][0] == '-')
	{
		stringconcat(_err, "cd: option not allowed");
	}
	else
	{
		stringconcat(_err, "cd: can't cd to ");
	}
	stringconcat(_err, arg[0]);
	stringconcat(_err, "\n");

	free(hststr);
	return (_err);
}

/**
 * _errorsyn - Creates an error message for syntax errors.
 * @arg: An array of arguments passed to the command.
 * Return: The error string.
 */
char *_errorsyn(char **arg)
{
	char *_err, *_hist;
	int length;

	_hist = NULL;
	_hist = _atoi(&_hist);
	if (!_hist)
	{
		return (NULL);
	}
	length = str_length(nm) + str_length(_hist) + str_length(arg[0]) + 33;
	_err = malloc(sizeof(char) * (length + 1));
	if (!_err)
	{
		free(_hist);
		return (NULL);
	}

	stringcopy(_err, nm);
	stringconcat(_err, ": ");
	stringconcat(_err, _hist);
	stringconcat(_err, "syntax error: \"");
	stringconcat(_err, arg[0]);
	stringconcat(_err, "\" unexpected error\n");

	free(_hist);
	return (_err);
}
