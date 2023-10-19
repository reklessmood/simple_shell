#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer Sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command Chaining Types */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Convert Number Flags */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* History Configuration */
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * Struct to represent a singly linked list.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * Struct to hold various shell-related information.
 */
typedef struct passinfo
{
	char *arg;			   /* Command arguments from getline */
	char **argv;			 /* Array of strings from arg */
	char *path;			  /* Path to the current command */
	int argc;				/* Argument count */
	unsigned int line_count; /* Line count for errors */
	int err_num;			 /* Error code for exit() */
	int linecount_flag;	  /* Flag to count this line of input */
	char *fname;			 /* Program filename */
	list_t *env;			 /* Linked list copy of environ */
	list_t *history;		 /* History node */
	list_t *alias;		   /* Alias node */
	char **environ;		  /* Custom modified copy of environ */
	int env_changed;		 /* Flag for environ changes */
	int status;			  /* Return status of the last executed command */
	char **cmd_buf;		  /* Pointer to command buffer for chaining */
	int cmd_buf_type;		/* Command chaining type (||, &&, ;) */
	int readfd;			  /* File descriptor for reading input */
	int histcount;		   /* History line number count */
} info_t;

/**
 * Struct to define built-in shell commands and their corresponding functions.
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function Prototypes */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int loophsh(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char, int);
int _putsfd(char *, int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *get_history_file(info_t);
int write_history(info_t);
int read_history(info_t);
int build_history_list(info_t, char *, int);
int renumber_history(info_t);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
int is_delim(char, char *);
int interactive(info_t *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

#endif
