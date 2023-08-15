static void	init_variables(unsigned long long	*result, int	*i, int	*sign)
{
	*i = 0;
	*sign = 1;
	*result = 0;
}

long long int	ft_atoi_long(const char *str)
{
	unsigned long  long	result;
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
		if (result > 9223372036854775808u && sign == -1)
			return (-1);
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
	}
	return (result * sign);
}
