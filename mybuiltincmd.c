#include "main.h"

/**
 * _cus_hist_md - shows list of _chro_event.
 * @_pakg: containing arguments
 *  Return: Always (0)
 */
int _cus_hist_md(_info_str_t *_pakg)
{
	_lis_prin_com_md(_pakg->_chro_event);
	return (0);
}

/**
 * unset_alias - adjusts _alter_name to be a string
 * @_pakg: struct of parameter
 * @_wrdstr: _alter_name of the string
 * Return: (0) if success, if not 1
 */
int unset_alias(_info_str_t *_pakg, char *_wrdstr)
{
	char *_pr, _str_in;
	int ret;

	_pr = _strchr(_wrdstr, '=');
	if (!_pr)
		return (1);
	_str_in = *_pr;
	*_pr = 0;
	ret = _del_ind_holder(&(_pakg->_alter_name),
		_node_ind_get_(_pakg->_alter_name,
			node_starts_with(_pakg->_alter_name, _wrdstr, -1)));
	*_pr = _str_in;
	return (ret);
}

/**
 * set_alias - lets _alter_name be a string
 * @_pakg: struct of param
 * @_wrdstr: _alter_name of the string
 * Return: if success (0), otherwise 1
 */
int set_alias(_info_str_t *_pakg, char *_wrdstr)
{
	char *_pr;

	_pr = _strchr(_wrdstr, '=');
	if (!_pr)
		return (1);
	if (!*++_pr)
		return (unset_alias(_pakg, _wrdstr));

	unset_alias(_pakg, _wrdstr);
	return (add_node_end(&(_pakg->_alter_name), _wrdstr, 0) == NULL);
}

/**
 * print_alias - formats a string _alter_name
 * @node: node of the _alter_name
 * Return: (0) success, else 1
 */
int print_alias(_str_li *node)
{
	char *_pr = NULL, *a = NULL;

	if (node)
	{
		_pr = _strchr(node->_wrdstr, '=');
		for (a = node->_wrdstr; a <= _pr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(_pr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _my_alternative - replicates _alter_name
 * @_pakg: arguments of structs for const functions
 *  Return: Always (0)
 */
int _my_alternative(_info_str_t *_pakg)
{
	int i = 0;
	char *_pr = NULL;
	_str_li *node = NULL;

	if (_pakg->_argue_count == 1)
	{
		node = _pakg->_alter_name;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; _pakg->_argu_variable[i]; i++)
	{
		_pr = _strchr(_pakg->_argu_variable[i], '=');
		if (_pr)
			set_alias(_pakg, _pakg->_argu_variable[i]);
		else
			print_alias(node_starts_with(_pakg->_alter_name,
						_pakg->_argu_variable[i], '='));
	}

	return (0);
}
