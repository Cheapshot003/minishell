/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:39:02 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/07 15:39:04 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char )c)
			return ((char *)s);
		s++;
	}
	if (*s == (char )c && *s == '\0')
		return ((char *)s);
	return (NULL);
}
