#include "shell.h"

/**
 * __bfree_mode - releases the reference then emoty the location
 * @_points: location the reference to free
 * Return: if released return 1, else return (0)
 */
int __bfree_mode(void **_points)
{
	if (_points && *_points)
	{
		free(*_points);
		*_points = NULL;
		return (1);
	}
	return (0);
}
