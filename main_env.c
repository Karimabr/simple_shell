#include "simple_shell.h"
/**
 * copy_environ - Creates a copy of the environment.
 * Return: a ppppointer to new copy, null if error occurs
 */
char **copy_environ(void)
{
	char **_newenv;
	char *names[] = {"PATH", "HOME", "USER", "SHELL", "TERM", NULL};
	int s = 0;
	int count = 0;
	char *value;

	while (names[s] != NULL)
		s++;

	_newenv = malloc(sizeof(char *) * (s + 1));
	if (!_newenv)
		return (NULL);

	while (names[count] != NULL)
	{
		value = get_env(names[count]);
		if (value == NULL)
			value = "";

		_newenv[count] = malloc(str_length(names[count]) + str_length(value) + 2);
		if (!_newenv[count])
		{
			for (count--; count >= 0; count--)
				free(_newenv[count]);
			free(_newenv);
			return (NULL);
		}
		stringcopy(_newenv[count], names[count]);
		stringconcat(_newenv[count], "=");
		stringconcat(_newenv[count], value);
		count++;
	}
	_newenv[count] = NULL;
	return (_newenv);
}
/**
 * _freeenviron - Frees the the environment copy.
 * Return: void returns nothing
 */
void _freeenviron(void)
{
	int count;

	for (count = 0; envron[count]; count++)
	{
		free(envron[count]);
	}
	free(envron);
}

/**
 * get_env - Gets an environmental variable from the PATH.
 * @variable: The name of the environmental variable to get.
 * Return: a pointer to the variable envron, null when error occurs
 */
char **get_env(const char *variable)
{
	int count;
	int length;

	length = str_length(variable);
	for (count = 0; envron[count]; count++)
	{
		if (strncompare(variable, envron[count], length) == 0)
		{
			return (&envron[count]);
		}
	}

	return (NULL);
}
/**
 * aliassetting - Will either set an existing alias 'name' with a new value,
 * @variable: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void aliassetting(char *variable, char *value)
{
	alias_n *current;
	int length, i, j;
	char *_newvalue;

	current = aliases;
	*value = '\0';
	value++;
	length = str_length(value) - stringspn(value, "'\"");
	_newvalue = (char)malloc(sizeof(char) * (length + 1));
	if (!_newvalue)
	{
		return;
	}
	for (i = 0, j = 0; value[i]; i++)
	{
		if (value[i] != '\'' && value[i] != '"')
		{
			_newvalue[j++] = value[i];
		}
	}
	_newvalue[j] = '\0';
	while (current)
	{
		if (strcompare(variable, current->name) == 0)
		{
			free(current->value);
			current->value = _newvalue;
			break;
		}
		current = current->next;
	}
	if (!current)
	{
		_addaliasfin(&aliases, variable, _newvalue);
	}
}
