#include "main.h"

/**
 * add_node - includes  _node to beginning of list
 * @_hd: location of reference to _hd _node
 * @_wrdstr: filed of string _node
 * @_digit: index _chro_event
 * Return: the list size
 */
_str_li *add_node(_str_li **_hd, const char *_wrdstr, int _digit)
{
	_str_li *_head_new;

	if (!_hd)
		return (NULL);
	_head_new = malloc(sizeof(_str_li));
	if (!_head_new)
		return (NULL);
	_fill_memory((void *)_head_new, 0, sizeof(_str_li));
	_head_new->_digit = _digit;
	if (_wrdstr)
	{
		_head_new->_wrdstr = _string_round_up_mde(_wrdstr);
		if (!_head_new->_wrdstr)
		{
			free(_head_new);
			return (NULL);
		}
	}
	_head_new->next = _hd;
	*_hd = _head_new;
	return (_head_new);
}

/**
 * add_node_end - includes  _node to the extreme list
 * @_hd: the location of the pointer to _hd _node
 * @_wrdstr: string of field _node
 * @_digit: _node _chro_event which index is used
 * Return: the list size
 */
_str_li *add_node_end(_str_li **_hd, const char *_wrdstr, int _digit)
{
	_str_li *_node_new, *_node;

	if (!_hd)
		return (NULL);

	_node = *_hd;
	_node_new = malloc(sizeof(_str_li));
	if (!_node_new)
		return (NULL);
	_fill_memory((void *)_node_new, 0, sizeof(_str_li));
	_node_new->_digit = _digit;
	if (_wrdstr)
	{
		_node_new->_wrdstr = _string_round_up_mde(_wrdstr);
		if (!_node_new->_wrdstr)
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
		_puts(h->_wrdstr ? h->_wrdstr : "(nil)");
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
		free(_node->_wrdstr);
		free(_node);
		return (1);
	}
	_node = *_hd;
	while (_node)
	{
		if (_index == index)
		{
			_node_pre->next = _node->next;
			free(_node->_wrdstr);
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
		free(_node->_wrdstr);
		free(_node);
		_node = node_nxt;
	}
	*head_ptr = NULL;
}
