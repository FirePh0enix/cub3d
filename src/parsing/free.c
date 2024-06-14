#include "../cub3d.h"
#include "../parsing/parsing.h"

bool	free_identifier(char *identifier)
{
	if (identifier)
	{
		identifier = NULL;
		free (identifier);
	}
	return (false);
}
