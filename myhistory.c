#include "main.h"

/**
 * get_history_file - file _chro_event to get
 * @_pakg: the struct param
 * Return: returns a string having the file _chro_event
 */

char *get_history_file(_info_str_t *_pakg)
{
	char *_buffer, *_direc;

	_direc = _getenv(_pakg, "HOME=");
	if (!_direc)
		return (NULL);
	_buffer = malloc(sizeof(char) * (_len_string_mode(_direc)
				+ _len_string_mode(_HISTORY_FILER) + 2));
	if (!_buffer)
		return (NULL);
	_buffer[0] = 0;
	_cpy_string_mode(_buffer, _direc);
	_cat_string_mode(_buffer, "/");
	_cat_string_mode(_buffer, _HISTORY_FILER);
	return (_buffer);
}

/**
 * _histo_writer_getter_ - add to existing file or make a new one
 * @_pakg: struct param
 * Return: if it's success return 1, otherwise return -1
 */
int _histo_writer_getter_(_info_str_t *_pakg)
{
	ssize_t _file_dir;
	char *filename = get_history_file(_pakg);
	_str_li *node = NULL;

	if (!filename)
		return (-1);

	_file_dir = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (_file_dir == -1)
		return (-1);
	for (node = _pakg->_chro_event; node; node = node->next)
	{
		_fds_putss_(node->_wrdstr, _file_dir);
		_fdsputs('\n', _file_dir);
	}
	_fdsputs(_FLUSH_BUFFER_SIZE, _file_dir);
	close(_file_dir);
	return (1);
}

/**
 * _hist_reader_md_ - _chro_event file to read
 * @_pakg: struct param
 * Return: if on success return _counter_his, if not return 0
 */
int _hist_reader_md_(_info_str_t *_pakg)
{
	int _ind1, _lis = 0, _counter = 0;
	ssize_t _file_dir, _linrd, _file_size = 0;
	struct stat st;
	char *_buffer = NULL, *filename = get_history_file(_pakg);

	if (!filename)
		return (0);

	_file_dir = open(filename, O_RDONLY);
	free(filename);
	if (_file_dir == -1)
		return (0);
	if (!fstat(_file_dir, &st))
		_file_size = st.st_size;
	if (_file_size < 2)
		return (0);
	_buffer = malloc(sizeof(char) * (_file_size + 1));
	if (!_buffer)
		return (0);
	_linrd = read(_file_dir, _buffer, _file_size);
	_buffer[_file_size] = 0;
	if (_linrd <= 0)
		return (free(_buffer), 0);
	close(_file_dir);
	for (_ind1 = 0; _ind1 < _file_size; _ind1++)
		if (_buffer[_ind1] == '\n')
		{
			_buffer[_ind1] = 0;
			_histo_li_buld_ins(_pakg, _buffer + _lis, _counter++);
			_lis = _ind1 + 1;
		}
	if (_lis != _ind1)
		_histo_li_buld_ins(_pakg, _buffer + _lis, _counter++);
	free(_buffer);
	_pakg->_counter_his = _counter;
	while (_pakg->_counter_his-- >= _HISTORY_MAX)
		_del_ind_holder(&(_pakg->_chro_event), 0);
	_histo_re_setter(_pakg);
	return (_pakg->_counter_his);
}

/**
 * _histo_li_buld_ins - include entry to _chro_event list
 * @_pakg: arguments of structs
 * @_buffer: buffer
 * @_counter: _chro_event of the _counter and the _counter_his
 * Return: (0) on success
 */
int _histo_li_buld_ins(_info_str_t *_pakg, char *_buffer, int _counter)
{
	_str_li *node = NULL;

	if (_pakg->_chro_event)
		node = _pakg->_chro_event;
	add_node_end(&node, _buffer, _counter);

	if (!_pakg->_chro_event)
		_pakg->_chro_event = node;
	return (0);
}

/**
 * _histo_re_setter - _chro_event of linked list to be renumbered after changes
 * @_pakg: maintaining the struct arguments
 * Return: latest _counter_his
 */
int _histo_re_setter(_info_str_t *_pakg)
{
	_str_li *node = _pakg->_chro_event;
	int _ind1 = 0;

	while (node)
	{
		node->_digit = _ind1++;
		node = node->next;
	}
	return (_pakg->_counter_his = _ind1);
}
