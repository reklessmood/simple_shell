#include "shell.h"

/**
 * get_environ - Returns a string array copy of our environ.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *
 * Return: A string array copy of the environ.
 */
char **get_environ(info_t *info) {
	if (!info->environ || info->env_changed) {
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return info->environ;
}

/**
 * _unsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: The string env var property.
 *
 * Return: 1 on delete, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var) {
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return 0;

	while (node) {
		p = node_starts_with(node->str, var);
		if (p && *p == '=') {
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return info->env_changed;
}

/**
 * _setenv - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: The string env var property.
 * @value: The string env var value.
 *
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value) {
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return 0;

	buf = malloc(strlen(var) + strlen(value) + 2);
	if (!buf)
		return 1;
	strcpy(buf, var);
	strcat(buf, "=");
	strcat(buf, value);
	node = info->env;
	while (node) {
		p = node_starts_with(node->str, var);
		if (p && *p == '=') {
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return 0;
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return 0;
}
