/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:56:15 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/15 12:56:18 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new1)
{
	if (*lst == NULL)
	{
		new1->next = NULL;
		*lst = new1;
	}
	else
	{
		new1->next = *lst;
		*lst = new1;
	}
}
