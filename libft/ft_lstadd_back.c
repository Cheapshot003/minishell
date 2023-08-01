/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:57:14 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/15 12:57:16 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*pos;

	if (*lst == NULL)
		*lst = new;
	else
	{
		pos = *lst;
		while (pos->next != NULL)
		{
			pos = pos->next;
		}
		pos->next = new;
	}
}
