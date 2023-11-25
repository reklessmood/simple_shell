#include "shell.h"

/*
 * clear_info - initialize info_t struct
 * info: struct adress
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct adress
 * @av: argument vector
*/
void set-info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc= i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct adress
 * @all: true if freeing all fields
*/
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->path = NULL;
	info->argv = NULL;
	if (all)
	{
		if (!info->)
	}
}