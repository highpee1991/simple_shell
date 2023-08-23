#include "main.h"

/**
 * _error_attoi - turns string to int
 * @_str_kp: string to turn
 * Return: if string is null return 0, else -1
 */
int _error_attoi(char *_str_kp)
{
	int _ind = 0;
	unsigned long int res = 0;

	if (*_str_kp == '+')
		_str_kp++;
	for (_ind = 0;  _str_kp[_ind] != '\0'; _ind++)
	{
		if (_str_kp[_ind] >= '0' && _str_kp[_ind] <= '9')
		{
			res *= 10;
			res += (_str_kp[_ind] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * _error_printer_ - display error
 * @info: info structure
 * @estr: error lists of the string
 * Return: if string is null return (0), else -1
 */
void _error_printer_(_info_str_t *info, char *estr)
{
	_errors_puts_(info->_file_plate);
	_errors_puts_(": ");
	print_d(info->_line_tally, STDERR_FILENO);
	_errors_puts_(": ");
	_errors_puts_(info->_argu_variable[0]);
	_errors_puts_(": ");
	_errors_puts_(estr);
}

/**
 * print_d - an integer number to other
 * @input: input to be taken
 * @fd: file to puts into
 * Return: chars nums should be displayed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int _ind, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _error_putchar_;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (_ind = 1000000000; _ind > 1; _ind /= 10)
	{
		if (_abs_ / _ind)
		{
			__putchar('0' + current / _ind);
			count++;
		}
		current %= _ind;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * _num_converter_ - a copy
 * @_digit: digits
 * @base: the base of the integer
 * @flags: for arguments
 * Return: return to be a string
 */
char *_num_converter_(long int _digit, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char fl = 0;
	char *ptr;
	unsigned long n = _digit;

	if (!(flags & _UNSIGNED_CONVERTER) && _digit < 0)
	{
		n = -_digit;
		fl = '-';

	}
	arr = flags & _LOWERCASE_CONVERTER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (fl)
		*--ptr = fl;
	return (ptr);
}

/**
 * _connent_remover_ - first example to replace another
 * @buf: string to change
 * Return: (0) on success;
 */
void _connent_remover_(char *buf)
{
	int _ind;

	for (_ind = 0; buf[_ind] != '\0'; _ind++)
		if (buf[_ind] == '#' && (!_ind || buf[_ind - 1] == ' '))
		{
			buf[_ind] = '\0';
			break;
		}
}
