/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:24:48 by peferrei          #+#    #+#             */
/*   Updated: 2025/01/27 17:27:21 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_mutex_error_handler(int status, t_mutex_code code)
{
	if (!status)
		return;
	if (status == EINVAL && (code == LOCK || code == UNLOCK))
		ft_print_error("Invalid value by mutex.\n");
	else if (status == EINVAL && code == INIT)
		ft_print_error("Invalid value by attr.\n");
	else if (status == EDEADLK)
		ft_print_error("Thread blocked waiting for mutex.\n");
	else if (status == EPERM)
		ft_print_error("Thread does not hold a lock on mutex.\n");
	else if (status == ENOMEM)
		ft_print_error("Process cannot allocate enough memory to create mutext.\n");
	else if (status == EBUSY)
		ft_print_error("Mutex is locked.\n");
}

void ft_mutex_handler(pthread_mutex_t *mutex, t_mutex_code code)
{
	if (code == LOCK)
		ft_mutex_error_handler(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		ft_mutex_error_handler(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		ft_mutex_error_handler(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		ft_mutex_error_handler(pthread_mutex_destroy(mutex), code);
	else
		ft_print_error("Wrong code for mutex handler");
}

void ft_thread_error_handler(int status, t_mutex_code code)
{
	if (!status)
		return;
	if (status == EAGAIN)
		ft_print_error("No resources to create another thread\n");
	else if (status == EPERM)
		ft_print_error("No permission\n");
	else if (status == EINVAL && code == CREATE)
		ft_print_error("Invalid value by attr.\n");
	else if (status == EDEADLK)
		ft_print_error("Deadlock detected\n");
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		ft_print_error("Value by thread not joinable.\n");
	else if (status == ESRCH)
		ft_print_error("No thread found\n");
}

void ft_thread_handler(pthread_t *thread, void *(*func)(void *), void *data, t_mutex_code code)
{
	if (code == CREATE)
		ft_thread_error_handler(pthread_create(thread, NULL, func, data), code);
	else if (code == JOIN)
		ft_thread_error_handler(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		ft_thread_error_handler(pthread_detach(*thread), code);
	else
		ft_print_error("Wrong code for mutex handler");
}