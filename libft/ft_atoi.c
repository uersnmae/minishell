/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dong-hki <dong-hki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:12:01 by dong-hki          #+#    #+#             */
/*   Updated: 2024/10/01 17:12:01 by dong-hki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long	result;
	int		neg_flag;
	int		index;

	result = 0;
	neg_flag = 1;
	index = 0;
	while (((str[index] >= 9 && str[index] <= 13) || str[index] == ' '))
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index++] == '-')
			neg_flag *= -1;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		if (result * 10 + (str[index] - '0') > 2147483648 && neg_flag == -1)
			return (-2147483648);
		if (result * 10 + (str[index] - '0') > 2147483647 && neg_flag == 1)
			return (2147483647);
		result = result * 10 + (str[index] - '0');
		index++;
	}
	return ((int)result * neg_flag);
}
