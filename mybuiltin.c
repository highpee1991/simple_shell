#include "main.h"

/**
 * _custom_exit_ - leaves shell
 * @_pakg: Arguments containing structure.
 *  Return: exit with a _postn 0 if _inf._argu_variable[0] if not exit
 */
int _custom_exit_(_info_str_t *_pakg)
{
	int _exit_checkers;

	if (_pakg->_argu_variable[1])
	{
		_exit_checkers = _error_attoi(_pakg->_argu_variable[1]);
		if (_exit_checkers == -1)
		{
			_pakg->_postn = 2;
			_error_printer_(_pakg, "Illegal number: ");
			_errors_puts_(_pakg->_argu_variable[1]);
			_error_putchar_('\n');
			return (1);
		}
		_pakg->_error_dig = _error_attoi(_pakg->_argu_variable[1]);
		return (-2);
	}
	_pakg->_error_dig = -1;
	return (-2);
}

/**
 * _custom_cd_md - modifies the process of current directory
 * @_pakg: having arguments for const function
 *  Return: Always (0)
 */
int _custom_cd_md(_info_str_t *_pakg)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!_pakg->_argu_variable[1])
	{
		dir = _getenv(_pakg, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(_pakg, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_string_cmp_mode(_pakg->_argu_variable[1], "-") == 0)
	{
		if (!_getenv(_pakg, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(_pakg, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(_pakg, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(_pakg->_argu_variable[1]);
	if (chdir_ret == -1)
	{
		_error_printer_(_pakg, "can't cd to ");
		_errors_puts_(_pakg->_argu_variable[1]), _error_putchar_('\n');
	}
	else
	{
		_cust_env_seter_md(_pakg, "OLDPWD", _getenv(_pakg, "PWD="));
		_cust_env_seter_md(_pakg, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _custom_help_md - modifies the present process
 * @_pakg: containing arguments for managing const prototype.
 *  Return: Always (0)
 */
int _custom_help_md(_info_str_t *_pakg)
{
	char **arg_array;

	arg_array = _pakg->_argu_variable;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
