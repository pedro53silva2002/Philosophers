/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:29:48 by peferrei          #+#    #+#             */
/*   Updated: 2025/01/22 15:59:59 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_int(pthread_mutex_t *mutex, int *var, int value)
{
	ft_mutex_handler(mutex, LOCK);
	*var = value;
	ft_mutex_handler(mutex, UNLOCK);
}

int	ft_get_int(pthread_mutex_t *mutex, int *var)
{
	int	result;

	ft_mutex_handler(mutex, LOCK);
	result = *var;
	ft_mutex_handler(mutex, UNLOCK);
	return (result);
}

void	ft_set_long(pthread_mutex_t *mutex, long *var, long value)
{
	ft_mutex_handler(mutex, LOCK);
	*var = value;
	ft_mutex_handler(mutex, UNLOCK);
}

int	ft_get_long(pthread_mutex_t *mutex, long *var)
{
	int	result;

	ft_mutex_handler(mutex, LOCK);
	result = *var;
	ft_mutex_handler(mutex, UNLOCK);
	return (result);
}

int	ft_philo_finished(t_philo_main *main)
{
	return(ft_get_int(&main->main_mutex, &main->end_program));
}