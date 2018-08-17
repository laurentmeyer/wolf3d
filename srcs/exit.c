#include "wolf3d.h"
#include <unistd.h>

void	exit_message(t_ram *ram, int exit_code, char *message)
{
	if (NULL != ram)
		free_ram(ram);
	if (NULL != message)
		ft_putstr_fd(message, STDERR_FILENO);
	exit(exit_code);
}