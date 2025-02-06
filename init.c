/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:52:03 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/04 15:33:19 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_main *main, pthread_mutex_t *forks)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(main->nbr_philo * sizeof(t_philo));
	if (!philo)
		ft_error_free(forks, main, philo, "Allocate memory error");
	while (++i < main->nbr_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].num_eat = 0;
		philo[i].fork_one = &forks[i];
		philo[i].fork_two = &forks[(i + 1) % main->nbr_philo];
		philo[i].last_meal_time = ft_get_time();
		philo[i].main = main;
		philo[i].full = 0;
	}
	return (philo);
}

pthread_mutex_t	*init_forks(t_main *main)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(main->nbr_philo * sizeof(pthread_mutex_t));
	if (!forks)
		ft_error_free(forks, main, NULL, "Allocate memory error");
	while (i < main->nbr_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free_forks(forks, i);
			ft_error_free(forks, main, NULL, "Error in mutex");
		}
		i++;
	}
	return (forks);
}

int	ft_init_main(char **argv, t_main *main)
{
	main->nbr_philo = ft_atol(argv[1]);
	main->time_to_die = ft_atol(argv[2]);
	main->time_to_eat = ft_atol(argv[3]);
	main->time_to_sleep = ft_atol(argv[4]);
	main->eat_times = -1;
	if (argv[5])
		main->eat_times = ft_atol(argv[5]);
	if (main->nbr_philo == 0 || main->eat_times == 0
		|| main->time_to_die == 0)
		return (false);
	if (pthread_mutex_init(&(main->mutex), NULL) != 0)
	{
		ft_error_free(NULL, main, NULL, "Error in mutex");
		return (0);
	}
	main->end_program = 0;
	return (1);
}
