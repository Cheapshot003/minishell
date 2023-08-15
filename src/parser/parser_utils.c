#include "../../includes/minishell.h"


int is_special_char(char c) 
{
    return (c == '<' || c == '|' || c == '>' || c == '*');
}

int is_quote(char c) 
{
    return (c == '\'' || c == '\"');
}
int is_redirect(char *str)
{
	if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return (2);
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return (3);
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return (4);
	else
		return (0);
}
int is_empty_string(const char* str) {
    while (*str != '\0') {
        if (!isspace(*str))
            return 0;
        str++;
    }
    return 1;
}

char** remove_empty_strings(char** input_tokens) {
    int non_empty_count = 0;
    int i = 0;
    while (input_tokens[i] != NULL) {
        if (!is_empty_string(input_tokens[i]))
            non_empty_count++;
        i++;
    }
    char** result_tokens = malloc((non_empty_count + 1) * sizeof(char*));
    int j = 0;
    for (i = 0; i < non_empty_count; i++) {
        while (is_empty_string(input_tokens[j]))
            j++;
        result_tokens[i] = strdup(input_tokens[j]);
		free(input_tokens[i]);
        j++;
    }
    result_tokens[non_empty_count] = NULL;
	free(input_tokens);
    return result_tokens;
}