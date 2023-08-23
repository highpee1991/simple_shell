#include "main.h"

/**
 * _cust_env_md - formats presents _env_var_store
 * @_in: const function prototype.
 * Return: (0) success
 */
int _cust_env_md(_info_str_t *_in)
{
	_lis_print_mds_(_in->_env_var_store);
	return (0);
}

/**
 * _getenv - _env_var_store variable value
 * @_in: having arguments
 * @name: variable name of the environment
 * Return: value
 */
char *_getenv(_info_str_t *_in, const char *name)
{
	_str_li *node = _in->_env_var_store;
	char *p;

	while (node)
	{
		p = _starter_mode_(node->_wrdstr, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _cust_env_setter - sets _env_var_store var
 * @_in: maintaining const functions
 *  Return: (0) on success
 */
int _cust_env_setter(_info_str_t *_in)
{
	if (_in->_argue_count != 3)
	{
		_errors_puts_("Incorrect number of arguements\n");
		return (1);
	}
	if (_cust_env_seter_md(_in, _in->_argu_variable[1], _in->_argu_variable[2]))
		return (0);
	return (1);
}

/**
 * _unset_env_cus - _env_var_store var will be removed
 * @_in: function prototype struct.
 *  Return: (0) on success
 */
int _unset_env_cus(_info_str_t *_in)
{
	int i;

	if (_in->_argue_count == 1)
	{
		_errors_puts_("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= _in->_argue_count; i++)
		_cust_env_unset_md_(_in, _in->_argu_variable[i]);

	return (0);
}

/**
 * _increament_env_lis - blows up environment list
 * @_in: function prototype const.
 * Return: (0) on success
 */
int _increament_env_lis(_info_str_t *_in)
{
	_str_li *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	_in->_env_var_store = node;
	return (0);
}
