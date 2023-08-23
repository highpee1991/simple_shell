#include "main.h"

/**
 **_memset - adds memory with const byte
 *@str: reference to area of the memory
 *@bf: byte to add *str
 *@_nums: size of byte(s) to be included
 *Return: returns a pointer string to the memory address str
 */
char *_memset(char *str, char bf, unsigned int _nums)
{
	unsigned int _ind;

	for (_ind = 0; _ind < _nums; _ind++)
		str[_ind] = bf;
	return (str);
}

/**
 * _ffree_mode - releases strings
 * @ptr_ptr: the string of other strings
 */
void _ffree_mode(char **ptr_ptr)
{
	char **a = ptr_ptr;

	if (!ptr_ptr)
		return;
	while (*ptr_ptr)
		free(*ptr_ptr++);
	free(a);
}

/**
 * _realloc - allocates a block of memory again
 * @ptr: reference to other allocated block
 * @old_sz: the size of prev block in byte(s)
 * @sz_new: size of latest block in byte
 * Return: reference to block
 */
void *_realloc(void *ptr, unsigned int old_sz, unsigned int sz_new)
{
	char *p;

	if (!ptr)
		return (malloc(sz_new));
	if (!sz_new)
		return (free(ptr), NULL);
	if (sz_new == old_sz)
		return (ptr);

	p = malloc(sz_new);
	if (!p)
		return (NULL);

	old_sz = old_sz < sz_new ? old_sz : sz_new;
	while (old_sz--)
		p[old_sz] = ((char *)ptr)[old_sz];
	free(ptr);
	return (p);
}
