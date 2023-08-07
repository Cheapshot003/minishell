#include "../../includes/minishell.h"

char **expander(char **tokens, t_data *data)
{
	int i;
	int j;

	(void)data;
	i = 0;
	while(tokens[i])
	{
		j = 0;
		while(tokens[i][j])
		{
			if (tokens[i][j] == '$')
			{
				tokens[i] = getenv(tokens[i] + 1);
			}
			j++;
		}
		i++;
	}
	return (tokens);
}