#include "simple_shell.h"

/**
 * _getlocal - a function to locate commands in a PATH.
 * @cmd: command to be located
 * Return: full path name of the command
 */
char *_getlocal(char *cmd)
{
	char **pt, *current;
	ls_t *drc;
	ls_t *hd;
	struct stat start;

	pt = get_env("PATH");
	if (!pt || !(*pt))
	{
		return (NULL);
	}
	drc = _path_drc(*pt + 5);
	hd = drc;
	while (drc)
	{
		current = malloc(str_length(drc->drc) + str_length(cmd) + 2);
		if (!current)
		{
			return (NULL);
		}

		stringcopy(current, drc->drc);
		stringconcat(current, "/");
		stringconcat(current, cmd);

		if (stat(current, &start) == 0)
		{
			_freethelist(hd);
			return (current);
		}

		drc = drc->next;
		free(current);
	}

	_freethelist(hd);
	return (NULL);
}

/**
 * _pathfilled - a function that copies path but also replaces it
 * @pt: a char pointer
 * Return: a copy of the path
 */
char *_pathfilled(char *pt)
{
	int count;
	char *cp_t;
	char *pd;
	int _len;

	pd = *(get_env("PWD")) + 4;
	for (count = 0; pt[count]; count++)
	{
		if (pt[count] == ':')
		{
			if (pt[count + 1] == ':' || count == 0 || pt[count + 1] == '\0')
			{
				_len += str_length(pd) + 1;
			}
			else
			{
				_len++;
			}
		}
		else
		{
			_len++;
		}
	}

	cp_t = malloc(sizeof(char) * (_len + 1));
	if (!cp_t)
	{
		return (NULL);
	}
	cp_t[0] = '\0';
	for (count = 0; pt[count]; count++)
	{
		if (pt[count] == ':')
		{
			if (count == 0)
			{
				stringconcat(cp_t, pd);
				stringconcat(cp_t, ":");
			}
			else if (pt[count + 1] == ':' || pt[count + 1] == '\0')
			{
				stringconcat(cp_t, ":");
				stringconcat(cp_t, pd);
			}
			else
			{
				stringconcat(cp_t, ":");
			}
		}
		else
		{
			strnconcat(cp_t, &pt[count], 1);
		}
	}
	return (cp_t);
}

/**
 * _path_drc - a function to get the list of directories
 * @p: a pointer to the path
 * Return: returns a pointer to the list
 */
ls_t *_path_drc(char *p)
{
	int count;
	char **drc;
	ls_t *hd;
	char *cp_t;

	hd = NULL;
	cp_t = _pathfilled(p);

	if (!cp_t)
	{
		return (NULL);
	}

	drc = _strtok_(cp_t, ":");

	free(cp_t);
	if (!drc)
	{
		return (NULL);
	}
	for (count = 0; drc[count]; count++)
	{
		if (_addnodefin(&hd, drc[count]) == NULL)
		{
			_freethelist(hd);

			free(drc);

			return (NULL);
		}
	}

	free(drc);

	return (hd);
}
