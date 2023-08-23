#include "main.h"

/**
 * _cus_hist_md - shows list of history.
 * @info: containing arguments
 *  Return: Always (0)
 */
int _cus_hist_md(_info_str_t *info)
{
	_lis_prin_com_md(info->history);
	return (0);
}

/**
 * unset_alias - adjusts alias to be a string
 * @info: struct of parameter
 * @str: alias of the string
 * Return: (0) if success, if not 1
 */
int unset_alias(_info_str_t *info, char *str)
{
	char *_pr, _str_in;
	int ret;

	_pr = _strchr(str, '=');
	if (!_pr)
		return (1);
	_str_in = *_pr;
	*_pr = 0;
	ret = _del_ind_holder(&(info->alias),
		_node_ind_get_(info->alias, node_starts_with(info->alias, str, -1)));
	*_pr = _str_in;
	return (ret);
}

/**
 * set_alias - lets alias be a string
 * @info: struct of param
 * @str: alias of the string
 * Return: if success (0), otherwise 1
 */
int set_alias(_info_str_t *info, char *str)
{
	char *_pr;

	_pr = _strchr(str, '=');
	if (!_pr)
		return (1);
	if (!*++_pr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - formats a string alias
 * @node: node of the alias
 * Return: (0) success, else 1
 */
int print_alias(_str_li *node)
{
	char *_pr = NULL, *a = NULL;

	if (node)
	{
		_pr = _strchr(node->str, '=');
		for (a = node->str; a <= _pr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(_pr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - replicates alias
 * @info: arguments of structs for const functions
 *  Return: Always (0)
 */
int _myalias(_info_str_t *info)
{
	int i = 0;
	char *_pr = NULL;
	_str_li *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		_pr = _strchr(info->argv[i], '=');
		if (_pr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
