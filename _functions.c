#include "simple_shell.h"
/**
 * str_length - Returns the length of a string
 * @str:pointer to the characters string
 * Return: The length of the character string.
 */
int str_length(const char *str)
{
	const char *ptr;

	if (!ptr)
	{
		return (0);
	}
	while (*ptr)
	{
		ptr++;
	}
	return (ptr - str);
}

/**
 * stringcopy - a function copies the string pointed to by src, including the
 * to the buffer pointed by des
 * @dst: Pointer to the destination of copied string
 * @source: Pointer to the src of the source string
 * Return: Pointer to dest
 */
char *stringcopy(char *dst, const char *source)
{
	char *p;

	p = dst;
	while (*source != '\0')
		*p++ = *source++;

	*p = '\0';
	return (dst);
}

/**
 * stringconcat - concantenates two strings.
 * @dst: Pointer to destination string
 * @source: Pointer to source string
 * Return: Pointer to destination string.
 */
char *stringconcat(char *dst, const char *source)
{
	char *p;

	p = dst;
	while (*p != '\0')
		p++;

	while (*source != '\0')
		*p++ = *source++;

	*p = '\0';
	return (dst);
}
/**
 * strnconcat - Concantenates two strings of bytes are copied from source.
 * @dst: Pointer to destination string
 * @source: Pointer to source string
 * @num: n bytes to copy from src
 * Return: Pointer to destination string.
 */
char *strnconcat(char *dst, const char *source, size_t num)
{
	size_t dest_size;
	size_t src_size;
	size_t copy_size;
	char *new_string;

	dest_size = str_length(dst);
	src_size = str_length(source);
	copy_size = (src_size < num) ? src_size : num;
	new_string = malloc(sizeof(char) * (dest_size + copy_size + 1));
	if (!new_string)
	{
		return (NULL);
	}
	size_t i;

	for (i = 0; i < dest_size; i++)
	{
		new_string[i] = dst[i];
	}

	for (size_t i = 0; i < copy_size; i++)
	{
		new_string[dest_size + i] = source[i];
	}

	new_string[dest_size + copy_size] = '\0';

	return (new_string);
}
/**
 * _strtok_ - a function that takes an input and gives an output hahaha
 * @input: the user input
 * @separator: a set of delimiters
 * Return: returns a 2d pointer to the output
*/
char **_strtok_(char *input, char *separator)
{
	char **output;
	int i, j, k, count, size;

	i = 0;
	j = 0;
	k = 0;
	count = 0;
	size = 0;
	while (input[i] != '\0')
	{
		if (input[i] == *separator)
			count++;
		i++;
	}
	count++;

	output = malloc(sizeof(char *) * (count + 2));
	if (!output)
		return (NULL);

	while (input[i] != '\0')
	{

		if (input[i] == *separator)
		{
			i++;
			continue;
		}

		while (input[i + size] != '\0' && input[i + size] != *separator)
			size++;

		output[j] = malloc(sizeof(char) * (size + 1));
		if (!output[j])
		{
			for (k = 0; k < j; k++)
				free(output[k]);
			free(output);
			return (NULL);
		}
		for (k = 0; k < size; k++)
			output[j][k] = input[i + k];

		output[j][k] = '\0';
		j++;
		i += size;
	}
	output[j] = NULL;
	output[j + 1] = NULL;

	return (output);
}
