/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:35:22 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/11 13:01:24 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	void	*dest;

	dest = malloc(ft_strlen(s) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy((char *)dest, s, ft_strlen(s) + 1);
	return (dest);
}
