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
