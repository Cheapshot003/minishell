/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/16 10:45:07 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env(t_data *data, char *token)
{
	int		i;
	char	name[1024];
	char	*value;

	i = 0;
	while (token[i] && !is_whitespace(token[i])
		&& !is_special_char(token[i]) && !is_quote(token[i]))
		i++;
	ft_strlcpy (name, token, i + 1);
	value = get_env_var_value(data, name);
	return (value);
}

char	*get_rest(char *rest)
{
	int	i;

	i = 0;
	while (rest[i] && !is_whitespace(rest[i])
		&& !is_quote(rest[i]) && !is_special_char(rest[i]))
		i++;
	if (rest[i])
		return (ft_strdup(rest + i));
	else
		return (NULL);
}

void	expander(char **tokens, t_data *data)
{
	int		i;
	int		j;
	char	temp[1024];
	char	*rest;
	char	*env;
	int		single_quotes;

	single_quotes = 0;
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
				if (tokens[i][j] == '\'')
					single_quotes = !single_quotes;
				if (tokens[i][j] == '$' && (tokens[i][j + 1]
						&& !is_whitespace(tokens[i][j]) && !single_quotes))
				{
					tokens[i][j] = '\0';
					rest = get_rest(tokens[i] + j + 1);
					ft_strlcpy(temp, tokens[i], ft_strlen(tokens[i]) + 1);
					env = get_env(data, tokens[i] + j + 1);
					if (env != NULL)
						ft_strlcat (temp, env, (
								ft_strlen(temp) + ft_strlen(env) + 1));
					if (rest != NULL)
					{
						ft_strlcat (temp, rest,
							ft_strlen(temp) + ft_strlen(rest) + 1);
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
	int	i;
	int	j;

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
