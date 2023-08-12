/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:58:52 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/07/31 15:58:55 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static int	i;
	static char	*s;
	int			start;
	int			j;

	if (str != NULL)
	{
		s = str;
		i = 0;
	}
	start = i;
	while (s[i] != '\0')
	{
		j = 0;
		while (delim[j] != '\0')
		{
			if (s[i] == delim[j])
			{
				s[i] = '\0';
				i = i + 1;
				if (s[start] != '\0')
					return (&s[start]);
				else
				{
					start = i;
					i--;
					break ;
				}
			}
			j++;
		}
		i++;
	}
	s[i] = '\0';
	if (s[start] == '\0')
		return (NULL);
	else
		return (&s[start]);
}
