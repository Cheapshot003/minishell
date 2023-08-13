#include "../../includes/minishell.h"

void	handle_execerr(t_data *data)
{
	if (errno == EACCES)
		exiterror(data, "Permission denied", 1);
	else
		exiterror(data, "Error", 1);
}