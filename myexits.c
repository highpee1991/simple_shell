#include "main.h"

/**
 **_strncpy - makes a copy of a _wrdstr
 *@dest: where the string is going
 *@src: where the string comes from
 *@_dg_kper: numbers of chars to make a copy of
 *Return: return the connected strings
 */
char *_strncpy(char *dest, char *src, int _dg_kper)
{
	int _ind, _ind2;
	char *_str_li = dest;

	_ind = 0;
	while (src[_ind] != '\0' && _ind < _dg_kper - 1)
	{
		dest[_ind] = src[_ind];
		_ind++;
	}
	if (_ind < _dg_kper)
	{
		_ind2 = _ind;
		while (_ind2 < _dg_kper)
		{
			dest[_ind2] = '\0';
			_ind2++;
		}
	}
	return (_str_li);
}

/**
 **_strncat - connects 2 strings together
 *@dest: string one
 *@src: string two
 *@_dg_kper: number of byte(s) to use
 *Return: strings connected
 */
char *_strncat(char *dest, char *src, int _dg_kper)
{
	int _ind, _ind2;
	char *_str_li = dest;

	_ind = 0;
	_ind2 = 0;
	while (dest[_ind] != '\0')
		_ind++;
	while (src[_ind2] != '\0' && _ind2 < _dg_kper)
	{
		dest[_ind] = src[_ind2];
		_ind++;
		_ind2++;
	}
	if (_ind2 < _dg_kper)
		dest[_ind] = '\0';
	return (_str_li);
}

/**
 **_strchr - finds where a char is located in _wrdstr
 *@_str_li: _wrdstr to use
 *@c: char to check
 *Return: returns _str_li which is pointer to a memory location
 */
char *_strchr(char *_str_li, char c)
{
	do {
		if (*_str_li == c)
			return (_str_li);
	} while (*_str_li++ != '\0');

	return (NULL);
}
