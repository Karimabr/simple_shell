#include "simple_shell.h"

/**
 * _numlength - Counts the digit length of a number.
 * @number: The number to measure.
 * Return: The digit length.
 */
int _numlength(int number)
{
	int length;

	length = 0;
	if (number == 0)
		return (1);

	if (number < 0)
	{
		length++;
		number /= 10;
	}
	while (number != 0)
	{
		length++;
		number /= 10;
	}
	return (length);
}

/**
 * _atoi - Converts an integer to a string.
 * @number: The integer.
 * Return: The converted string.
 */
char *_atoi(int number)
{
	int length;
	char *buf;

	length = _numlength(number);
	buf = malloc(sizeof(char) * (length + 1));
	if (!buf)
		return NULL;
	buf[length] = '\0';
	length--;

	int sign = number < 0;
	if (sign)
		number *= -1;

	while (number != 0)
	{
		int digit = number % 10;
		buf[length] = digit + '0';
		length--;
		number /= 10;
	}
	if (sign)
		buf[0] = '-';

	return buf;
}
/**
 * _crterr - Writes a custom error message to stderr.
 * @arg: An array of arguments.
 * @error: The error value.
 * Return: The error value.
 */
int _crterr(char **arg, int error)
{
	char *_msg;
	char *(*_err)(char **);

	if (error == -1)
		_err = _err_env(arg);
	else if (error == 1)
		_err = _err1(arg);
	else if (error == 2)
	{
		if (*(arg[0]) == 'e')
			_err = _errorexit(arg);
		else if (arg[0][0] == ';' || arg[0][0] == '&' || arg[0][0] == '|')
			_err = _errorsyn(arg);
		else
			_err = _errorcd(arg);
	}
	else if (error == 3)
		_err = err_3(arg);
	else if (error == 4)
		_err = err_4(arg);
	else
		return (error);

	_msg = (*_err)(arg);

	write(STDERR_FILENO, _msg, str_length(_msg));

	if (_msg)
		free(_msg);

	return (error);
}
