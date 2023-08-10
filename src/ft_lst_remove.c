/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 07:23:17 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/04 07:23:19 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cmp(void *a, void *b)
{
	if (ft_strncmp(((t_var *)a)->var_name,
			((t_var *)b)->var_name, ft_strlen(((t_var *)a)->var_name) + 1) == 0)
		return (0);
	return (1);
}

t_list	*ft_lst_remove(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*previous;
	t_list	*iter;
	int		i;

	i = 0;
	iter = *begin_list;
	while (iter != NULL)
	{
		if (cmp(iter->content, data_ref) == 0)
		{
			if (i == 0)
				*begin_list = iter->next;
			else
				previous->next = iter->next;
			return (iter);
		}
		else
			previous = iter; 
		iter = iter->next; 
		i++;
	}
	return (NULL);
}
