/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);   // Free the memory pointed to by ptr
		*ptr = NULL;  // Set the pointer to NULL
		return 1;	 // Return 1 to indicate success
	}
	return 0;		 // Return 0 to indicate failure
}
