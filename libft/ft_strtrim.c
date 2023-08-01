/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:18:47 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/23 14:28:53 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	s1_len = ft_strlen(s1);
	while (ft_strchr(set, s1[s1_len]) && s1_len != 0)
		s1_len--;
	return (ft_substr(s1, 0, s1_len + 1));
}
