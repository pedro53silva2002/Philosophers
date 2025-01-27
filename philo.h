/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:01:38 by peferrei          #+#    #+#             */
/*   Updated: 2025/01/27 16:30:35 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

#define DEBUG_MODE 0
typedef struct s_philo_main t_philo_main;

typedef enum e_mutex_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
} t_mutex_code;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
} t_time_code;

typedef enum e_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DYING,
} t_philo_state;

typedef struct s_philo_fork
{
	pthread_mutex_t fork;
	int fork_id;
} t_philo_fork;

typedef struct s_philos
{
	int id;
	t_philo_fork *fork_one;
	t_philo_fork *fork_two;
	/* int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep; */
	// bool full;
	pthread_mutex_t philo_mutex;
	int nbr_meals;
	long time_passed;
	pthread_t thread_id;
	t_philo_main *main;
} t_philos;

typedef struct s_philo_main
{
	long nbr_philos;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long min_eatings;
	long start_time;
	long act_thr_run;
	int end_program;
	int threads_start;
	pthread_t checker;
	pthread_mutex_t main_mutex;
	pthread_mutex_t state_mutex;
	t_philo_fork *forks;
	t_philos *philos;
} t_philo_main;

void ft_print_error(char *str);
void ft_print_message(int nbr, int time, char *philo);
int ft_strcmp(char *s1, char *s2);
int ft_isdigit(int c);
int ft_check_args(char **argv);
void ft_checks(int argc, char **argv);
int ft_atol(const char *str);
void ft_init_main(t_philo_main *main, char **argv);
void ft_mutex_handler(pthread_mutex_t *mutex, t_mutex_code code);
void ft_thread_handler(pthread_t *thread, void *(*func)(void *), void *data, t_mutex_code code);
void ft_set_int(pthread_mutex_t *mutex, int *var, int value);
int ft_get_int(pthread_mutex_t *mutex, int *var);
void ft_set_long(pthread_mutex_t *mutex, long *var, long value);
int ft_get_long(pthread_mutex_t *mutex, long *var);
int ft_philo_finished(t_philo_main *main);
void ft_start(t_philo_main *main);

#endif
