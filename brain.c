#include "main.h"

/**
 * _bi_freein_optn - releases the reference then emoty the location
 * @_locatorrs: location the reference to free
 * Return: if released return 1, else return (0)
 */
int _bi_freein_optn(void **_locatorrs)
{
	if (_locatorrs && *_locatorrs)
	{
		free(*_locatorrs);
		*_locatorrs = NULL;
		return (1);
	}
	return (0);
}
