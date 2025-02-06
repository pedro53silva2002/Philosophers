/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:35:04 by peferrei          #+#    #+#             */
/*   Updated: 2025/02/04 15:36:43 by peferrei         ###   ########.fr       */
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

void	print_status(t_philo *philo, char *status, t_action action)
{
	long	time;

	pthread_mutex_lock(&philo->main->mutex);
	if (philo->main->end_program == 1 && action != DEAD)
		pthread_mutex_unlock(&philo->main->mutex);
	else if (philo->main->end_program == 0)
	{
		pthread_mutex_unlock(&philo->main->mutex);
		time = ft_get_time() - philo->start_time;
		printf("%ld %d %s\n", time, philo->philo_id, status);
	}
	else if (action == DEAD)
	{
		pthread_mutex_unlock(&philo->main->mutex);
		time = ft_get_time() - philo->start_time;
		printf("%ld %d %s\n", time, philo->philo_id, status);
	}
	else
		pthread_mutex_unlock(&philo->main->mutex);
}
