/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:15:20 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/18 11:59:56 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_path(t_data *data)
{
	data->path_env = getenv("PATH");
	return ;
}

t_data	*init_data(t_data *data)
{
	data->append_redirection = 0;
	data->arg_count = 0;
	data->full_tokens = NULL;
	data->input_file = NULL;
	data->input_redirection = 0;
	data->output_file = NULL;
	data->output_redirection = 0;
	data->path_args = NULL;
	data->path_env = NULL;
	data->working_dir = NULL;
	data->builtin = 0;
	data->exit_status = 0;
	data->exit = 0;
	data->exit_arg = 0;
	data->exit_str = NULL;
	data->skip = 0;
	data->cmd_head = 0;
	data->exec_head = 0;
	data->wait_pid = 0;
	fill_path(data);
	return (data);
}
