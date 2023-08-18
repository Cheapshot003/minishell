/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 17:08:28 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect1(
	t_exec	**current_exec,
	t_cmd	**current_cmd
)
{
	if ((*current_exec)->output_file != NULL)
		free((*current_exec)->output_file);
	(*current_exec)->input_redirection = 1;
	(*current_exec)->input_file = ft_strdup(
			(*current_cmd)->next->str);
}

void	redirect2(
	t_exec	**current_exec,
	t_cmd	**current_cmd
)
{
	if ((*current_exec)->output_file != NULL)
		free((*current_exec)->output_file);
	(*current_exec)->output_redirection = 1;
	(*current_exec)->output_file = ft_strdup(
			(*current_cmd)->next->str);
}

void	redirect3(
	t_exec	**current_exec,
	t_cmd	**current_cmd
)
{
	(*current_exec)->heredoc->numheredoc += 1;
	(*current_exec)->heredoc->delims = ft_appendstr(
			(*current_exec)->heredoc->delims, ft_strdup(
				(*current_cmd)->next->str));
}

void	redirect4(
	t_exec	**current_exec,
	t_cmd	**current_cmd
)
{
	if ((*current_exec)->output_file != NULL)
		free((*current_exec)->output_file);
	(*current_exec)->append_redirection = 1;
	(*current_exec)->output_file = ft_strdup(
			(*current_cmd)->next->str);
}

void	check_redirects(
	t_exec	**current_exec,
	t_cmd	**current_cmd,
	int redirect
)
{
	if (redirect == 1)
		redirect1(current_exec, current_cmd);
	else if (redirect == 2)
		redirect2(current_exec, current_cmd);
	else if (redirect == 3)
		redirect3(current_exec, current_cmd);
	else if (redirect == 4)
		redirect4(current_exec, current_cmd);
}
