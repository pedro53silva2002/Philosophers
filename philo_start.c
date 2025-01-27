/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:47:19 by peferrei          #+#    #+#             */
/*   Updated: 2025/01/27 17:26:46 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_get_time(t_time_code code)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        ft_print_error("Get time failed\n");
    if (code == SECOND)
        return (tv.tv_sec + (tv.tv_usec / 1e6));
    else if (code == MILLISECOND)
        return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
    else if (code == MICROSECOND)
        return ((tv.tv_sec * 1e6) + tv.tv_usec);
    else
        ft_print_error("Invalid time code\n");
    return (1337);
}

void ft_sleep_time(long usec, t_philo_main *main)
{
    long start;
    long passed;
    long remaining;

    start = ft_get_time(MICROSECOND);
    while (ft_get_time(MICROSECOND) - start < usec)
    {
        if (ft_philo_finished(main) == 1)
            break;
        passed = ft_get_time(MICROSECOND) - start;
        remaining = usec - passed;

        if (remaining > 1e3)
            usleep(usec / 2);
        else
        {
            while (ft_get_time(MICROSECOND) - start < usec)
                ;
        }
    }
}

void ft_print_status_debug(t_philo_state status, t_philos *philo, int passed)
{
    if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !ft_philo_finished(philo->main))
        printf("%d %d has taken the first fork %d\n", passed, philo->id, philo->fork_one->fork_id);
    if (status == TAKE_SECOND_FORK && !ft_philo_finished(philo->main))
        printf("%d %d has taken the second fork %d\n", passed, philo->id, philo->fork_two->fork_id);
    else if (status == EATING && !ft_philo_finished(philo->main))
        printf("%d %d is eating %d meals\n", passed, philo->id, philo->nbr_meals);
    else if (status == SLEEPING && !ft_philo_finished(philo->main))
        printf("%d %d is sleeping\n", passed, philo->id);
    else if (status == THINKING && !ft_philo_finished(philo->main))
        printf("%d %d is thinking\n", passed, philo->id);
    else if (status == DYING)
        printf("%d %d died\n", passed, philo->id);
}
void ft_print_status(t_philo_state status, t_philos *philo, int debug)
{
    long passed;

    /* if (philo->nbr_meals == philo->main->min_eatings)
        return; */
    passed = ft_get_time(MILLISECOND);
    ft_mutex_handler(&philo->main->state_mutex, LOCK);
    if (debug == 1)
        ft_print_status_debug(status, philo, passed);
    else
    {
        if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !ft_philo_finished(philo->main))
            printf("%ld %d has taken the fork\n", passed, philo->id);
        else if (status == EATING && !ft_philo_finished(philo->main))
            printf("%ld %d is eating\n", passed, philo->id);
        else if (status == SLEEPING && !ft_philo_finished(philo->main))
            printf("%ld %d is sleeping\n", passed, philo->id);
        else if (status == THINKING && !ft_philo_finished(philo->main))
            printf("%ld %d is thinking\n", passed, philo->id);
        else if (status == DYING)
            printf("%ld %d died\n", passed, philo->id);
    }
    ft_mutex_handler(&philo->main->state_mutex, UNLOCK);
}

void ft_wait_for_threads(t_philo_main *main)
{
    while (ft_get_int(&main->main_mutex, &main->threads_start) == 0)
        ;
}

void ft_think(t_philos *philo)
{
    ft_print_status(THINKING, philo, DEBUG_MODE);
}

void ft_eat(t_philos *philo)
{
    ft_mutex_handler(&philo->fork_one->fork, LOCK);
    ft_print_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    ft_mutex_handler(&philo->fork_two->fork, LOCK);
    ft_print_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
    ft_set_long(&philo->philo_mutex, &philo->time_passed, ft_get_time(MILLISECOND));
    philo->nbr_meals++;
    ft_print_status(EATING, philo, DEBUG_MODE);
    ft_sleep_time(MILLISECOND, philo->main);
    /* if (philo->main->nbr_philos > 0
        && philo->nbr_meals == philo->main->min_eatings)
        ft_set_int(&philo->philo_mutex,&philo->full, 1); */
    ft_mutex_handler(&philo->fork_one->fork, UNLOCK);
    ft_mutex_handler(&philo->fork_two->fork, UNLOCK);
}

void *ft_rounds(void *data)
{
    t_philos *philo;

    philo = (t_philos *)data;
    ft_wait_for_threads(philo->main);
    while (ft_philo_finished(philo->main) == 0)
    {
        if (philo->nbr_meals == philo->main->min_eatings)
            break;

        ft_eat(philo);
        ft_print_status(SLEEPING, philo, DEBUG_MODE);
        ft_sleep_time(philo->main->time_to_sleep, philo->main);
        ft_think(philo);
    }
    return (NULL);
}

void ft_start(t_philo_main *main)
{
    int i;

    i = -1;
    // if (main->min_eatings == 0)
    // return ;
    if (main->nbr_philos == 1)
        return;
    else
    {
        while (++i < main->nbr_philos)
        {
            ft_thread_handler(&main->philos[i].thread_id, ft_rounds, &main->philos[i], CREATE);
        }
    }
    main->start_time = ft_get_time(MILLISECOND);

    ft_set_int(&main->main_mutex, &main->threads_start, 1);
    i = -1;
    while (++i < main->nbr_philos)
        ft_thread_handler(&main->philos[i].thread_id, NULL, NULL, JOIN);
}