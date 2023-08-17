/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:21:55 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/12 08:29:26 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_vars(t_list *lst)
{
	while (lst != NULL)
	{
		printf ("%s=", ((t_var *)lst->content)->var_name);
		if (((t_var *)lst->content)->var_value != NULL)
			printf("%s", ((t_var *)lst->content)->var_value);
		printf("\n");
		lst = lst->next;
	}
}

int	ft_env(t_data *data, char **tokens)
{
	if (getarrlen(tokens) == 1)
	{
		print_env_vars(data->vars);
		return (0);
	}
	ft_putstr_fd("minishell: env: too many arguments\n", 2);
	return (1);
}
