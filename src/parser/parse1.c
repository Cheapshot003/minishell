/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 17:07:16 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_hdoc	*get_hdoc(void)
{
	t_hdoc	*out;

	out = malloc(sizeof(t_hdoc));
	out->delims = NULL;
	out->numheredoc = 0;
	out->stuff = NULL;
	return (out);
}

void	check_end(
	t_exec **current_exec,
	t_cmd **current_cmd,
	int *done
)
{
	if ((*current_cmd) == NULL || (*current_cmd)->str == NULL)
		*done = 1;
	else
	{
		*current_exec = (*current_exec)->next;
		*current_cmd = (*current_cmd)->next;
	}
}

void	init_vars_3(
	int *i
)
{
	*i = 0;
}

void	delete_commands(t_cmd **head_cmd, int i, t_cmd **current_cmd)
{
	delete_t_cmd_at_index(head_cmd, i + 1);
	delete_t_cmd_at_index(head_cmd, i);
	(*current_cmd) = *head_cmd;
}

void	free_tok(char **tokens)
{
	int	i;

	i = getarrlen(tokens);
	while (i >= 0)
	{
		free(tokens[i]);
		i--;
	}
	free(tokens);
	return ;
}
