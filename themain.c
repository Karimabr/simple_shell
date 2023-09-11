#include "simple_shell.h"
/**
 * main - the main function
 * @ac: arguments count
 * @av: a pointer to strings
 * Return: value of the command
*/
int main (int ac, char **av)
{
	char *prmpt, *newstr;
	int a, b;
	int *exert;

	prmpt = "s ";
	newstr = "\n";
	a = 0;
	exert = &b;
	exert = 0;
	nm = av[0];
	aliases = NULL;

	signal(SIGINT, seg_fault);
	envron = copy_environ();
	if (ac != 1)
	{
		a = file_cmnds(av[1], exert);
		_freealiasfin(aliases);
		exit (*exert);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (a != EOF)
		{
			a = _handleargmnt(exert);
			_freealiasfin(aliases);
			exit(*exert);
		}
	}
	while(1)
	{
		write(STDOUT_FILENO, prmpt, 2);
		a = _handleargmnt(exert);
		while (a == EOF || a == -3)
		{
			_freealiasfin(aliases);
			return (*exert);
		}
	}
	_freeenviron();
	_freealiasfin(aliases);
	return (*exert);
}
