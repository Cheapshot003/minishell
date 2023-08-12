/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:13:56 by otietz            #+#    #+#             */
/*   Updated: 2023/08/12 17:05:20 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void tokenize(char *line, t_data *data)
{
	char **tokens;

	tokens = cmdtok(line, data);
	tokens = expander(tokens, data);
	cmdlex(tokens, data);
	free_tok(tokens);
	parse(data);
}

char **cmdtok(char *line, t_data *data) {
    char *tok;
    char **tokens;
    int tokens_capacity; // Current capacity of the tokens array
    int i;

	(void)data;
    i = 0;
    tokens_capacity = 10;
    tokens = malloc(tokens_capacity * sizeof(char *));
    while (*line != '\0') {
        tok = getnexttoken(line);
        if (tok == NULL)
            break;
        if (i == tokens_capacity) {
            tokens_capacity *= 2;
            char** temp = malloc(tokens_capacity * sizeof(char *));
            ft_memcpy(temp, tokens, i * sizeof(char *));
            free(tokens);
            tokens = temp;
        }
        tokens[i] = strdup(tok);
		if (tok != NULL)
			free(tok);
        i++;
    }
    tokens[i] = NULL;
    return tokens;
}

void cmdlex(char **input_tokens, t_data *data)
{
	int i;
	t_cmd *head;
	t_cmd *new;
	int j;
	char *temp;
	char aux;

	temp = NULL;
	head = create_t_cmd();
	data->cmd_head = head;
	new = head;
	j = 0;
	i = 0;
	while (input_tokens[i])
	{
		j = 0;	
		if (is_special_char(input_tokens[i][0]))
		{
			while (is_special_char(input_tokens[i][j]))
				j++;
			if ((input_tokens[i][0] == '|' && j > 1) || input_tokens[i][0] == '*')
			{
				exiterror(data, "ERROR: Unsupported stuff detected. pls don't use || or *     :3", 0);
				return ;
			}
			new->str = ft_calloc((sizeof(char *) * j) + 1, sizeof(char));
			ft_strlcpy(new->str, input_tokens[i], j+1);
			new = create_t_cmd();
			insert_t_cmd(&head, new);
			if (j > 0)
			{
				temp = strdup(input_tokens[i] + j);
				free(input_tokens[i]);
				input_tokens[i] = temp;
				j--;
			}
		}
		else
		{
			while(input_tokens[i][j] &&!is_special_char(input_tokens[i][j]))
				j++;
			aux = input_tokens[i][j];
			input_tokens[i][j] = '\0';
			temp = strdup(input_tokens[i]);
			new->str = temp;
			new = create_t_cmd();
			insert_t_cmd(&head, new);
			input_tokens[i][j] = aux;
			temp = strdup(input_tokens[i] + j);
			free(input_tokens[i]);
			input_tokens[i] = temp;
		}
		if (input_tokens[i][0] == '\0')
			i++;
	}
}

int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

char* getnexttoken(char *input) {
    static char buffer[1024]; // Buffer to hold the extracted token
    int buffer_index; // Index to track the position in the buffer
    int quote; // Flag to indicate if we are inside a quote
    int i; // Index to traverse the input string
	int j;

	i = 0;
	quote = 0;
	buffer_index = 0;
    while (is_whitespace(input[i]))
        i++;
    if (input[i] == '\'' || input[i] == '\"') {
        quote = input[i];
				buffer[buffer_index++] = input[i];
        i++; // Move past the quote character
    }
    while (input[i] != '\0' && (quote || !is_whitespace(input[i]))) {
        if (quote && input[i] == quote) {
						buffer[buffer_index++] = input[i];
            quote = 0; // Reset the quote flag
            i++; // Move past the closing quote character
            break;
        }
        buffer[buffer_index++] = input[i];
        i++;
    }

    buffer[buffer_index] = '\0';
    j = 0;
    while (input[i] != '\0') {
        input[j++] = input[i++];
    }
    input[j] = '\0';
    return ft_strdup(buffer);
}