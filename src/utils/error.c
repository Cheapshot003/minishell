/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:50:09 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/16 10:45:07 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_execerr(t_data *data)
{
	if (errno == EACCES)
	{
		data->exit_status = 126;
		exiterror(data, " Permission denied", 1);
	}
	else if (errno == ENOENT)
	{
		data->exit_status = 127;
		exiterror(data, " No such file or directory", 1);
	}
	else
		exiterror(data, "Error", 1);
}
