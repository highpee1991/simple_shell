#include "main.h"

/**
 * **strtow - divids strings into words. delim that are repeated is ignored
 * @str: string to input
 * @d: string delim
 * Return: return a pointer to array of strings, || NULL if fail
 */

char **strtow(char *str, char *d)
{
	int _ind, _ind2, _ind3, _mw, word_num = 0;
	char **_str_p;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (_ind = 0; str[_ind] != '\0'; _ind++)
		if (!_cus_delimeter_(str[_ind], d)
				&& (_cus_delimeter_(str[_ind + 1], d) || !str[_ind + 1]))
			word_num++;

	if (word_num == 0)
		return (NULL);
	_str_p = malloc((1 + word_num) * sizeof(char *));
	if (!_str_p)
		return (NULL);
	for (_ind = 0, _ind2 = 0; _ind2 < word_num; _ind2++)
	{
		while (_cus_delimeter_(str[_ind], d))
			_ind++;
		_ind3 = 0;
		while (!_cus_delimeter_(str[_ind + _ind3], d) && str[_ind + _ind3])
			_ind3++;
		_str_p[_ind2] = malloc((_ind3 + 1) * sizeof(char));
		if (!_str_p[_ind2])
		{
			for (_ind3 = 0; _ind3 < _ind2; _ind3++)
				free(_str_p[_ind3]);
			free(_str_p);
			return (NULL);
		}
		for (_mw = 0; _mw < _ind3; _mw++)
			_str_p[_ind2][_mw] = str[_ind++];
		_str_p[_ind2][_mw] = 0;
	}
	_str_p[_ind2] = NULL;
	return (_str_p);
}

/**
 * **strtow2 - divides string to words
 * @str: string to input
 * @d: delimeter
 * Return: returns a pointer to strings || NULL if fail
 */
char **strtow2(char *str, char d)
{
	int _ind, _ind2, _ind3, _mw, word_num = 0;
	char **_str_p;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (_ind = 0; str[_ind] != '\0'; _ind++)
		if ((str[_ind] != d && str[_ind + 1] == d) ||
		    (str[_ind] != d && !str[_ind + 1]) || str[_ind + 1] == d)
			word_num++;
	if (word_num == 0)
		return (NULL);
	_str_p = malloc((1 + word_num) * sizeof(char *));
	if (!_str_p)
		return (NULL);
	for (_ind = 0, _ind2 = 0; _ind2 < word_num; _ind2++)
	{
		while (str[_ind] == d && str[_ind] != d)
			_ind++;
		_ind3 = 0;
		while (str[_ind + _ind3] != d && str[_ind + _ind3] && str[_ind + _ind3] != d)
			_ind3++;
		_str_p[_ind2] = malloc((_ind3 + 1) * sizeof(char));
		if (!_str_p[_ind2])
		{
			for (_ind3 = 0; _ind3 < _ind2; _ind3++)
				free(_str_p[_ind3]);
			free(_str_p);
			return (NULL);
		}
		for (_mw = 0; _mw < _ind3; _mw++)
			_str_p[_ind2][_mw] = str[_ind++];
		_str_p[_ind2][_mw] = 0;
	}
	_str_p[_ind2] = NULL;
	return (_str_p);
}
