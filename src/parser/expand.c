#include "../../includes/minishell.h"

char *get_env_var_value(t_data *data, char *var_name)
{
    t_list *current;
    t_var *current_var;

    current = data->vars;
    data->exit_str = ft_itoa(data->exit_status);
	if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
		return (data->exit_str);
    while (current != NULL)
    {
        current_var = (t_var *)current->content;
        if (ft_strncmp(current_var->var_name, var_name, ft_strlen(var_name)) == 0) {
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

char **expander(char **tokens, t_data *data)
{
	int i;
	int j;
    char *var_name;
    int var_name_length;
	char *var_value;
    int is_in_single_quote;

	i = 0;
	while(tokens[i])
	{
        is_in_single_quote = 0;
		j = 0;
		while(tokens[i][j])
		{
            tokens[i] = find_and_replace_unclosed_quote(tokens[i], '\'');
            tokens[i] = find_and_replace_unclosed_quote(tokens[i], '"');

            if (tokens[i][j] == '\'')
                is_in_single_quote = !is_in_single_quote;
			if (tokens[i][j] == '$' && is_in_single_quote == 0)
			{
                var_name_length = 0;
                while (ft_isalnum(tokens[i][j + 1 +var_name_length]) || tokens[i][j + 1 +var_name_length] == '_') {
                    var_name_length++;
                }
                var_name = malloc(var_name_length * sizeof(char) + 1);
                var_name[0] = '\0';
                ft_strlcpy(var_name, &tokens[i][j + 1], var_name_length + 1);
				var_value = get_env_var_value(data, var_name);
                free(var_name);

                int old_token_len = ft_strlen(&tokens[i][j]);
                int new_token_length = j + (old_token_len - var_name_length - 1);
                if (var_value != NULL)
                    new_token_length += ft_strlen(var_value);
                char *new_token = malloc(new_token_length * sizeof(char) + 1);
                new_token[0] = '\0';
                tokens[i][j] = '\0';
                int current_new_token_length = ft_strlen(tokens[i]);
                ft_strlcat(new_token, tokens[i], current_new_token_length + 1);
                if (var_value != NULL) {
                    current_new_token_length += ft_strlen(var_value);
                    ft_strlcat(new_token, var_value, current_new_token_length + 1);
                }
                current_new_token_length += ft_strlen(&tokens[i][j + 1 + var_name_length]);
                ft_strlcat(new_token, &tokens[i][j + 1 + var_name_length], current_new_token_length + 1);
                free(tokens[i]);
                tokens[i] = new_token;
                if (var_value != NULL)
                    j += ft_strlen(var_value);
			} else {
                j++;
            }
		}
		i++;
	}
    cut_quotes(tokens);
	return (tokens);
}
