#include "simple_shell.h"
/**
 * file_cmnds - a function to run the commands
 * @fpath: a Path to the file
 * @exert: Return value of the last executed command
 * Return: value of the command ran
 */
int file_cmnds(char *fpath, int *exert)
{
	ssize_t fd, _bfferrd;
	unsigned int strsize;
	char *str, **arg;
	char _buf[130];
	unsigned int _olds;
	ssize_t count;
	int _rt;
	char **fnt;

	strsize = 0;
	_olds = 121;
	count = 0;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
	{
		return (*exert);
	}
	str = malloc(sizeof(char) * _olds);

	if (!str)
	{
		return (-1);
	}
	do {
		_bfferrd = read(fd, _buf, 120);
		strsize += _bfferrd;
		if (_bfferrd == 0 && strsize == 0)
		{
			return (*exert);
		}
		_buf[_bfferrd] = '\0';

		str = _realloc_(str, _olds, strsize);
		stringconcat(str, _buf);
		_olds = strsize;

	} while (_bfferrd);

	while (str[count] == '\n')
	{
		count++;
		str[count] = ' ';
	}
	while (count < strsize)
	{
		count++;

		if (str[count] == '\n')
		{
			str[count] = ';';

			for (count += 1; count < strsize && str[count] == '\n'; count++)
			{
				str[count] = ' ';
			}
		}
	}

	_var_rep(&str, exert);

	_handline(&str, strsize);

	arg = _strtok_(str, " ");

	free(str);

	if (!arg)
	{
		return (0);
	}
	if (_checkonarg(arg) != 0)
	{
		*exert = 2;

		_freearg(arg, arg);

		return (*exert);
	}

	fnt = arg;

	while (arg[count])
	{
		count++;
		if (strncompare(arg[count], ";", 1) == 0)
		{
			free(arg[count]);
			arg[count] = NULL;
			_rt = _callarg(arg, fnt, exert);

			arg = &arg[count++];
			count = 0;
		}
	}

	_rt = _callarg(arg, fnt, exert);

	free(fnt);

	return (_rt);
}
