#include "main.h"

/**
 * _custom_exit_ - leaves shell
 * @_inf: Arguments containing structure.
 *  Return: exit with a status 0 if _inf.argv[0] if not exit
 */
int _custom_exit_(_info_str_t *_inf)
{
	int _exit_checkers;

	if (_inf->argv[1])
	{
		_exit_checkers = _error_attoi(_inf->argv[1]);
		if (_exit_checkers == -1)
		{
			_inf->status = 2;
			_error_printer_(_inf, "Illegal number: ");
			_errors_puts_(_inf->argv[1]);
			_error_putchar_('\n');
			return (1);
		}
		_inf->err_num = _error_attoi(_inf->argv[1]);
		return (-2);
	}
	_inf->err_num = -1;
	return (-2);
}

/**
 * _custom_cd_md - modifies the process of current directory
 * @_inf: having arguments for const function
 *  Return: Always (0)
 */
int _custom_cd_md(_info_str_t *_inf)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!_inf->argv[1])
	{
		dir = _getenv(_inf, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(_inf, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_string_cmp_mode(_inf->argv[1], "-") == 0)
	{
		if (!_getenv(_inf, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(_inf, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(_inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(_inf->argv[1]);
	if (chdir_ret == -1)
	{
		_error_printer_(_inf, "can't cd to ");
		_errors_puts_(_inf->argv[1]), _error_putchar_('\n');
	}
	else
	{
		_cust_env_seter_md(_inf, "OLDPWD", _getenv(_inf, "PWD="));
		_cust_env_seter_md(_inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _custom_help_md - modifies the present process
 * @_inf: containing arguments for managing const prototype.
 *  Return: Always (0)
 */
int _custom_help_md(_info_str_t *_inf)
{
	char **arg_array;

	arg_array = _inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
