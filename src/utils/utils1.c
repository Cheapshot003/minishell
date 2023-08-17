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
		output[i] = ft_strdup(dest[i]);
		i++;
	}
	output[i] = ft_strdup(str);
	output[i+1] = NULL;
	free(str);
	if (dest != NULL)
		free_array((void **)dest);
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
	if (arr == NULL)
		return ;
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

void cut_quotes(char *aux)
{
	char *src;
    char *dest;

	src = aux;
	dest = aux;

    while (*src)
	{
        if (*src != '"' && *src != '\'') {
            *dest = *src;
            dest++;
        }
        src++;
    }
    *dest = '\0';
}