#include "main.h"

/**
 * input_buf - container concatenated commands
 * @info: the struct param
 * @buf: location of the buffer
 * @_lengths: _lengths variable location
 * Return: result of byte(s) reads
 */
ssize_t input_buf(_info_str_t *info, char **buf, size_t *_lengths)
{
	ssize_t _red = 0;
	size_t p_length = 0;

	if (!*_lengths)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, _sigint_Handler);
#if _GETLINE_USER
		_red = getline(buf, &p_length, stdin);
#else
		_red = _fetch_line(info, buf, &p_length);
#endif
		if (_red > 0)
		{
			if ((*buf)[_red - 1] == '\n')
			{
				(*buf)[_red - 1] = '\0';
				_red--;
			}
			info->_line_counter_marker = 1;
			_connent_remover_(*buf);
			_histo_li_buld_ins(info, *buf, info->_counter_his++);

			{
				*_lengths = _red;
				info->_instruction_buff = buf;
			}
		}
	}
	return (_red);
}

/**
 * _inpu_getter_md - finds line excluding new one
 * @info: the struct param
 * Return: returns result of byte(s) it reads
 */
ssize_t _inpu_getter_md(_info_str_t *info)
{
	static char *buf;
	static size_t _ind, j, _lengths;
	ssize_t _red = 0;
	char **buf_p = &(info->_arguements), *_pri;

	_putchar(_FLUSH_BUFFER_SIZE);
	_red = input_buf(info, &buf, &_lengths);
	if (_red == -1)
		return (-1);
	if (_lengths)
	{
		j = _ind;
		_pri = buf + _ind;

		_chain_ele_ch(info, buf, &j, _ind, _lengths);
		while (j < _lengths)
		{
			if (_chain_ele_(info, buf, &j))
				break;
			j++;
		}

		_ind = j + 1;
		if (_ind >= _lengths)
		{
			_ind = _lengths = 0;
			info->_struc_buff_instrtn = _COMMAND_NORMAL;
		}

		*buf_p = _pri;
		return (_len_string_mode(_pri));
	}

	*buf_p = buf;
	return (_red);
}

/**
 * read_buf - checks out a buffer
 * @info: the struct param
 * @buf: the buffer
 * @_ind: size
 * Return: _red
 */
ssize_t read_buf(_info_str_t *info, char *buf, size_t *_ind)
{
	ssize_t _red = 0;

	if (*_ind)
		return (0);
	_red = read(info->_inp_intr_fil, buf, _BUFFER_SIZE_READER);
	if (_red >= 0)
		*_ind = _red;
	return (_red);
}

/**
 * _fetch_line - next line of input should be gotten from the STDIN
 * @info: the struct param
 * @ptr: the location of pointer to the container, allocated before or empty
 * @length: the size of the ptr preallocated buffer if it's not empty
 * Return: _dis to be returned
 */
int _fetch_line(_info_str_t *info, char **ptr, size_t *length)
{
	static char buf[_BUFFER_SIZE_READER];
	static size_t _ind, _lengths;
	size_t _indx;
	ssize_t _red = 0, _dis = 0;
	char *_pri = NULL, *_new_pr = NULL, *_ite;

	_pri = *ptr;
	if (_pri && length)
		_dis = *length;
	if (_ind == _lengths)
		_ind = _lengths = 0;

	_red = read_buf(info, buf, &_lengths);
	if (_red == -1 || (_red == 0 && _lengths == 0))
		return (-1);

	_ite = _strchr(buf + _ind, '\n');
	_indx = _ite ? 1 + (unsigned int)(_ite - buf) : _lengths;
	_new_pr = _res_memo(_pri, _dis, _dis ? _dis + _indx : _indx + 1);
	if (!_new_pr)
		return (_pri ? free(_pri), -1 : -1);

	if (_dis)
		_strncat(_new_pr, buf + _ind, _indx - _ind);
	else
		_strncpy(_new_pr, buf + _ind, _indx - _ind + 1);

	_dis += _indx - _ind;
	_ind = _indx;
	_pri = _new_pr;

	if (length)
		*length = _dis;
	*ptr = _pri;
	return (_dis);
}

/**
 * _sigint_Handler - ctrl-C will be terminated
 * @sig_num: the number of the signal
 * Return: (void)
 */
void _sigint_Handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(_FLUSH_BUFFER_SIZE);
}
