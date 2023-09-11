#include "simple_shell.h"
/**
 * _shellalias - Builtin command that either prints all aliases,
 * @arg: An array of arguments.
 * @fnt: A double pointer to the beginning of args.
 * Return: If an error occurs - -1. Otherwise - 0.
 */
int _shellalias(char **arg, char **fnt)
{
	(void)fnt;
	alias_n *curr;
	int i, rt;
	char *val;

	curr = aliases;
	rt = 0;
	if (!arg[0])
	{
		while (curr)
		{
			aliasprinted(curr);
			curr = curr->next;
		}
		return (rt);
	}
	for (i = 0; arg[i]; i++)
	{
		curr = aliases;
		val = stringchr(arg[i], '=');
		if (!val)
		{
			while (curr)
			{
				if (strcompare(arg[i], curr->name) == 0)
				{
					print_alias(curr);
					break;
				}
				curr = curr->next;
			}
			if (!curr)
			{
				rt = create_error(arg + i, 1);
			}
		}
		else
		{
			aliassetting(arg[i], val);
		}
	}
	return (rt);
}
/**
 * aliasprinted - Prints the alias in the format name='value'.
 * @als: Pointer to an alias.
 */
void aliasprinted(alias_n *als)
{
	char *als_string;
	int length;

	length = str_length(als->name) + str_length(als->value) + 4;
	als_string = malloc(sizeof(char) * (length + 1));
	if (!als_string)
	{
		return;
	}
	stringcopy(als_string, als->name);
	stringconcat(als_string, "='");
	stringconcat(als_string, als->value);
	stringconcat(als_string, "'\n");
	write(STDOUT_FILENO, als_string, length);
	free(als_string);
}
/**
 * _switchaliases - Goes through the arguments and replace any matching alias
 * @arg: pointer to the arguments.
 * Return: pointer to the arguments.
 */
char **_switchaliases(char **arg)
{
	alias_n *curr;
	int i;
	char *_newvalue;

	if (strcompare(arg[0], "alias") == 0)
	{
		return (arg);
	}
	for (i = 0; arg[i]; i++)
	{
		curr = aliases;
		while (curr)
		{
			if (strcompare(arg[i], curr->name) == 0)
			{
				_newvalue = malloc(sizeof(char) * (str_length(curr->value) + 1));
				if (!_newvalue)
				{
					_freearg(arg, arg);
					return (NULL);
				}
				stringcopy(_newvalue, curr->value);
				free(arg[i]);
				arg[i] = _newvalue;
				i--;
				break;
			}
			curr = curr->next;
		}
	}

	return (arg);
}
