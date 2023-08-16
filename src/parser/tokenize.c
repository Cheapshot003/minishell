/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:13:56 by otietz            #+#    #+#             */
/*   Updated: 2023/08/13 12:17:32 otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void tokenize(char *line, t_data *data)
{
	if (data->skip)
		return ;
	char **tokens;
	tokens = cmdtok(line, data);
	if (tokens == NULL)
		return ;
	expander(tokens, data);
	cmdlex(tokens, data);
	free_tok(tokens);
	parse(data);
}

char **cmdtok(char *line, t_data *data) {
    char *tok;
    char **tokens;
	int double_quote;
	int	single_quote;
    int i;
	// char *temp;

	// temp = line;
	i = 0;
	(void)data;
	single_quote = 0;
	tokens = NULL;
	double_quote = 0;
	while (is_whitespace(line[i]))
		i++;
	while (line[i])
	{
		if (line[i] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (line[i] == '\"' && single_quote == 0)
			double_quote = !double_quote;
		else if (is_whitespace(line[i]) && single_quote == 0 && double_quote == 0)
		{
			while(is_whitespace(line[i]))
				i++;
			tok = malloc(i);
			if (tok == NULL)
				return (NULL);
			line[i-1] = '\0';
			ft_strlcpy(tok, line, i);
			tokens = ft_appendstr(tokens, ft_strdup(tok));
			free(tok);
			tok = NULL;
			line = line + i;
			i = -1;
		}
		i++;
	}
	if (double_quote || single_quote)
	{
		exiterror(data, "Error: Unclosed quotes not supported!", 0);
		return (NULL);
	}
	tok = ft_strdup(line);
	tokens = ft_appendstr(tokens, ft_strdup(tok));
	free(tok);
	return (tokens);

}

void cmdlex(char **input_tokens, t_data *data)
{
	int i;
	t_cmd *head;
	t_cmd *new;
	int j;
	char *temp;
	char aux[1024];

	temp = NULL;
	head = create_t_cmd();
	data->cmd_head = head;
	new = head;
	i = 0;
	while (input_tokens[i])
	{
		j = 0;
		if (input_tokens[i][0] == '\'' || input_tokens[i][0] == '\"')
		{
			input_tokens[i][ft_strlen(input_tokens[i]) - 1] = '\0'; 
			temp = ft_strdup(input_tokens[i] + 1);
			new->str = temp;
			input_tokens[i][0] = '\0';
		}
		else if(is_special_char(input_tokens[i][0]))
		{
			while (is_special_char(input_tokens[i][j]))
				j++;
			ft_strlcpy(aux, input_tokens[i], j+1);
			temp = ft_strdup(input_tokens[i] + j);
			new->str = ft_strdup(aux);
			free(input_tokens[i]);			
			input_tokens[i] = temp;
		}
		else if (input_tokens[i][0])
		{
			while(input_tokens[i][j] && !is_special_char(input_tokens[i][j]))
				j++;
			ft_strlcpy(aux, input_tokens[i], j+1);
			temp = ft_strdup(input_tokens[i] + j);
			new->str = ft_strdup(aux);
			free(input_tokens[i]);
			input_tokens[i] = temp;
		}
		new = create_t_cmd();
		insert_t_cmd(&head, new);
		if(input_tokens[i][0] == '\0' || input_tokens[i] == NULL)
			i++;
	}
}

int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}