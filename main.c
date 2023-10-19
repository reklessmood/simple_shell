#include "shell.h"

/**
 * main - Entry point for the shell.
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	/*This block of assembly code seems to be modifying the 'fd' variable.*/
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		/*Attempt to open a file for input if a filename is provided as an argument.*/
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}

	/* Initialize environment variables and read command history.*/
	populate_env_list(info);
	read_history(info);

	/* Start the main shell loop.*/
	hsh(info, av);

	return (EXIT_SUCCESS);
}
