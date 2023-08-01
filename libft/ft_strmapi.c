/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:15:20 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/23 14:57:44 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	res = (char *)malloc(ft_strlen(s) + 1);
	if (res == NULL)
		return (NULL);
	while (i < (ft_strlen(s)))
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
