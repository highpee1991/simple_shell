#include "main.h"

/**
 * get_environ - the environment string copy returns
 * @info: const function prototype.
 * Return: (0) on success
 */
char **get_environ(_info_str_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _cust_env_unset_md_ - env var out
 * @info: maintaining const prototype.
 *  Return: if removed returns 1, if not return 0
 * @var: string environment variable
 */
int _cust_env_unset_md_(_info_str_t *info, char *var)
{
	_str_li *node = info->env;
	size_t _ind = 0;
	char *_pr;

	if (!node || !var)
		return (0);

	while (node)
	{
		_pr = _starter_mode_(node->str, var);
		if (_pr && *_pr == '=')
		{
			info->env_changed = _del_ind_holder(&(info->env), _ind);
			_ind = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		_ind++;
	}
	return (info->env_changed);
}

/**
 * _cust_env_seter_md - assisgn env var
 * @info: maintaining const prototype
 * @var: string environment variable
 * @value: value of string environment variable
 *  Return: (0) on success
 */
int _cust_env_seter_md(_info_str_t *info, char *var, char *value)
{
	char *buf = NULL;
	_str_li *node;
	char *_pr;

	if (!var || !value)
		return (0);

	buf = malloc(_len_string_mode(var) + _len_string_mode(value) + 2);
	if (!buf)
		return (1);
	_cpy_string_mode(buf, var);
	_cat_string_mode(buf, "=");
	_cat_string_mode(buf, value);
	node = info->env;
	while (node)
	{
		_pr = _starter_mode_(node->str, var);
		if (_pr && *_pr == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
