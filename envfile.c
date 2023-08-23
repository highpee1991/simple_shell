#include "main.h"

/**
 * _cust_env_md - formats presents env
 * @_in: const function prototype.
 * Return: (0) success
 */
int _cust_env_md(_info_str_t *_in)
{
	_lis_print_mds_(_in->env);
	return (0);
}

/**
 * _getenv - env variable value
 * @_in: having arguments
 * @name: variable name of the environment
 * Return: value
 */
char *_getenv(_info_str_t *_in, const char *name)
{
	_str_li *node = _in->env;
	char *p;

	while (node)
	{
		p = _starter_mode_(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _cust_env_setter - sets env var
 * @_in: maintaining const functions
 *  Return: (0) on success
 */
int _cust_env_setter(_info_str_t *_in)
{
	if (_in->argc != 3)
	{
		_errors_puts_("Incorrect number of arguements\n");
		return (1);
	}
	if (_cust_env_seter_md(_in, _in->argv[1], _in->argv[2]))
		return (0);
	return (1);
}

/**
 * _unset_env_cus - env var will be removed
 * @_in: function prototype struct.
 *  Return: (0) on success
 */
int _unset_env_cus(_info_str_t *_in)
{
	int i;

	if (_in->argc == 1)
	{
		_errors_puts_("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= _in->argc; i++)
		_cust_env_unset_md_(_in, _in->argv[i]);

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
	_in->env = node;
	return (0);
}
