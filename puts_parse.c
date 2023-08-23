#include "main.h"

/**
 * _cus_command_ - decides maybe a file is exec cmd
 * @_inf: struct of _inf
 * @_pt: the _pt to file
 * Return: return 1 if correct, else 0
 */
int _cus_command_(_info_str_t *_inf, char *_pt)
{
	struct stat st;

	(void)_inf;
	if (!_pt || stat(_pt, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _chars_duplis_ - make copies of chars
 * @_strpath: PATH string
 * @start: where index begins
 * @stop: where index stops
 * Return: reference to new container
 */
char *_chars_duplis_(char *_strpath, int start, int stop)
{
	static char buf[1024];
	int _ind1 = 0, ind2 = 0;

	for (ind2 = 0, _ind1 = start; _ind1 < stop; _ind1++)
		if (_strpath[_ind1] != ':')
			buf[ind2++] = _strpath[_ind1];
	buf[ind2] = 0;
	return (buf);
}

/**
 * _path_finders_ - checks the cmd in PATH of string
 * @_inf: struct of _inf
 * @_strpath: PATH string
 * @cmd: command to look for
 * Return: _pt if cmd found || empty
 */
char *_path_finders_(_info_str_t *_inf, char *_strpath, char *cmd)
{
	int _ind1 = 0, curr_pos = 0;
	char *_pt;

	if (!_strpath)
		return (NULL);
	if ((_len_string_mode(cmd) > 2) && _starter_mode_(cmd, "./"))
	{
		if (_cus_command_(_inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!_strpath[_ind1] || _strpath[_ind1] == ':')
		{
			_pt = _chars_duplis_(_strpath, curr_pos, _ind1);
			if (!*_pt)
				_cat_string_mode(_pt, cmd);
			else
			{
				_cat_string_mode(_pt, "/");
				_cat_string_mode(_pt, cmd);
			}
			if (_cus_command_(_inf, _pt))
				return (_pt);
			if (!_strpath[_ind1])
				break;
			curr_pos = _ind1;
		}
		_ind1++;
	}
	return (NULL);
}
