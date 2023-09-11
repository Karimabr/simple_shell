#include "simple_shell.h"

/**
 * err_3 - Creates an error message for permission denied failures.
 * @arg: An array of arguments passed to the command.
 * Return: The error string.
 */
char *err_3(char **arg)
{
	char *_err, *hst_;
	int length;

	hst_ = _atoi(hst);
	if (!hst_)
	{
		return (NULL);
	}
	length = str_length(nm) + str_length(hst_) + str_length(arg[0]) + 24;
	_err = malloc(sizeof(char) * (length + 1));
	if (!_err)
	{
		free(hst_);
		return (NULL);
	}

	stringcopy(_err, nm);
	stringconcat(_err, ": ");
	stringconcat(_err, hst_);
	stringconcat(_err, ": ");
	stringconcat(_err, arg[0]);
	stringconcat(_err, "Permission denied\n");

	free(hst_);
	return (_err);
}

/**
 * err_4 - Creates an error message for command not found failures.
 * @arg: An array of arguments passed to the command.
 * Return: The error string.
 */
char *err_4(char **arg)
{
	char *_err, *hist;
	int length;

	hist = _atoi(hist);
	if (!hist)
	{
		return (NULL);
	}
	length = str_length(nm) + str_length(hist) + str_length(arg[0]) + 16;
	_err = malloc(sizeof(char) * (length + 1));
	if (!_err)
	{
		free(hist);
		return (NULL);
	}

	stringcopy(_err, nm);
	stringconcat(_err, ": ");
	stringconcat(_err, hist);
	stringconcat(_err, ": ");
	stringconcat(_err, arg[0]);
	stringconcat(_err, ": not found\n");

	free(hist);
	return (_err);
}
