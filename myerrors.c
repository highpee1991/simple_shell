#include "main.h"

/**
 *_errors_puts_ - string of input display
 * @str: string to show
 * Return: Null
 */
void _errors_puts_(char *str)
{
	int _ind = 0;

	if (!str)
		return;
	while (str[_ind] != '\0')
	{
		_error_putchar_(str[_ind]);
		_ind++;
	}
}

/**
 * _error_putchar_ - texts char c
 * @c: char to be displayed
 * Return: 1 if it's a success, if not -1 is returned
 */
int _error_putchar_(char c)
{
	static int _ind;
	static char buf[_BUFFER_SIZE_WRITER];

	if (c == _FLUSH_BUFFER_SIZE || _ind >= _BUFFER_SIZE_WRITER)
	{
		write(2, buf, _ind);
		_ind = 0;
	}
	if (c != _FLUSH_BUFFER_SIZE)
		buf[_ind++] = c;
	return (1);
}

/**
 * _fdsputs - char c to be texted
 * @c: char to be displayed
 * @fd: file to puts into
 *
 * Return: 1 if it's success, if not -1.
 */
int _fdsputs(char c, int fd)
{
	static int _ind;
	static char buf[_BUFFER_SIZE_WRITER];

	if (c == _FLUSH_BUFFER_SIZE || _ind >= _BUFFER_SIZE_WRITER)
	{
		write(fd, buf, _ind);
		_ind = 0;
	}
	if (c != _FLUSH_BUFFER_SIZE)
		buf[_ind++] = c;
	return (1);
}

/**
 *_fds_putss_ - string input to be formated
 * @str: the displayd string
 * @fd: descriptor to display into
 * Return: characters of numb put
 */
int _fds_putss_(char *str, int fd)
{
	int _ind = 0;

	if (!str)
		return (0);
	while (*str)
	{
		_ind += _fdsputs(*str++, fd);
	}
	return (_ind);
}

