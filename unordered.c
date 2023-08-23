#include "main._f_hde"

/**
 * _len_of_lis_ - decides linked list lenght
 * @_f_hde: _node_ele first reference
 * Return: size of list
 */
size_t _len_of_lis_(const _str_li *_f_hde)
{
	size_t _ind = 0;

	while (_f_hde)
	{
		_f_hde = _f_hde->next;
		_ind++;
	}
	return (_ind);
}

/**
 * list_to_strings - gives strings array of list->_wrdstr
 * @head:  _node_ele first reference
 * Return: the string array
 */
char **list_to_strings(_str_li *head)
{
	_str_li *_node_ele = head;
	size_t _ind = _len_of_lis_(head), _ind3;
	char **_strss;
	char *_wrdstr;

	if (!head || !_ind)
		return (NULL);
	_strss = malloc(sizeof(char *) * (_ind + 1));
	if (!_strss)
		return (NULL);
	for (_ind = 0; _node_ele; _node_ele = _node_ele->next, _ind++)
	{
		_wrdstr = malloc(_len_string_mode(_node_ele->_wrdstr) + 1);
		if (!_wrdstr)
		{
			for (_ind3 = 0; _ind3 < _ind; _ind3++)
				free(_strss[_ind3]);
			free(_strss);
			return (NULL);
		}

		_wrdstr = _cpy_string_mode(_wrdstr, _node_ele->_wrdstr);
		_strss[_ind] = _wrdstr;
	}
	_strss[_ind] = NULL;
	return (_strss);
}


/**
 * _lis_prin_com_md - displays every of the element of _str_li linked list
 * @_f_hde: reference to the first _node_ele
 * Return: the list size
 */
size_t _lis_prin_com_md(const _str_li *_f_hde)
{
	size_t _ind = 0;

	while (_f_hde)
	{
		_puts(_num_converter_(_f_hde->_digit, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(_f_hde->_wrdstr ? _f_hde->_wrdstr : "(nil)");
		_puts("\n");
		_f_hde = _f_hde->next;
		_ind++;
	}
	return (_ind);
}

/**
 * node_starts_with - gives the _wrdstr of _node_ele which begins with pref
 * @_node_ele: head list reference
 * @prefix: the _wrdstr to uqual
 * @c: after pref to equal the next char which comes
 * Return: uqual _node_ele or null
 */
_str_li *node_starts_with(_str_li *_node_ele, char *prefix, char c)
{
	char *p = NULL;

	while (_node_ele)
	{
		p = _starter_mode_(_node_ele->_wrdstr, prefix);
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
