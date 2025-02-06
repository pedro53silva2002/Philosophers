/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:30:23 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/04 15:23:57 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	ft_start(t_main *main, t_philo *philo, pthread_mutex_t *fork)
{
	int			i;
	suseconds_t	time;

	i = -1;
	time = ft_get_time();
	while (++i < main->nbr_philo)
	{
		philo[i].start_time = time;
		if (pthread_create(&philo[i].t_id, NULL,
				&ft_dinner_simul, (void *)&philo[i]))
			return (ft_error_free(fork, NULL, philo, "Allocate memory error."));
	}
	i = -1;
	ft_checker(main, philo);
	while (++i < main->nbr_philo)
	{
		if (pthread_join(philo[i].t_id, NULL))
			return (ft_error_free(fork, NULL, philo, "Allocate memory error."));
	}
	return (true);
}

int	ft_checker(t_main *main, t_philo *philo)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (true)
	{
		while (++i < main->nbr_philo)
		{
			if (main->eat_times != -1)
				if (ft_filled(&philo[i]))
					++j;
			if (j == main->nbr_philo && main->eat_times != -1)
				return (ft_end_simul(main));
			if (main-> end_program == 0 && ft_dead_philo(&philo[i]))
			{
				ft_end_simul(main);
				print_status(&philo[i], "died", DEAD);
				return (true);
			}
		}
		i = -1;
	}
	return (true);
}

int	ft_dead_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->mutex);
	if (philo->main->end_program == 0
		&& ft_get_time() - philo->last_meal_time > philo->main->time_to_die)
	{
		philo->main->end_program = 1;
		pthread_mutex_unlock(&philo->main->mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->main->mutex);
	return (false);
}

int	ft_filled(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->mutex);
	if (philo->main->eat_times != -1)
	{
		if (philo->num_eat >= philo->main->eat_times && philo->full == 0)
		{
			philo->full = 1;
			pthread_mutex_unlock(&philo->main->mutex);
			return (true);
		}
	}
	pthread_mutex_unlock(&philo->main->mutex);
	return (false);
}
