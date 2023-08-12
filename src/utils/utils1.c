#include "../../includes/minishell.h"

char **ft_appendstr(char **dest, char *str)
{
	int fulllen;
	int	i;
	char **output;

	i = 0;

	fulllen = getarrlen(dest) + 2;
	output = ft_calloc(fulllen, sizeof(char *));
	while (dest != NULL && i < fulllen - 2)
	{
		output[i] = dest[i];
		i++;
	}
	output[i] = str;
	output[i+1] = NULL;
	free(dest);
	return (output);
}

int	getarrlen(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return (0);
	while(arr[i])
	{
		i++;
	}
	return (i);
}

void free_array(void **arr)
{
	int i = 0;
		while (arr[i] != NULL)
		{
				free(arr[i]);
				i++;
		}
		free(arr);
}

void free_env(char **env)
{
	int i;

	i = getarrlen(env);

	while (i >= 0)
	{	
		free(env[i]);
		i--;
	}
	free(env);
	return ;
}