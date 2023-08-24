#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <sys/types.h>

#define _BUFFER_SIZE_READER 1024
#define _BUFFER_SIZE_WRITER 1024
#define _FLUSH_BUFFER_SIZE -1

#define _COMMAND_NORMAL	0
#define _COMMAND_ALT 1
#define _COMMAND_AND 2
#define _CHAIN_CMMAND 3

#define _LOWERCASE_CONVERTER 1
#define _UNSIGNED_CONVERTER 2

#define _GETLINE_USER 0
#define _STRTOK_USER 0

#define _HISTORY_FILER ".simple_shell_history"
#define _HISTORY_MAX	4096


extern char **environ;

/**
 * struct _strlister_ - Node of a singly linked list
 * @_digit: An integer field representing a number
 * @_wrdstr: A string field
 * @next: Pointer to the next node in the list
 */
typedef struct _strlister_
{
	int _digit;
	char *_wrdstr;
	struct _strlister_ *next;
} _str_li;

/**
 * struct _info_passer - Contains information to
 * be passed as pseudo-arguments
 * to a function, enabling a uniform prototype for a
 * function pointer struct.
 * @_arguements: A string generated from getline that
 * contains arguments.
 * @_argu_variable: An array of strings generated from '_arguements'.
 * @_trail: A string representing the current command's _trail.
 * @_argue_count: The argument count.
 * @_line_tally: The error count.
 * @_error_dig: The error code for exit() calls.
 * @_line_counter_marker: If active, count this line of input.
 * @_file_plate: The program filename.
 * @_env_var_store: A linked list representing a local copy of environ.
 * @environ: A custom modified copy of environ from LL _env_var_store.
 * @_chro_event: The _chro_event node.
 * @_alter_name: The _alter_name node.
 * @env_changed: If active, environ was changed.
 * @_postn: The return _postn of the last executed command.
 * @_instruction_buff: Address of the pointer to _instruction_buff; active if chaining.
 * @_struc_buff_instrtn: CMD_type: ||, &&, ;.
 * @_inp_intr_fil: The file descriptor from which to read line input.
 * @_counter_his: The _chro_event line number count.
 */
typedef struct _info_passer
{
	char *_arguements;
	char **_argu_variable;
	char *_trail;
	int _argue_count;
	unsigned int _line_tally;
	int _error_dig;
	int _line_counter_marker;
	char *_file_plate;
	_str_li *_env_var_store;
	_str_li *_chro_event;
	_str_li *_alter_name;
	char **environ;
	int env_changed;
	int _postn;

	char **_instruction_buff;
	int _struc_buff_instrtn;
	int _inp_intr_fil;
	int _counter_his;
} _info_str_t;

#define _INIT_INFOR_CONS \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
 * struct _builtin_cmds_ - Contains a _builtin_cmds_
 * string along with its related function.
 * @type: The flag representing the _builtin_cmds_ command.
 * @func: The associated function.
 */
typedef struct _builtin_cmds_
{
	char *type;
	int (*func)(_info_str_t *);
} _table_bult_in;


int _history_loo(_info_str_t *, char **);
int _built_in_finders(_info_str_t *);
void _command_finder_(_info_str_t *);
void _command_fork_(_info_str_t *);

int _cus_command_(_info_str_t *, char *);
char *_chars_duplis_(char *, int, int);
char *_path_finders_(_info_str_t *, char *, char *);

int _loops_shs(char **);

void _errors_puts_(char *);
int _error_putchar_(char);
int _fdsputs(char c, int fd);
int _fds_putss_(char *_wrdstr, int fd);

int _len_string_mode(char *);
int _string_cmp_mode(char *, char *);
char *_starter_mode_(const char *, const char *);
char *_cat_string_mode(char *, char *);

char *_cpy_string_mode(char *, char *);
char *_string_round_up_mde(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **tokenizeString(char *, char *);
char **_segstring(char *, char);

char *_fill_memory(char *, char, unsigned int);
void _f_fring_option(char **);
void *_res_memo(void *, unsigned int, unsigned int);

int _bi_freein_optn(void **);

int _finteractive_mode(_info_str_t *);
int _cus_delimeter_(char, char *);
int _cus_alph(int);
int _atoi(char *);

int _error_attoi(char *);
void _error_printer_(_info_str_t *, char *);
int print_d(int, int);
char *_num_converter_(long int, int, int);
void _connent_remover_(char *);

int _custom_exit_(_info_str_t *);
int _custom_cd_md(_info_str_t *);
int _custom_help_md(_info_str_t *);

int _cus_hist_md(_info_str_t *);
int _my_alternative(_info_str_t *);

ssize_t _inpu_getter_md(_info_str_t *);
int _fetch_line(_info_str_t *, char **, size_t *);
void _sigint_Handler(int);

void _infor_clear_(_info_str_t *);
void _infor_setter(_info_str_t *, char **);
void _infor_free_md(_info_str_t *, int);

char *_getenv(_info_str_t *, const char *);
int _cust_env_md(_info_str_t *);
int _cust_env_setter(_info_str_t *);
int _unset_env_cus(_info_str_t *);
int _increament_env_lis(_info_str_t *);

char **get_environ(_info_str_t *);
int _cust_env_unset_md_(_info_str_t *, char *);
int _cust_env_seter_md(_info_str_t *, char *, char *);

char *get_history_file(_info_str_t *info);
int _histo_writer_getter_(_info_str_t *info);
int _hist_reader_md_(_info_str_t *info);
int _histo_li_buld_ins(_info_str_t *info, char *buf, int linecount);
int _histo_re_setter(_info_str_t *info);

_str_li *add_node(_str_li **, const char *, int);
_str_li *add_node_end(_str_li **, const char *, int);
size_t _lis_print_mds_(const _str_li *);
int _del_ind_holder(_str_li **, unsigned int);
void _lis_free_mds_(_str_li **);

size_t _len_of_lis_(const _str_li *);
char **list_to_strings(_str_li *);
size_t _lis_prin_com_md(const _str_li *);
_str_li *node_starts_with(_str_li *, char *, char);
ssize_t _node_ind_get_(_str_li *, _str_li *);

int _chain_ele_(_info_str_t *, char *, size_t *);
void _chain_ele_ch(_info_str_t *, char *, size_t *, size_t, size_t);
int _alias_replacer_(_info_str_t *);
int _vars_replacer_(_info_str_t *);
int _strings_replacer_(char **, char *);

#endif
