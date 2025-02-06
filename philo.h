/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:02:21 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/04 15:36:26 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	DEFORK,
	DEAD,
	THINK,
}	t_action;

typedef struct s_main
{
	long					nbr_philo;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					eat_times;
	pthread_mutex_t			mutex;
	int						end_program;
}				t_main;

typedef struct s_philo
{
	int					philo_id;
	int					num_eat;
	int					full;
	long				start_time;
	long				last_meal_time;
	pthread_mutex_t		*fork_one;
	pthread_mutex_t		*fork_two;
	pthread_t			t_id;
	t_main				*main;
}			t_philo;

int				ft_init_main(char **argv, t_main *philos);
int				ft_start(t_main *main, t_philo *philo,
					pthread_mutex_t *fork);
void			*ft_dinner_simul(void *v_philo);
void			print_status(t_philo *philo, char *status, t_action action);
int				ft_dead_philo(t_philo *philo);
void			ft_action(t_philo *philo, int action);
long			ft_get_time(void);
int				ft_checker(t_main *main, t_philo *philo);
int				ft_round(t_philo *philo);
int				ft_filled(t_philo *philo);
void			ft_get_forks(t_philo *philo);
void			ft_put_forks(t_philo *philo);
void			ft_wait(t_philo *philo, long time);
int				ft_end_simul(t_main *main);
void			ft_checks(int argc, char **argv);
int				ft_check_args(char **argv);
t_philo			*init_philos(t_main *main, pthread_mutex_t *forks);
pthread_mutex_t	*init_forks(t_main *main);
void			free_forks(pthread_mutex_t *forks, int end);
void			free_all(pthread_mutex_t *forks, t_main *main,
					t_philo *philo);
int				ft_error_free(pthread_mutex_t *forks, t_main *main,
					t_philo *philo, char *err);
long			ft_atol(const char *str);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *str);
void			ft_print_error(char *str);
void			ft_print_message(int nbr, int time, char *philo);

#endif