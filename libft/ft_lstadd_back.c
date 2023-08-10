/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:57:14 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/15 12:57:16 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new1)
{
	t_list	*pos;

	if (*lst == NULL)
		*lst = new1;
	else
	{
		pos = *lst;
		while (pos->next != NULL)
		{
			pos = pos->next;
		}
		pos->next = new1;
	}
}
