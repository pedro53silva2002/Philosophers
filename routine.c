/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:12:47 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/04 17:07:40 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_dinner_simul(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	if (philo->main->nbr_philo == 1)
	{
		print_status(philo, "has taken a fork", FORK);
		return (NULL);
	}
	while (true)
		if (!ft_round(philo))
			break ;
	return (NULL);
}

void	ft_action(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->main->mutex);
	if (philo->main->end_program == 1)
	{
		pthread_mutex_unlock(&philo->main->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->main->mutex);
	if (action == FORK)
		ft_get_forks(philo);
	else if (action == EAT)
	{
		pthread_mutex_lock(&philo->main->mutex);
		philo->last_meal_time = ft_get_time();
		philo->num_eat++;
		if (philo->main->end_program == 1)
		{
			pthread_mutex_unlock(&philo->main->mutex);
			ft_put_forks(philo);
			return ;
		}
		pthread_mutex_unlock(&philo->main->mutex);
	}
	else if (action == DEFORK)
		ft_put_forks(philo);
}

void	ft_get_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->mutex);
	if (philo->main->end_program == 1)
	{
		pthread_mutex_unlock(&philo->main->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->main->mutex);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_two);
		print_status(philo, "has taken a fork", FORK);
		pthread_mutex_lock(philo->fork_one);
		print_status(philo, "has taken a fork", FORK);
	}
	else
	{
		pthread_mutex_lock(philo->fork_one);
		print_status(philo, "has taken a fork", FORK);
		pthread_mutex_lock(philo->fork_two);
		print_status(philo, "has taken a fork", FORK);
	}
}

void	ft_put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_two);
	pthread_mutex_unlock(philo->fork_one);
}

int	ft_round(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->mutex);
	if (philo->main->end_program == 1)
	{
		pthread_mutex_unlock(&philo->main->mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->main->mutex);
	ft_action(philo, FORK);
	ft_action(philo, EAT);
	print_status(philo, "is eating", EAT);
	ft_wait(philo, philo->main->time_to_eat);
	pthread_mutex_lock(&philo->main->mutex);
	if (philo->main->end_program == 1)
	{
		ft_put_forks(philo);
		pthread_mutex_unlock(&philo->main->mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->main->mutex);
	ft_action(philo, DEFORK);
	print_status(philo, "is sleeping", SLEEP);
	ft_wait(philo, philo->main->time_to_sleep);
	print_status(philo, "is thinking", THINK);
	return (true);
}
