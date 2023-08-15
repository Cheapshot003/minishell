#include "../../includes/minishell.h"

char *get_env_var_value(t_data *data, char *var_name)
{
    t_list *current;
    t_var *current_var;
	int i;

	i = 0;
    current = data->vars;
	while (*var_name == '\"' || *var_name == '$')
		var_name++;
	while (var_name[i] && var_name[i] != '\"' && var_name[i] != '\'' && !is_whitespace(var_name[i]))
		i++;
    data->exit_str = ft_itoa(data->exit_status);
	if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
		return (data->exit_str);
    while (current != NULL)
    {
        current_var = (t_var *)current->content;
        if (ft_strncmp(current_var->var_name, var_name, i) == 0) {
            return current_var->var_value;
        }
        current = current->next;
    }
    return getenv(var_name);
}

void cut_quotes(char **tokens)
{
    int i;
    int len;
    char *token;
    char *new_token;

    i = 0;
    while (tokens[i] != NULL)
    {
        token = tokens[i];
        len = ft_strlen(token);
        if ((token[0] == '\'' && token[len-1] == '\'') || (token[0] == '"' && token[len-1] == '"'))
        {
            new_token = malloc(len - 1);
            new_token[0] = '\0';
            ft_strlcat(new_token, &token[1], len - 1);
            free(token);
            tokens[i] = new_token;
        }
        i++;
    }
}

char *find_and_replace_unclosed_quote(char  *str, char quote)
{
    int i = 0;
    int move = 0;
    int count = 0;
    int last_quote_pos = 0;

    while (str[i] != '\0') {
        if (str[i] == quote) {
            count++;
            last_quote_pos = i;
        }
        i++;
    }

    if (count % 2 != 0) {
        i = last_quote_pos;
        while (str[i] != '\0') {
            if (str[i] == quote)
                move = 1;
            if (move)
                str[i] = str[i+1];
            i++;
        }
    }
    return str;
}
void	insert_var(t_data *data, char *line, int i)
{
	char *var;
	char *rest;

	rest = line + i ;
	var = get_env_var_value(data, line+i);

}

char *get_env(t_data *data, char *token)
{
	int i;
	char name[1024];
	char *value;

	i = 0;

	while(token[i] && !is_whitespace(token[i]) && !is_special_char(token[i]))
	{
		i++;
	}
	ft_strlcpy(name, token, i+1);
	value = get_env_var_value(data, name);
	return (value);
}
char *get_rest(char *rest)
{
	int i;

	i = 0;
	while (rest[i] && !is_whitespace(rest[i]) && rest[i] != '\"' && !is_special_char(rest[i]))
	{
		i++;
	}
	if (rest[i])
		return (ft_strdup(rest + i));
	else
		return (NULL);
}
void expander(char **tokens, t_data *data) 
{
	int i;
	int j;
	char temp[1024];
	char *rest;
	char *env;
	i = 0;
	while (tokens[i])
	{
		j = 0;
		if (tokens[i][0] == '\'')
			i++;
		else
		{
			while (tokens[i][j])
			{
				if (tokens[i][j] == '$' && (tokens[i][j+1] && !is_whitespace(tokens[i][j])))
				{
					tokens[i][j] = '\0';
					rest = get_rest(tokens[i] + j + 1);
					ft_strlcpy(temp, tokens[i], ft_strlen(tokens[i]) + 1);
					env = get_env(data, tokens[i] + j + 1);
					if (env != NULL)
						ft_strlcat(temp, env, (ft_strlen(temp) + ft_strlen(env) + 1));
					if (rest != NULL)
					{
						ft_strlcat(temp, rest, ft_strlen(temp) + ft_strlen(rest) + 1);
						free(rest);
					}
					
					j = j + ft_strlen(env) - 1;
					free(tokens[i]);
					tokens[i] = ft_strdup(temp);
				}
				j++;
			}
			i++;
		}
	}
}
int	clearstrlen(char *str)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\'')
			j++;
		i++;
	}
	return (j);
}
char *clear_single_quotes(char *str)
{
	int i;
	char *output;
	int len;

	len = clearstrlen(str);
	i = 0;
	output = malloc(len);
	while(str[i])
	{
		if (str[i] == '\'')
		{
			str[i] = '\0';
			ft_strlcat(output, str, len);
		}
		i++;
	}
	free(str);
	str = NULL;
	return (output);
}