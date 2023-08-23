#include "main.h"

/**
 * _cpy_string_mode - duplicates the string
 * @_sptor: going to
 * @_sc: coming from
 * Return: reference to destination
 */
char *_cpy_string_mode(char *_sptor, char *_sc)
{
	int _ind = 0;

	if (_sptor == _sc || _sc == 0)
		return (_sptor);
	while (_sc[_ind])
	{
		_sptor[_ind] = _sc[_ind];
		_ind++;
	}
	_sptor[_ind] = 0;
	return (_sptor);
}

/**
 * _string_round_up_mde - copies string
 * @_strin: string to copy
 * Return: reference to the copied string
 */
char *_string_round_up_mde(const char *_strin)
{
	int _len = 0;
	char *ret;

	if (_strin == NULL)
		return (NULL);
	while (*_strin++)
		_len++;
	ret = malloc(sizeof(char) * (_len + 1));
	if (!ret)
		return (NULL);
	for (_len++; _len--;)
		ret[_len] = *--_strin;
	return (ret);
}

/**
 *_puts - displays string input
 *@_strin: the string to be printed
 * Return: Null
 */
void _puts(char *_strin)
{
	int _ind = 0;

	if (!_strin)
		return;
	while (_strin[_ind] != '\0')
	{
		_putchar(_strin[_ind]);
		_ind++;
	}
}

/**
 * _putchar - texts the char c to standard output
 * @c: char to display
 * Return: return 1 if succeed. if not -1
 */
int _putchar(char c)
{
	static int _ind;
	static char buf[_BUFFER_SIZE_WRITER];

	if (c == _FLUSH_BUFFER_SIZE || _ind >= _BUFFER_SIZE_WRITER)
	{
		write(1, buf, _ind);
		_ind = 0;
	}
	if (c != _FLUSH_BUFFER_SIZE)
		buf[_ind++] = c;
	return (1);
}
