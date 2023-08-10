/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:56:39 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/26 10:33:30 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] != c)
		{
			word_count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (word_count);
}

static int	ft_size_word(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i] != '\0')
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

static void	init_variables(int *i, int *j, int	*word_count, char	***strs)
{
	*i = 0;
	*j = -1;
	*strs = (char **)malloc((*word_count + 1) * sizeof(char *));
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word_count;
	char	**strs;
	int		size;
	int		j;

	word_count = ft_count_word(s, c);
	init_variables(&i, &j, &word_count, &strs);
	if (!strs)
		return (NULL);
	while (++j < word_count)
	{
		while (s[i] == c)
			i++;
		size = ft_size_word(s, c, i);
		strs[j] = ft_substr(s, i, size);
		if (!strs[j])
		{
			ft_free(strs, j);
			return (NULL);
		}
		i = i + size;
	}
	strs[j] = NULL;
	return (strs);
}
