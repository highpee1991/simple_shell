#include "main.h"

/**
 * _chain_ele_ - check maybe current character in buff is delim or not
 * @_inf: struct param
 * @_buffer: character buff
 * @_nu: the location of current position in _buffer
 * Return: if chain delim return 1, else 0
 */
int _chain_ele_(_info_str_t *_inf, char *_buffer, size_t *_nu)
{
	size_t j = *_nu;

	if (_buffer[j] == '|' && _buffer[j + 1] == '|')
	{
		_buffer[j] = 0;
		j++;
		_inf->cmd_buf_type = _COMMAND_ALT;
	}
	else if (_buffer[j] == '&' && _buffer[j + 1] == '&')
	{
		_buffer[j] = 0;
		j++;
		_inf->cmd_buf_type = _COMMAND_AND;
	}
	else if (_buffer[j] == ';')
	{
		_buffer[j] = 0;
		_inf->cmd_buf_type = _CHAIN_CMMAND;
	}
	else
		return (0);
	*_nu = j;
	return (1);
}

/**
 * _chain_ele_ch - looks if to concatenating based on last status or not
 * @_inf: struct param
 * @_buffer: character buff
 * @_nu: location of current stage in _buffer
 * @_ind1: beginning stage in _buffer
 * @len: _buffer lenght
 * Return: return Void
 */
void _chain_ele_ch(_info_str_t *_inf, char *_buffer, size_t *_nu,
		size_t _ind1, size_t len)
{
	size_t j = *_nu;

	if (_inf->cmd_buf_type == _COMMAND_AND)
	{
		if (_inf->status)
		{
			_buffer[_ind1] = 0;
			j = len;
		}
	}
	if (_inf->cmd_buf_type == _COMMAND_ALT)
	{
		if (!_inf->status)
		{
			_buffer[_ind1] = 0;
			j = len;
		}
	}

	*_nu = j;
}

/**
 * _alias_replacer_ - change alias in string tokenized
 * @_inf: struct param
 * Return: return 1 if replace, else 0
 */
int _alias_replacer_(_info_str_t *_inf)
{
	int _ind1;
	_str_li *node;
	char *_nu;

	for (_ind1 = 0; _ind1 < 10; _ind1++)
	{
		node = node_starts_with(_inf->alias, _inf->argv[0], '=');
		if (!node)
			return (0);
		free(_inf->argv[0]);
		_nu = _strchr(node->str, '=');
		if (!_nu)
			return (0);
		_nu = _string_round_up_mde(_nu + 1);
		if (!_nu)
			return (0);
		_inf->argv[0] = _nu;
	}
	return (1);
}

/**
 * _vars_replacer_ - changes variables in the string tokenized
 * @_inf: struct param
 * Return: replaced? return 1, else return 0
 */
int _vars_replacer_(_info_str_t *_inf)
{
	int _ind1 = 0;
	_str_li *node;

	for (_ind1 = 0; _inf->argv[_ind1]; _ind1++)
	{
		if (_inf->argv[_ind1][0] != '$' || !_inf->argv[_ind1][1])
			continue;

		if (!_string_cmp_mode(_inf->argv[_ind1], "$?"))
		{
			_strings_replacer_(&(_inf->argv[_ind1]),
				_string_round_up_mde(_num_converter_(_inf->status, 10, 0)));
			continue;
		}
		if (!_string_cmp_mode(_inf->argv[_ind1], "$$"))
		{
			_strings_replacer_(&(_inf->argv[_ind1]),
				_string_round_up_mde(_num_converter_(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(_inf->env, &_inf->argv[_ind1][1], '=');
		if (node)
		{
			_strings_replacer_(&(_inf->argv[_ind1]),
				_string_round_up_mde(_strchr(node->str, '=') + 1));
			continue;
		}
		_strings_replacer_(&_inf->argv[_ind1], _string_round_up_mde(""));

	}
	return (0);
}

/**
 * _strings_replacer_ - changes a string
 * @old: location of previous string
 * @new: current string
 * Return: replaced? return 1, return 0 if not
 */
int _strings_replacer_(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
