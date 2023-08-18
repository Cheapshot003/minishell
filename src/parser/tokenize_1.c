/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:48:13 by otietz            #+#    #+#             */
/*   Updated: 2023/08/18 17:53:56 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmdlex_2(char **input_tokens, t_cmd *new, int *i, int *j)
{
	char	*temp;
	char	aux[1024];

	if (is_special_char(input_tokens[*i][0]))
	{
		while (is_special_char(input_tokens[*i][*j]))
			*j = *j + 1;
		ft_strlcpy(aux, input_tokens[*i], *j + 1);
		temp = ft_strdup(input_tokens[*i] + *j);
		new->str = ft_strdup(aux);
		free(input_tokens[*i]);
		input_tokens[*i] = temp;
	}
	else if (input_tokens[*i][0])
	{
		while (input_tokens[*i][*j]
				&& !is_special_char(input_tokens[*i][*j]))
			*j = *j + 1;
		ft_strlcpy(aux, input_tokens[*i], *j + 1);
		cut_quotes(aux);
		temp = ft_strdup(input_tokens[*i] + *j);
		new->str = ft_strdup(aux);
		free(input_tokens[*i]);
		input_tokens[*i] = temp; 
	}
}

void	cmdlex(char **input_tokens, t_data *data)
{
	int		i;
	t_cmd	*new;
	int		j;
	char	*temp;

	data->cmd_head = create_t_cmd();
	new = data->cmd_head;
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
		else
			cmdlex_2(input_tokens, new, &i, &j);
		new = create_t_cmd();
		insert_t_cmd(&(data->cmd_head), new);
		if (input_tokens[i][0] == '\0' || input_tokens[i] == NULL)
			i++;
	}
}
