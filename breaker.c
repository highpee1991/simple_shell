#include "main.h"

/**
 * **tokenizeString - divids strings into words. delim that are repeated is ignored
 * @_wrdstr: string to input
 * @_dig_str: string delim
 * Return: return a pointer to array of strings, || NULL if fail
 */

char **tokenizeString(char *_wrdstr, char *_dig_str)
{
	int _ind, _ind2, _ind3, _mw, word_num = 0;
	char **_str_p;

	if (_wrdstr == NULL || _wrdstr[0] == 0)
		return (NULL);
	if (!_dig_str)
		_dig_str = " ";
	for (_ind = 0; _wrdstr[_ind] != '\0'; _ind++)
		if (!_cus_delimeter_(_wrdstr[_ind], _dig_str)
				&& (_cus_delimeter_(_wrdstr[_ind + 1], _dig_str) || !_wrdstr[_ind + 1]))
			word_num++;

	if (word_num == 0)
		return (NULL);
	_str_p = malloc((1 + word_num) * sizeof(char *));
	if (!_str_p)
		return (NULL);
	for (_ind = 0, _ind2 = 0; _ind2 < word_num; _ind2++)
	{
		while (_cus_delimeter_(_wrdstr[_ind], _dig_str))
			_ind++;
		_ind3 = 0;
		while (!_cus_delimeter_(_wrdstr[_ind + _ind3], _dig_str) && _wrdstr[_ind + _ind3])
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
			_str_p[_ind2][_mw] = _wrdstr[_ind++];
		_str_p[_ind2][_mw] = 0;
	}
	_str_p[_ind2] = NULL;
	return (_str_p);
}

/**
 * **_segstring - divides string to words
 * @_wrdstr: string to input
 * @_dig_str: delimeter
 * Return: returns a pointer to strings || NULL if fail
 */
char **_segstring(char *_wrdstr, char _dig_str)
{
	int _ind, _ind2, _ind3, _mw, word_num = 0;
	char **_str_p;

	if (_wrdstr == NULL || _wrdstr[0] == 0)
		return (NULL);
	for (_ind = 0; _wrdstr[_ind] != '\0'; _ind++)
		if ((_wrdstr[_ind] != _dig_str && _wrdstr[_ind + 1] == _dig_str) ||
		    (_wrdstr[_ind] != _dig_str && !_wrdstr[_ind + 1]) || _wrdstr[_ind + 1] == _dig_str)
			word_num++;
	if (word_num == 0)
		return (NULL);
	_str_p = malloc((1 + word_num) * sizeof(char *));
	if (!_str_p)
		return (NULL);
	for (_ind = 0, _ind2 = 0; _ind2 < word_num; _ind2++)
	{
		while (_wrdstr[_ind] == _dig_str && _wrdstr[_ind] != _dig_str)
			_ind++;
		_ind3 = 0;
		while (_wrdstr[_ind + _ind3] != _dig_str && _wrdstr[_ind + _ind3] && _wrdstr[_ind + _ind3] != _dig_str)
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
			_str_p[_ind2][_mw] = _wrdstr[_ind++];
		_str_p[_ind2][_mw] = 0;
	}
	_str_p[_ind2] = NULL;
	return (_str_p);
}
