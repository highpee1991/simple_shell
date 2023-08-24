#include "main.h"

/**
 * get_environ - the environment string copy returns
 * @_packg: const function prototype.
 * Return: (0) on success
 */
char **get_environ(_info_str_t *_packg)
{
	if (!_packg->environ || _packg->env_changed)
	{
		_packg->environ = list_to_strings(_packg->_env_var_store);
		_packg->env_changed = 0;
	}

	return (_packg->environ);
}

/**
 * _cust_env_unset_md_ - _env_var_store _storg out
 * @_packg: maintaining const prototype.
 *  Return: if removed returns 1, if not return 0
 * @_storg: string environment variable
 */
int _cust_env_unset_md_(_info_str_t *_packg, char *_storg)
{
	_str_li *node = _packg->_env_var_store;
	size_t _ind = 0;
	char *_pr;

	if (!node || !_storg)
		return (0);

	while (node)
	{
		_pr = _starter_mode_(node->_wrdstr, _storg);
		if (_pr && *_pr == '=')
		{
			_packg->env_changed = _del_ind_holder(&(_packg->_env_var_store), _ind);
			_ind = 0;
			node = _packg->_env_var_store;
			continue;
		}
		node = node->next;
		_ind++;
	}
	return (_packg->env_changed);
}

/**
 * _cust_env_seter_md - assisgn _env_var_store var
 * @_packg: maintaining const prototype
 * @_storg: string environment variable
 * @_va: value of string environment variable
 *  Return: (0) on success
 */
int _cust_env_seter_md(_info_str_t *_packg, char *_storg, char *_va)
{
	char *buf = NULL;
	_str_li *node;
	char *_pr;

	if (!_storg || !_va)
		return (0);

	buf = malloc(_len_string_mode(_storg) + _len_string_mode(_va) + 2);
	if (!buf)
		return (1);
	_cpy_string_mode(buf, _storg);
	_cat_string_mode(buf, "=");
	_cat_string_mode(buf, _va);
	node = _packg->_env_var_store;
	while (node)
	{
		_pr = _starter_mode_(node->_wrdstr, _storg);
		if (_pr && *_pr == '=')
		{
			free(node->_wrdstr);
			node->_wrdstr = buf;
			_packg->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(_packg->_env_var_store), buf, 0);
	free(buf);
	_packg->env_changed = 1;
	return (0);
}
