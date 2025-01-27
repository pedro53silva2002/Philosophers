/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:19:34 by peferrei          #+#    #+#             */
/*   Updated: 2025/01/23 12:02:46 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* int mails = 0;
pthread_mutex_t mutex;

void* routine()
{
	int	i;

	i = -1;
	while (++i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main()
{
	pthread_t p1, p2;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
		return (printf("1"), 1);
	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
		return (printf("2"), 2);
	if (pthread_join(p1, NULL) != 0)
		return (printf("3"), 3);
	if (pthread_join(p2, NULL) != 0)
		return (printf("4"), 4);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
} */

int main(int argc, char **argv)
{
	t_philo_main	main;

	ft_checks(argc, argv);
	ft_init_main(&main, argv);
	printf("Philo: %ld\nDeath: %ld\tEat: %ld\tSleep: %ld\n", main.nbr_philos, main.time_to_die, main.time_to_eat, main.time_to_sleep);
	/* int i = -1;
	while (++i < main.nbr_philos)
	{
		printf("Fork %d\n", main.forks[i].fork_id);
	}
	printf("EVERYTHING WENT GOOD\n"); */
	ft_start(&main);
	return (0);
}
