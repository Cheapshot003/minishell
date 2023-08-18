/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillredirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 14:40:19 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_is_not_null_or_special(char *str)
{
	return (str == NULL || is_special_char(str[0]));
}

void	fillredirects_iterate(t_cmd	**current_cmd, int *i)
{
	(*current_cmd) = (*current_cmd)->next;
	*i = *i + 1;
}

int	str_is_pipe(char *str)
{
	return (ft_strncmp(str, "|",
			ft_strlen(str)) != 0);
}

void	fillredirects2(
	t_cmd	**head_cmd,
	t_exec	**current_exec,
	t_cmd	**current_cmd,
	int *done
)
{
	int		i;
	int		redirect;

	init_vars_3(&i, &redirect);
	while (*done == 0 && *current_cmd)
	{
		while ((*current_cmd)->str != NULL)
		{
			if (str_is_pipe((*current_cmd)->str))
			{
				redirect = is_redirect((*current_cmd)->str);
				if (redirect > 0)
				{
					if (str_is_not_null_or_special((*current_cmd)->next->str))
						return ;
					check_redirects(current_exec, current_cmd, &redirect);
					delete_commands(head_cmd, i, current_cmd);
					i--;
					continue ;
				}
			}
			else
				*current_exec = (*current_exec)->next;
			fillredirects_iterate(current_cmd, &i);
		}
		check_end(current_exec, current_cmd, done);
	}
}

void	fillredirects(t_exec *head, t_data *data)
{
	t_cmd	*head_cmd;
	t_exec	*current_exec;
	t_cmd	*current_cmd;
	int		done;

	current_exec = head;
	head_cmd = data->cmd_head;
	current_cmd = head_cmd;
	done = 0;
	fillredirects2(&head_cmd, &current_exec, &current_cmd, &done);
	data->cmd_head = head_cmd;
}
