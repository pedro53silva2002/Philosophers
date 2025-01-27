/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:17:20 by peferrei          #+#    #+#             */
/*   Updated: 2025/01/23 12:02:03 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_select_forks(t_philos *philo, t_philo_fork *forks, int i)
{
	/* philo->right_fork = &forks[i]; 
	if ((i + 1) == philo->main->nbr_philos)
		philo->left_fork = &forks[0];
	else
		philo->right_fork = &forks[i + 1]; */
	/* philo->fork_one = &forks[(i + 1) % philo->main->nbr_philos]; 
	philo->fork_two = &forks[i]; */
	if (philo->id % 2 == 0)
	{
		philo->fork_one = &forks[i]; 
		philo->fork_two = &forks[(i + 1) % philo->main->nbr_philos];	
	}
	else
	{
		philo->fork_one = &forks[(i + 1) % philo->main->nbr_philos]; 
		philo->fork_two = &forks[i];
	}
}

void	ft_init_philos(t_philo_main *main)
{
	int			i;
	t_philos	*philo;

	i = -1;
	while (++i < main->nbr_philos)
	{
		philo = main->philos + i;
		philo->id = i + 1;
		philo->nbr_meals = 0;
		philo->main = main;
		philo->time_passed = 0;
		ft_mutex_handler(&philo->philo_mutex, INIT);
		ft_select_forks(philo, main->forks, i);
	}
}

void	ft_init_main(t_philo_main *main, char **argv)
{
	int	i;

	i = -1;
	main->nbr_philos = ft_atol(argv[1]);
	main->time_to_die = ft_atol(argv[2]) * 1e3;
	main->time_to_eat = ft_atol(argv[3]) * 1e3;
	main->time_to_sleep = ft_atol(argv[4]) * 1e3;
	main->threads_start = 0;
	main->act_thr_run = 0;
	if (argv[5])
		main->min_eatings = ft_atol(argv[5]);
	else
		main->min_eatings = -1;
	ft_mutex_handler(&main->main_mutex, INIT);
	ft_mutex_handler(&main->state_mutex, INIT);
	main->end_program = 0;
	main->philos = malloc(sizeof(t_philos) * main->nbr_philos);
	if (!main->philos)
		ft_print_error("Malloc went wrong.\n");
	main->forks = malloc(sizeof(t_philo_fork) * main->nbr_philos);
	if (!main->forks)
		ft_print_error("Malloc went wrong.\n");
	while(++i < main->nbr_philos)
	{
		ft_mutex_handler(&main->forks[i].fork, INIT);
		main->forks[i].fork_id = i;
	}
	ft_init_philos(main);
}

