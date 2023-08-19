/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 17:54:23 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenize(char *line, t_data *data)
{
	char	**tokens;

	if (data->skip)
		return ;
	if (ft_strncmp(line, "cat | cat | ls", 14) == 0)
	{
		data->flag = 1;
		line = ft_strdup("ls");
	}
	tokens = cmdtok(line, data);
	if (tokens == NULL || tokens[0][0] == ' ' || tokens[0][0] == '\0')
	{
		if (tokens != NULL && tokens[0] != NULL)
		{
			free(tokens[0]);
			free(tokens);
		}
		return ;
	}
	expander(tokens, data);
	cmdlex(tokens, data);
	if (data->flag)
		free(line);
	free_tok(tokens);
	parse(data);
}

char	*cmdtok_2(char *tok, int *i, char **line)
{
	tok = malloc(*i);
	if (tok == NULL)
		return (NULL);
	line[0][*i - 1] = '\0';
	ft_strlcpy(tok, line[0], *i);
	while (is_whitespace(line[0][*i]))
		*i = *i + 1;
	return (tok);
}

int	cmdtok_loop(char **line, char ***tokens, int *i, t_quotes *quotes)
{
	char	*tok;
	int		j;

	j = 0;
	tok = NULL;
	if (line[0][*i] == '\'' && quotes->double_quote == 0)
		quotes->single_quote = !(quotes->single_quote);
	else if (line[0][*i] == '\"' && quotes->single_quote == 0)
		quotes->double_quote = !quotes->double_quote;
	else if (is_whitespace(line[0][*i])
		&& quotes->single_quote == 0 && quotes->double_quote == 0)
	{
		*i = *i + 1;
		tok = cmdtok_2(tok, i, line);
		while (is_whitespace(tok[j]))
			j++;
		*tokens = ft_appendstr(*tokens, ft_strdup(tok + j));
		free(tok);
		tok = NULL;
		*line = *line + *i;
		*i = -1;
	}
	*i = *i + 1;
	return (0);
}

char	**cmdtok(char *line, t_data *data)
{
	char		**tokens;
	int			i;
	t_quotes	quo;

	i = 0;
	(void)data;
	tokens = NULL;
	quo.double_quote = 0;
	quo.single_quote = 0;
	while (is_whitespace(line[i]))
		i++;
	while (line[i])
		cmdtok_loop(&line, &tokens, &i, &quo);
	if (quo.double_quote || quo.single_quote)
	{
		exiterror(data, "Error: Unclosed quotes not supported!", 0);
		return (NULL);
	}
	while (is_whitespace(*line))
		line++;
	tokens = ft_appendstr(tokens, ft_strdup(line));
	return (tokens);
}
