#include "simple_shell.h"

/**
 * _realloc_ - Reallocates a memory block using malloc and free.
 * @p: A pointer to the memory previously allocated.
 * @old_s: The size in bytes of the allocated space for ptr.
 * @size_new: The size in bytes for the new memory block.
 * Return: a pointer to the reallocated memory
 */
void *_realloc_(void *p, unsigned int old_s, unsigned int size_new)
{
	char *cp_ptr, *fil;
	unsigned int count;
	void *memory;

	if (size_new == old_s)
	{
		return (p);
	}
	if (p == NULL)
	{
		memory = malloc(size_new);
		if (memory == NULL)
		{
			return (NULL);
		}
		return (memory);
	}

	if (size_new == 0 && p != NULL)
	{
		free(p);
		return (NULL);
	}

	cp_ptr = p;
	memory = malloc(sizeof(*cp_ptr) * size_new);
	if (memory == NULL)
	{
		free(p);
		return (NULL);
	}

	fil = memory;

	for (count = 0; count < old_s && count < size_new; count++)
	{
		fil[count] = *cp_ptr++;
	}
	free(p);
	return (memory);
}

/**
 * lnptr_assignment - Reassigns the lineptr variable for _getline.
 * @linep: A buffer to store an input string.
 * @num: The size of lineptr.
 * @buf: The string to assign to lineptr.
 * @size: The size of buffer.
 */
void lnptr_assignment(char **linep, size_t *num, char *buf, size_t size)
{
	if (*linep == NULL)
	{
		if (size > 120)
		{
			*num = size;
		}
		else
		{
			*num = 120;
		}
		*linep = buf;
	}
	else if (*num < size)
	{
		if (size > 120)
		{
			*num = size;
		}
		else
		{
			*num = 120;
		}
		*linep = buf;
	}
	else
	{
		stringcopy(*linep, buf);
		free(buf);
	}
}

/**
 * _getline - Reads input from a stream.
 * @lnpointr: A buffer to store the input.
 * @num: The size of lnpointr.
 * @strm: file to read from.
 * Return: returns number of bytes read.
 */
ssize_t _getline(char **lnpointr, size_t *num, FILE *strm)
{
	ssize_t _rt;
	char s, *buf;
	static ssize_t i;
	int b;

	s = 'x';
	i = 0;
	if (i == 0)
	{
		fflush(strm);
	}
	else
	{
		return (-1);
	}

	buf = malloc(sizeof(char) * 120);
	if (!buf)
	{
		return (-1);
	}
	while (s != '\n')
	{
		b = read(STDIN_FILENO, &s, 1);
		if (b == -1 || (b == 0 && i == 0))
		{
			free(buf);
			return (-1);
		}
		if (b == 0 && i != 0)
		{
			i++;
			break;
		}

		if (i >= 120)
		{
			buf = _realloc_(buf, i, i + 1);
		}
		buf[i] = s;
		i++;
	}

	buf[i] = '\0';

	lnptr_assignment(lnpointr, num, buf, i);
	_rt = i;
	if (b != 0)
	{
		i = 0;
	}
	return (_rt);
}
