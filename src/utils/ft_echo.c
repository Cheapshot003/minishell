/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/12 08:29:26 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_data *data, char **tokens)
{
	int	with_newline;
	int	i;

	with_newline = 1;
	i = 1;
	if (data->arg_count > 1)
	{
		if (ft_strncmp(tokens[i], "-n", 3) == 0)
		{
			with_newline = 0;
			i++;
		}
		while (i < data->arg_count)
		{
			printf("%s", tokens[i]);
			if (i != data->arg_count - 1)
				printf(" ");
			i++;
		}
		if (with_newline)
			printf("\n");
	}
	else
		printf("\n");
	return (0);
}
