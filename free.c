/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:08:58 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/04 15:33:56 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(pthread_mutex_t *forks, int end)
{
	int	i;

	i = 0;
	while (i <= end)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	free_all(pthread_mutex_t *forks, t_main *main, t_philo *philo)
{
	int	i;

	i = 0;
	if (main)
		pthread_mutex_destroy(&main->mutex);
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
	if (forks)
	{
		while (i < main->nbr_philo)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
		free(forks);
		forks = NULL;
	}
}

int	ft_error_free(pthread_mutex_t *forks, t_main *main,
			t_philo *philo, char *str)
{
	free_all(forks, main, philo);
	ft_print_error(str);
	return (0);
}
