#include "../../includes/minishell.h"

char **expander(char **tokens, t_data *data)
{
	int i;
	int j;
	char *var;

	(void)data;
	i = 0;
	while(tokens[i])
	{
		j = 0;
		while(tokens[i][j])
		{
			if (tokens[i][j] == '$')
			{
				var = getenv(tokens[i] + j + 1);
				tokens[i][j] = '\0';
				tokens[i] = ft_strjoin(tokens[i], var);
			}
			j++;
		}
		i++;
	}
	return (tokens);
}