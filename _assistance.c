#include "simple_shell.h"

/**
 * _freearg - Frees up memory taken by args.
 * @arg: A null-terminated double pointer containing commands/arguments.
 * @fnt: A double pointer to the beginning of args.
 */
void _freearg(char **arg, char **fnt)
{
	size_t count;

	for (count = 0; arg[count] || arg[count + 1]; count++)
	{
		free(arg[count]);
	}
	free(fnt);
}

/**
 * _getpid_ - Gets the current process ID.
 * Return: The current process ID or NULL on failure.
 */
char *_getpid_(void)
{
	size_t count;
	char *buf;
	ssize_t fd;

	count = 0;
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		perror("Cant read fd");
		return (NULL);
	}
	buf = malloc(120);
	if (!buf)
	{
		close(fd);
		return (NULL);
	}
	read(fd, buf, 120);
	while (buf[count] != ' ')
	{
		count++;
	}
	buf[count] = '\0';

	close(fd);
	return (buf);
}

/**
 * _getenval_ - a function that Gets the value corresponding to a variable
 * @start: environmental variable to look for
 * @length: The length of the environmental variable to search for
 * Return: the value of the variable replacement, otherwise empty string
 */
char *_getenval_(char *start, int length)
{
	char **address;
	char *replce, *curr;
	char *variable;

	replce = NULL;
	variable = malloc(length + 1);
	if (!variable)
	{
		return (NULL);
	}
	variable[0] = '\0';

	strnconcat(variable, start, length);

	address = get_env(variable);
	free(variable);
	if (address)
	{
		curr = *address;

		while (*curr != '=')
		{
			curr++;
		}
		curr++;
		replce = malloc(str_length(curr) + 1);
		if (replce)
		{
			stringcopy(replce, curr);
		}
	}

	return (replce);
}

/**
 * _var_rep - Handles variable replacement.
 * @arg: A double pointer containing the command and arguments.
 * @exert: A pointer to the return value of the last executed command.
 * Return: void returns nothing
 */
void _var_rep(char **arg, int *exert)
{
	int count, j, length;
	char *changer, *prev_line, *newline;

	j = 0;
	changer = NULL;
	prev_line = NULL;
	prev_line = *arg;
	for (count = 0; prev_line[count]; count++)
	{
		if (prev_line[count] == '$' && prev_line[count + 1] && prev_line[j + 1] != ' ')
		{
			if (prev_line[count + 1] == '$')
			{
				changer = _getpid_();
				j = count + 2;
			}
			else if (prev_line[count + 1] == '?')
			{
				changer = _atoi(*exert);
				j = count + 2;
			}
			else if (prev_line[count + 1])
			{
				for (j = count + 1; prev_line[j] && prev_line[j] != '$' &&
						prev_line[j] != ' '; j++)
					;
				length = j - (count + 1);
				changer = _getenval_(&prev_line[count + 1], length);
			}
			newline = malloc(count + str_length(changer)
					  + str_length(&prev_line[j]) + 1);
			if (!arg)
			{
				return;
			}
			newline[0] = '\0';
			strnconcat(newline, prev_line, count);
			if (changer)
			{
				stringconcat(newline, changer);
				free(changer);
				changer = NULL;
			}
			stringconcat(newline, &prev_line[j]);

			free(prev_line);
			*arg = newline;
			prev_line = newline;
			count = -1;
		}
	}
}
