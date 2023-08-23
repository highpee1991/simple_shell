#include "main.h"

/**
 * _history_loo - loop of the shell
 * @_inf: param && gives struct of _inf
 * @av: argv from main function
 * Return: if success return 0, otherwise 1
 */
int _history_loo(_info_str_t *_inf, char **av)
{
	ssize_t sz_r = 0;
	int _ret = 0;

	while (sz_r != -1 && _ret != -2)
	{
		_infor_clear_(_inf);
		if (_finteractive_mode(_inf))
			_puts("$ ");
		_error_putchar_(_FLUSH_BUFFER_SIZE);
		sz_r = _inpu_getter_md(_inf);
		if (sz_r != -1)
		{
			_infor_setter(_inf, av);
			_ret = _built_in_finders(_inf);
			if (_ret == -1)
				_command_finder_(_inf);
		}
		else if (_finteractive_mode(_inf))
			_putchar('\n');
		_infor_free_md(_inf, 0);
	}
	_histo_writer_getter_(_inf);
	_infor_free_md(_inf, 1);
	if (!_finteractive_mode(_inf) && _inf->status)
		exit(_inf->status);
	if (_ret == -2)
	{
		if (_inf->err_num == -1)
			exit(_inf->status);
		exit(_inf->err_num);
	}
	return (_ret);
}

/**
 * _built_in_finders - looks for a _builtin_cmds_ cmd
 * @_inf: param && gives struct of _inf
 * Return: return -1 if _builtin_cmds_ not found, retun 0 if successful
 * return 1 if _builtin_cmds_ found but not rathersuccessful
 * retun -2 if _builtin_cmds_ signals exits()
 */
int _built_in_finders(_info_str_t *_inf)
{
	int _ind1, _ret_s = -1;
	_table_bult_in builtintbl[] = {
		{"exit", _custom_exit_},
		{"env", _cust_env_md},
		{"help", _custom_help_md},
		{"history", _cus_hist_md},
		{"setenv", _cust_env_setter},
		{"unsetenv", _unset_env_cus},
		{"cd", _custom_cd_md},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (_ind1 = 0; builtintbl[_ind1].type; _ind1++)
		if (_string_cmp_mode(_inf->argv[0], builtintbl[_ind1].type) == 0)
		{
			_inf->line_count++;
			_ret_s = builtintbl[_ind1].func(_inf);
			break;
		}
	return (_ret_s);
}

/**
 * _command_finder_ - finds a command in PATH
 * @_inf: param && returns struct of _inf
 * Return: (void)
 */
void _command_finder_(_info_str_t *_inf)
{
	char *_pt = NULL;
	int _ind1, _ind4;

	_inf->path = _inf->argv[0];
	if (_inf->linecount_flag == 1)
	{
		_inf->line_count++;
		_inf->linecount_flag = 0;
	}
	for (_ind1 = 0, _ind4 = 0; _inf->arg[_ind1]; _ind1++)
		if (!_cus_delimeter_(_inf->arg[_ind1], " \t\n"))
			_ind4++;
	if (!_ind4)
		return;

	_pt = _path_finders_(_inf, _getenv(_inf, "PATH="), _inf->argv[0]);
	if (_pt)
	{
		_inf->path = _pt;
		_command_fork_(_inf);
	}
	else
	{
		if ((_finteractive_mode(_inf) || _getenv(_inf, "PATH=")
			|| _inf->argv[0][0] == '/') && _cus_command_(_inf, _inf->argv[0]))
			_command_fork_(_inf);
		else if (*(_inf->arg) != '\n')
		{
			_inf->status = 127;
			_error_printer_(_inf, "not found\n");
		}
	}
}

/**
 * _command_fork_ - forks a an exec thread to run cmd
 * @_inf: param && returns the struct of _inf
 * Return: (void)
 */
void _command_fork_(_info_str_t *_inf)
{
	pid_t _pid;

	_pid = fork();
	if (_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (_pid == 0)
	{
		if (execve(_inf->path, _inf->argv, get_environ(_inf)) == -1)
		{
			_infor_free_md(_inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(_inf->status));
		if (WIFEXITED(_inf->status))
		{
			_inf->status = WEXITSTATUS(_inf->status);
			if (_inf->status == 126)
				_error_printer_(_inf, "Permission denied\n");
		}
	}
}
