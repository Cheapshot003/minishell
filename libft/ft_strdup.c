/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otietz <otietz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:35:22 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/08/12 09:37:50 by otietz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	void	*dest;

	dest = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy((char *)dest, s, ft_strlen(s) + 1);
	return (dest);
}
