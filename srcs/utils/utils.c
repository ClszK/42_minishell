#include "minishell.h"

int	ps_move_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

long	ft_atol(char *str, int *flag)
{
	int		i;
	int		sign;
	long	result;
	long	tmp;

	sign = 1;
	result = 0;
	i = ps_move_sign(str, &sign);
	if (!str[i--])
		*flag = 1;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			*flag = 1;
		tmp = result;
		result = (result * 10) + (str[i] - '0');
		if (tmp > result)
			*flag = 1;
	}
	result *= sign;
	return (result);
}
