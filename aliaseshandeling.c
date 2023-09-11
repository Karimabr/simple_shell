#include "simple_shell.h"

/**
 * _addaliasfin - Adds a node to the end of a alias_n linked list
 * @hd: pointer to the head of the ls_t list
 * @nm: The name of the new alias to be added
 * @val: value of the new alias to be added
 * Return: pointer to the new allocated node
 */
alias_n *_addaliasfin(alias_n **hd, char *nm, char *val)
{
	alias_n *node;
	alias_n *fin;

	node = malloc(sizeof(alias_n));
	if (!node)
	{
		return (NULL);
	}
	node->next = NULL;

	node->name = malloc(sizeof(char) * (str_length(nm) + 1));
	if (!node->name)
	{
		free(node);
		return (NULL);
	}

	node->value = val;

	stringcopy(node->name, nm);
	if (*hd)
	{
		fin = *hd;
		while (fin->next != NULL)
		{
			fin = fin->next;
		}

		fin->next = node;
	}
	else
	{
		*hd = node;
	}

	return (node);
}

/**
 * _addnodefin - Adds a node to the end of a ls_t linked list
 * @hd: A pointer to the head of the ls_t list
 * @drc: The directory path for the new node to contain
 * Return: returns a pointer to newly allocated node
 */
ls_t *_addnodefin(ls_t **hd, char *drc)
{
	ls_t *_node = malloc(sizeof(ls_t));
	ls_t *fin;

	_node = malloc(sizeof(ls_t));
	if (!_node)
	{
		return (NULL);
	}
	_node->drc = drc;
	_node->next = NULL;
	if (*hd)
	{
		fin = *hd;

		while (fin->next != NULL)
		{
			fin = fin->next;
		}

		fin->next = _node;
	}
	else
	{
		*hd = _node;
	}

	return (_node);
}

/**
 * _freealiasfin - Frees a alias_n linked list
 * @hd: THe head of the alias_n list
 * Return: void returns nothing
 */
void _freealiasfin(alias_n *hd)
{
	alias_n *rt;

	while (hd)
	{
		rt = hd->next;
		free(hd->name);
		free(hd->value);
		free(hd);
		hd = rt;
	}
}

/**
 * _freethelist - Frees a ls_t linked list
 * @hd: The head of the ls_t list
 * Return: void returns nothing
 */
void _freethelist(ls_t *hd)
{
	ls_t *apres;

	while (hd)
	{
		apres = hd->next;

		free(hd->drc);
		free(hd);

		hd = apres;
	}
}
