#include "../includes/minishell.h"

char **gettokens(char *input, t_data *data)
{
  	char **tokens;
  	int nToken;
  	int i;

  	i = 1;
  	nToken = counttoken(input, ' ');
  	data->arg_count = nToken;
  	tokens = malloc(sizeof(char *) * (nToken + 1));
  	tokens[nToken] = NULL;
  	if (nToken-- > 0)
   		tokens[0] = strtok(input, " ");
  	while(nToken-- > 0)
 		tokens[i++] = strtok(NULL, " ");
	parse_tokens(tokens, data);
	return tokens;
}

void parse_tokens(char **tokens, t_data *data)
{
	int i;
	int arglen;
	int j;

	arglen = 0;
	i = 0;
	j = 0;

	arglen = countargs(tokens, data);
	data->path_args = ft_calloc(arglen + 1, sizeof(char *));
	while (i < data->arg_count)
	{
		if (!is_special(tokens[i]))
		{
			data->path_args[j] = tokens[i];
			j++;
			i++;
		}
		else
		{
			i++;
			i++;
		}
	}
	data->path_args[i] = NULL;
	return ;
}
int countargs(char **tokens, t_data *data)
{
	int i;
	int j;
	i = 0;
	j = 0;
	while (i < data->arg_count)
	{
		if (!is_special(tokens[i]))
		{
			i++;
			j++;
		}
		else
		{
			i++;
		}
	}
	return (j);
}

int is_special(char *token)
{
	int i;

	i = 0;
	if (token == NULL)
		return (0);
	while (token[i])
	{
		if (token[i] == '<' || token[i] == '>' || token[i] == '|')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
int counttoken(char *str, char delim)
{
  int i = 1;
  while (*str)
  {
    if (*str == delim)
      i++;
    str++;
  }
  return (i);
}
