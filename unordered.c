#include "main.h"

/**
 * _len_of_lis_ - decides linked list lenght
 * @h: _node_ele first reference
 * Return: size of list
 */
size_t _len_of_lis_(const _str_li *h)
{
	size_t _ind = 0;

	while (h)
	{
		h = h->next;
		_ind++;
	}
	return (_ind);
}

/**
 * list_to_strings - gives strings array of list->str
 * @head:  _node_ele first reference
 * Return: the string array
 */
char **list_to_strings(_str_li *head)
{
	_str_li *_node_ele = head;
	size_t _ind = _len_of_lis_(head), _ind3;
	char **_strss;
	char *str;

	if (!head || !_ind)
		return (NULL);
	_strss = malloc(sizeof(char *) * (_ind + 1));
	if (!_strss)
		return (NULL);
	for (_ind = 0; _node_ele; _node_ele = _node_ele->next, _ind++)
	{
		str = malloc(_len_string_mode(_node_ele->str) + 1);
		if (!str)
		{
			for (_ind3 = 0; _ind3 < _ind; _ind3++)
				free(_strss[_ind3]);
			free(_strss);
			return (NULL);
		}

		str = _cpy_string_mode(str, _node_ele->str);
		_strss[_ind] = str;
	}
	_strss[_ind] = NULL;
	return (_strss);
}


/**
 * _lis_prin_com_md - displays every of the element of _str_li linked list
 * @h: reference to the first _node_ele
 * Return: the list size
 */
size_t _lis_prin_com_md(const _str_li *h)
{
	size_t _ind = 0;

	while (h)
	{
		_puts(_num_converter_(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		_ind++;
	}
	return (_ind);
}

/**
 * node_starts_with - gives the str of _node_ele which begins with pref
 * @_node_ele: head list reference
 * @prefix: the str to uqual
 * @c: after pref to equal the next char which comes
 * Return: uqual _node_ele or null
 */
_str_li *node_starts_with(_str_li *_node_ele, char *prefix, char c)
{
	char *p = NULL;

	while (_node_ele)
	{
		p = _starter_mode_(_node_ele->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (_node_ele);
		_node_ele = _node_ele->next;
	}
	return (NULL);
}

/**
 * _node_ind_get_ - the ind of _node_ele to get
 * @head: reference to list head
 * @_node_ele: the _node_ele reference
 * Return: _node_ele index rather -1
 */
ssize_t _node_ind_get_(_str_li *head, _str_li *_node_ele)
{
	size_t _ind = 0;

	while (head)
	{
		if (head == _node_ele)
			return (_ind);
		head = head->next;
		_ind++;
	}
	return (-1);
}
