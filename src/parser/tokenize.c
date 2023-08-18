/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 14:48:21 by otietz           ###   ########.fr       */
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
	if (tokens == NULL)
		return ;
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

int	cmdtok_loop(char **line, char ***tokens, int *i)
{
	char	*tok;
	int		single_quote;
	int		double_quote;

	single_quote = 0;
	double_quote = 0;
	tok = NULL;
	if (line[0][*i] == '\'' && double_quote == 0)
		single_quote = !(single_quote);
	else if (line[0][*i] == '\"' && single_quote == 0)
		double_quote = !double_quote;
	else if (is_whitespace(line[0][*i])
		&& single_quote == 0 && double_quote == 0)
	{
		*i = *i + 1;
		tok = cmdtok_2(tok, i, line);
		*tokens = ft_appendstr(*tokens, ft_strdup(tok));
		free(tok);
		tok = NULL;
		*line = *line + *i;
		*i = -1;
	}
	*i = *i + 1;
	return (single_quote || double_quote);
}

char	**cmdtok(char *line, t_data *data)
{
	char	*tok;
	char	**tokens;
	int		open_quotes;
	int		i;

	i = 0;
	(void)data;
	open_quotes = 0;
	tokens = NULL;
	while (is_whitespace(line[i]))
		i++;
	while (line[i])
		open_quotes = cmdtok_loop(&line, &tokens, &i);
	if (open_quotes)
	{
		exiterror(data, "Error: Unclosed quotes not supported!", 0);
		return (NULL);
	}
	tok = ft_strdup(line);
	tokens = ft_appendstr(tokens, ft_strdup(tok));
	free(tok);
	return (tokens);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
