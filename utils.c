/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:17:42 by peferrei          #+#    #+#             */
/*   Updated: 2025/01/21 15:17:44 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_error(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	ft_print_message(int nbr, int time, char *philo)
{
	if (nbr == 1)
		printf("%d %s has taken a fork\n", time, philo);
	else if (nbr == 2)
		printf("%d %s is eating\n", time, philo);
	else if (nbr == 3)
		printf("%d %s is sleeping\n", time, philo);
	else if (nbr == 4)
		printf("%d %s is thinking\n", time, philo);
	else if (nbr == 5)
		printf("%d %s died\n", time, philo);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
	{
		return (0);
	}
	return (1);
}

int	ft_atol(const char *str)
{
	long	number;
	long	minus;
	long	signals;

	number = 0;
	minus = 1;
	signals = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		minus *= -1;
	if (*str == '+' || *str == '-')
	{
		if (signals > 1)
			return (number * minus);
		signals += 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	return (number * minus);
}