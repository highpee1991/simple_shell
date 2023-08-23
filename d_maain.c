#include "main.h"

/**
 * main - entry point
 * @ac: argc
 * @av: argv
 * Return: return 0 if it's a success, if not 0
 */
int main(int ac, char **av)
{
	_info_str_t info[] = { _INIT_INFOR_CONS };
	int _filed = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (_filed)
		: "r" (_filed));

	if (ac == 2)
	{
		_filed = open(av[1], O_RDONLY);
		if (_filed == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errors_puts_(av[0]);
				_errors_puts_(": 0: Can't open ");
				_errors_puts_(av[1]);
				_error_putchar_('\n');
				_error_putchar_(_FLUSH_BUFFER_SIZE);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = _filed;
	}
	_increament_env_lis(info);
	_hist_reader_md_(info);
	_history_loo(info, av);
	return (EXIT_SUCCESS);
}
