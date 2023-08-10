/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohnatiuk <ohnatiuk@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:56:52 by ohnatiuk          #+#    #+#             */
/*   Updated: 2022/10/23 16:33:47 by ohnatiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	init_variables(long	*result, int	*i, int	*sign)
{
	*i = 0;
	*sign = 1;
	*result = 0;
}

int	ft_atoi(const char *str)
{
	long	result;
	int		i;
	int		sign;

	init_variables(&result, &i, &sign);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		if (result > 2147483648 && sign == -1)
			return (0);
		if (result > 2147483647 && sign == 1)
			return (-1);
	}
	return (result * sign);
}
