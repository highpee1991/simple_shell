#include "main.h"

/**
 * _infor_clear_ - sets the struct
 * @_mul: the location of the struct
 */
void _infor_clear_(_info_str_t *_mul)
{
	_mul->_arguements = NULL;
	_mul->_argu_variable = NULL;
	_mul->_trail = NULL;
	_mul->_argue_count = 0;
}

/**
 * _infor_setter - sets the struct
 * @_mul: location of the struct
 * @av: _argu_variable
 */
void _infor_setter(_info_str_t *_mul, char **av)
{
	int _ind = 0;

	_mul->_file_plate = av[0];
	if (_mul->_arguements)
	{
		_mul->_argu_variable = tokenizeString(_mul->_arguements, " \t");
		if (!_mul->_argu_variable)
		{

			_mul->_argu_variable = malloc(sizeof(char *) * 2);
			if (_mul->_argu_variable)
			{
				_mul->_argu_variable[0] = _string_round_up_mde(_mul->_arguements);
				_mul->_argu_variable[1] = NULL;
			}
		}
		for (_ind = 0; _mul->_argu_variable && _mul->_argu_variable[_ind]; _ind++)
			;
		_mul->_argue_count = _ind;

		_alias_replacer_(_mul);
		_vars_replacer_(_mul);
	}
}

/**
 * _infor_free_md - releases _info_str_t struct
 * @_mul: location of the struct
 * @all: if everything is released return true
 */
void _infor_free_md(_info_str_t *_mul, int all)
{
	_f_fring_option(_mul->_argu_variable);
	_mul->_argu_variable = NULL;
	_mul->_trail = NULL;
	if (all)
	{
		if (!_mul->_instruction_buff)
			free(_mul->_arguements);
		if (_mul->_env_var_store)
			_lis_free_mds_(&(_mul->_env_var_store));
		if (_mul->_chro_event)
			_lis_free_mds_(&(_mul->_chro_event));
		if (_mul->_alter_name)
			_lis_free_mds_(&(_mul->_alter_name));
		_f_fring_option(_mul->environ);
			_mul->environ = NULL;
		_bi_freein_optn((void **)_mul->_instruction_buff);
		if (_mul->_inp_intr_fil > 2)
			close(_mul->_inp_intr_fil);
		_putchar(_FLUSH_BUFFER_SIZE);
	}
}
