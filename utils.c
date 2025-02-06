/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:28:43 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/04 15:35:56 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
	{
		return (0);
	}
	return (1);
}

long	ft_atol(const char *str)
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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

void	ft_wait(t_philo *philo, long time)
{
	if ((ft_get_time() + time) >= (long)philo->main->time_to_die
		+ ft_get_time())
		usleep(((long)philo->main->time_to_die) * 999);
	else
		usleep(time * 999);
}
