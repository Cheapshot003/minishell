/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:13:56 by otietz            #+#    #+#             */
/*   Updated: 2023/08/07 12:35:38 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **tokenize(char *line, t_data *data)
{
	char **tokens;
	char **tokens1;

	tokens = cmdtok(line, data);
	tokens = expander(tokens, data);
	tokens1 = cmdlex(tokens, data);
	tokens1 = remove_empty_strings(tokens1);
	return tokens1;
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

char **cmdlex(char **input_tokens, t_data *data)
{
  char** tokens = malloc((sizeof(input_tokens) / sizeof(input_tokens[0])) * sizeof(char*));
    int token_count = 0;
    int i = 0;

	(void)data;

    while (input_tokens[i] != NULL) {
        char* token = input_tokens[i];
        int token_length = strlen(token);
        int token_index = 0;
        char* current_token = malloc((token_length + 1) * sizeof(char));

        // Process each character of the token
        for (int j = 0; j < token_length; j++) {
            char c = token[j];
            char next_c = token[j + 1];

            // Check if it is a special character outside quotes
            if (j == 0 && is_special_char(c) && !is_quote(c)) {
                // Allocate memory for the special character token and add it to the tokens array
                tokens[token_count] = malloc(2 * sizeof(char));
                tokens[token_count][0] = c;
                tokens[token_count][1] = '\0';
                token_count++;
            } else if (is_special_char(c) && !is_quote(c) && (next_c == '\0' || is_whitespace(next_c) || is_special_char(next_c))) {
                // Add the current token to the tokens array
                current_token[token_index] = '\0';
                tokens[token_count] = current_token;
                token_count++;

                // Allocate memory for the special character token and add it to the tokens array
                tokens[token_count] = malloc(2 * sizeof(char));
                tokens[token_count][0] = c;
                tokens[token_count][1] = '\0';
                token_count++;

                // Reset current_token for the next token
                current_token = malloc((token_length + 1) * sizeof(char));
                token_index = 0;
            } else {
                // Add the character to the current token
                current_token[token_index] = c;
                token_index++;
            }
        }

        // Add the remaining token to the tokens array
        current_token[token_index] = '\0';
        tokens[token_count] = current_token;
        token_count++;

        i++; // Move to the next token
    }

    // Add a NULL pointer at the end of the array to indicate the end of tokens
    tokens[token_count] = NULL;

    return tokens; 
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
        i++; // Move past the quote character
    }
    while (input[i] != '\0' && (quote || !is_whitespace(input[i]))) {
        if (quote && input[i] == quote) {
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