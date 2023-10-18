#include "main.h"

/**
 * execute - Function for arguments execution
 * @args: The input line from where the arguments are parsed
 *
 * Return: Corresponding function-launch function results
 */
int execute(char **args)
{
char *built_in_str[] = {
		"exit",
		"env"
	};
int (*built_in_func[]) (char **) = {
		&built_in_exit,
		&built_in_env
	};

	int i;

	if (args[0] == NULL) /* No arguments */
	{
		return (1); /* Return 1 to continue the loop in main function */
	}
	/* Loop - built-in commands array */
	for (i = 0; i < num_built_ins(); i++)
	{/* If  first argument matches  built-in command  */
		if (strcmp(args[0], built_in_str[i]) == 0)
		{/* Call  corresponding function and return result */
			return ((*built_in_func[i])(args));
		}
	}
	/* No built-in command matches, launch program and return result */
	return (launch(args));
}
