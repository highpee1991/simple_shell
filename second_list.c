#include "main.h"

/**
 * add_node - includes  _node to beginning of list
 * @_hd: location of reference to _hd _node
 * @str: filed of string _node
 * @num: index history
 * Return: the list size
 */
_str_li *add_node(_str_li **_hd, const char *str, int num)
{
	_str_li *_head_new;

	if (!_hd)
		return (NULL);
	_head_new = malloc(sizeof(_str_li));
	if (!_head_new)
		return (NULL);
	_memset((void *)_head_new, 0, sizeof(_str_li));
	_head_new->num = num;
	if (str)
	{
		_head_new->str = _string_round_up_mde(str);
		if (!_head_new->str)
		{
			free(_head_new);
			return (NULL);
		}
	}
	_head_new->next = *_hd;
	*_hd = _head_new;
	return (_head_new);
}

/**
 * add_node_end - includes  _node to the extreme list
 * @_hd: the location of the pointer to _hd _node
 * @str: string of field _node
 * @num: _node history which index is used
 * Return: the list size
 */
_str_li *add_node_end(_str_li **_hd, const char *str, int num)
{
	_str_li *_node_new, *_node;

	if (!_hd)
		return (NULL);

	_node = *_hd;
	_node_new = malloc(sizeof(_str_li));
	if (!_node_new)
		return (NULL);
	_memset((void *)_node_new, 0, sizeof(_str_li));
	_node_new->num = num;
	if (str)
	{
		_node_new->str = _string_round_up_mde(str);
		if (!_node_new->str)
		{
			free(_node_new);
			return (NULL);
		}
	}
	if (_node)
	{
		while (_node->next)
			_node = _node->next;
		_node->next = _node_new;
	}
	else
		*_hd = _node_new;
	return (_node_new);
}

/**
 * _lis_print_mds_ - displays just string elem of _str_li list linked
 * @h: reference to _node
 * Return: the list size
 */
size_t _lis_print_mds_(const _str_li *h)
{
	size_t _index = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		_index++;
	}
	return (_index);
}

/**
 * _del_ind_holder - removes _node at index been given
 * @_hd: location of the pointer to the first _node
 * @index: the _node index to get rid of
 * Return: if success return 1, otherwise 0
 */
int _del_ind_holder(_str_li **_hd, unsigned int index)
{
	_str_li *_node, *_node_pre;
	unsigned int _index = 0;

	if (!_hd || !*_hd)
		return (0);

	if (!index)
	{
		_node = *_hd;
		*_hd = (*_hd)->next;
		free(_node->str);
		free(_node);
		return (1);
	}
	_node = *_hd;
	while (_node)
	{
		if (_index == index)
		{
			_node_pre->next = _node->next;
			free(_node->str);
			free(_node);
			return (1);
		}
		_index++;
		_node_pre = _node;
		_node = _node->next;
	}
	return (0);
}

/**
 * _lis_free_mds_ - releases every nodes of list
 * @head_ptr: location of the reference to _hd _node
 * Return: (void)
 */
void _lis_free_mds_(_str_li **head_ptr)
{
	_str_li *_node, *node_nxt, *_hd;

	if (!head_ptr || !*head_ptr)
		return;
	_hd = *head_ptr;
	_node = _hd;
	while (_node)
	{
		node_nxt = _node->next;
		free(_node->str);
		free(_node);
		_node = node_nxt;
	}
	*head_ptr = NULL;
}
