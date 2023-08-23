#include "main.h"

/**
 * _finteractive_mode - if shell is _finteractive_mode mode then return true
 * @inform: address of struct
 *
 * Return: if _finteractive_mode mode retun 1, if not return 0
 */
int _finteractive_mode(_info_str_t *inform)
{
	return (isatty(STDIN_FILENO) && inform->readfd <= 2);
}

/**
 * _cus_delimeter_ - looks if character is a _delimeter or not
 * @string_line: char to check
 * @_delimeter: string of the _delimeter
 * Return: return 1 if it's true, if not 0
 */
int _cus_delimeter_(char string_line, char *_delimeter)
{
	while (*_delimeter)
		if (*_delimeter++ == string_line)
			return (1);
	return (0);
}

/**
 *_isalpha - alphabetic char to  check
 *@jdb_f: char to input if any
 *Return: 1 to return if string_line is alphabetic, if not 0
 */

int _isalpha(int jdb_f)
{
	if ((jdb_f >= 'a' && jdb_f <= 'z') || (jdb_f >= 'A' && jdb_f <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - an integer to be converted into a string
 *@str_mode: converted string
 *Return: return 0 if no numbers in string, if not return converted numbers
 */

int _atoi(char *str_mode)
{
	int num_decl, flag_holder = 1, flag = 0, display_ele;
	unsigned int res = 0;

	for (num_decl = 0;  str_mode[num_decl] != '\0' && flag != 2; num_decl++)
	{
		if (str_mode[num_decl] == '-')
			flag_holder *= -1;

		if (str_mode[num_decl] >= '0' && str_mode[num_decl] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (str_mode[num_decl] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (flag_holder == -1)
		display_ele = -res;
	else
		display_ele = res;

	return (display_ele);
}

