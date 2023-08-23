#include "main.h"

/**
 * _infor_clear_ - sets the struct
 * @_mul: the location of the struct
 */
void _infor_clear_(_info_str_t *_mul)
{
	_mul->arg = NULL;
	_mul->argv = NULL;
	_mul->path = NULL;
	_mul->argc = 0;
}

/**
 * _infor_setter - sets the struct
 * @_mul: location of the struct
 * @av: argv
 */
void _infor_setter(_info_str_t *_mul, char **av)
{
	int _ind = 0;

	_mul->fname = av[0];
	if (_mul->arg)
	{
		_mul->argv = strtow(_mul->arg, " \t");
		if (!_mul->argv)
		{

			_mul->argv = malloc(sizeof(char *) * 2);
			if (_mul->argv)
			{
				_mul->argv[0] = _string_round_up_mde(_mul->arg);
				_mul->argv[1] = NULL;
			}
		}
		for (_ind = 0; _mul->argv && _mul->argv[_ind]; _ind++)
			;
		_mul->argc = _ind;

		_alias_replacer_(_mul);
		_vars_replacer_(_mul);
	}
}

/**
 * _infor_free_md - releases _info_str_t struct
 * @_mul: location of the struct
 * @all: if everything is released return true
 */
void _infor_free_md(_info_str_t *_mul, int all)
{
	_ffree_mode(_mul->argv);
	_mul->argv = NULL;
	_mul->path = NULL;
	if (all)
	{
		if (!_mul->cmd_buf)
			free(_mul->arg);
		if (_mul->env)
			_lis_free_mds_(&(_mul->env));
		if (_mul->history)
			_lis_free_mds_(&(_mul->history));
		if (_mul->alias)
			_lis_free_mds_(&(_mul->alias));
		_ffree_mode(_mul->environ);
			_mul->environ = NULL;
		__bfree_mode((void **)_mul->cmd_buf);
		if (_mul->readfd > 2)
			close(_mul->readfd);
		_putchar(_FLUSH_BUFFER_SIZE);
	}
}
