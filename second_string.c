#include "main.h"

/**
 * _len_string_mode - the length of string will be returned
 * @_str: string length to look for
 * Return: length of the string int
 */
int _len_string_mode(char *_str)
{
	int _ind = 0;

	if (!_str)
		return (0);

	while (*_str++)
		_ind++;
	return (_ind);
}

/**
 * _string_cmp_mode - compares two strangs.
 * @_str1: _wrdstr one
 * @_str3: _wrdstr two
 * Return: return negative if _str1 is less than _str3
 * return positive if _str1 is greater than _str3
 * return zero if _str1 is equal to _str3
 */
int _string_cmp_mode(char *_str1, char *_str3)
{
	while (*_str1 && *_str3)
	{
		if (*_str1 != *_str3)
			return (*_str1 - *_str3);
		_str1++;
		_str3++;
	}
	if (*_str1 == *_str3)
		return (0);
	else
		return (*_str1 < *_str3 ? -1 : 1);
}

/**
 * _starter_mode_ - looks maybe _nedl begins with _heap_stack or not
 * @_heap_stack: the _wrdstr to look for
 * @_nedl: looks for substr
 * Return: the location of the followed character of _heap_stack || NULL
 */
char *_starter_mode_(const char *_heap_stack, const char *_nedl)
{
	while (*_nedl)
		if (*_nedl++ != *_heap_stack++)
			return (NULL);
	return ((char *)_heap_stack);
}

/**
 * _cat_string_mode - joins strings
 * @dc: the destination buffer
 * @sc: the source buffer
 * Return: reference to bufer destination
 */
char *_cat_string_mode(char *dc, char *sc)
{
	char *disp = dc;

	while (*dc)
		dc++;
	while (*sc)
		*dc++ = *sc++;
	*dc = *sc;
	return (disp);
}
