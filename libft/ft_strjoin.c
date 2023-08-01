/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:43:35 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/23 15:06:34 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	len;

	if (!s1 || !s2)
	{
		return (NULL);
	}
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = malloc(len);
	if (newstr == NULL)
		return (NULL);
	newstr[0] = '\0';
	ft_strlcat(newstr, s1, ft_strlen(s1) + 1);
	ft_strlcat(newstr, s2, len);
	return (newstr);
}
