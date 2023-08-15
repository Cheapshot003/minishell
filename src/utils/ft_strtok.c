/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:58:52 by ohnatiuk          #+#    #+#             */
/*   Updated: 2023/07/31 15:58:55 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_delim(const char *delim, char *s, int *i, int *start)
{
	int	j;

	j = 0;
	while (delim[j] != '\0')
	{
		if (s[*i] == delim[j])
		{
			s[*i] = '\0';
			*i = *i + 1;
			if (s[*start] != '\0')
				return (1);
			else
			{
				*start = *i;
				*i = *i - 1;
				break ;
			}
		}
		j++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static int	i;
	static char	*s;
	int			start;

	if (str != NULL)
	{
		s = str;
		i = 0;
	}
	start = i;
	while (s[i] != '\0')
	{
		if (check_delim(delim, s, &i, &start) == 1)
			return (&s[start]);
		i++;
	}
	s[i] = '\0';
	if (s[start] == '\0')
		return (NULL);
	else
		return (&s[start]);
}
