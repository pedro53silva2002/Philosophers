/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:02:15 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/04 15:09:28 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_main			main;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	ft_checks(argc, argv);
	if (!(ft_init_main(argv, &main)))
		return (1);
	forks = init_forks(&main);
	philo = init_philos(&main, forks);
	if (!ft_start(&main, philo, forks))
		return (1);
	free_all(forks, &main, philo);
	return (1);
}
