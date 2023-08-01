/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:39:25 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/25 14:05:35 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen((char *)s) + 1;
	while (len--)
	{
		if (*(s + len) == (char)c)
			return ((char *)(s + len));
	}
	return (NULL);
}
