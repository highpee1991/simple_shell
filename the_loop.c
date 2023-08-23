#include "main.h"

/**
 * _history_loo - loop of the shell
 * @_inf: param && gives struct of _inf
 * @_a_var: _argu_variable from main function
 * Return: if success return 0, otherwise 1
 */
int _history_loo(_info_str_t *_inf, char **_a_var)
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
			_infor_setter(_inf, _a_var);
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
	if (!_finteractive_mode(_inf) && _inf->_postn)
		exit(_inf->_postn);
	if (_ret == -2)
	{
		if (_inf->_error_dig == -1)
			exit(_inf->_postn);
		exit(_inf->_error_dig);
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
		{"_env_var_store", _cust_env_md},
		{"help", _custom_help_md},
		{"_chro_event", _cus_hist_md},
		{"setenv", _cust_env_setter},
		{"unsetenv", _unset_env_cus},
		{"cd", _custom_cd_md},
		{"_alter_name", _my_alternative},
		{NULL, NULL}
	};

	for (_ind1 = 0; builtintbl[_ind1].type; _ind1++)
		if (_string_cmp_mode(_inf->_argu_variable[0], builtintbl[_ind1].type) == 0)
		{
			_inf->_line_tally++;
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

	_inf->_trail = _inf->_argu_variable[0];
	if (_inf->_line_counter_marker == 1)
	{
		_inf->_line_tally++;
		_inf->_line_counter_marker = 0;
	}
	for (_ind1 = 0, _ind4 = 0; _inf->_arguements[_ind1]; _ind1++)
		if (!_cus_delimeter_(_inf->_arguements[_ind1], " \t\n"))
			_ind4++;
	if (!_ind4)
		return;

	_pt = _path_finders_(_inf, _getenv(_inf, "PATH="), _inf->_argu_variable[0]);
	if (_pt)
	{
		_inf->_trail = _pt;
		_command_fork_(_inf);
	}
	else
	{
		if ((_finteractive_mode(_inf) || _getenv(_inf, "PATH=")
			|| _inf->_argu_variable[0][0] == '/') && _cus_command_(_inf, _inf->_argu_variable[0]))
			_command_fork_(_inf);
		else if (*(_inf->_arguements) != '\n')
		{
			_inf->_postn = 127;
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
		if (execve(_inf->_trail, _inf->_argu_variable, get_environ(_inf)) == -1)
		{
			_infor_free_md(_inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(_inf->_postn));
		if (WIFEXITED(_inf->_postn))
		{
			_inf->_postn = WEXITSTATUS(_inf->_postn);
			if (_inf->_postn == 126)
				_error_printer_(_inf, "Permission denied\n");
		}
	}
}
