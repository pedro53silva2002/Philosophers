/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:21:32 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/02/04 15:35:22 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_check_args(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
		}
		if (!ft_atol(argv[i]) || ft_atol(argv[i]) <= 0
			|| ft_atol(argv[i]) > INT_MAX)
			return (0);
	}
	return (1);
}

void	ft_checks(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		ft_print_error("Invalid number of arguments");
	if (!ft_check_args(argv))
		ft_print_error("Invalid input");
	if (ft_atol(argv[1]) > 200)
		ft_print_error("I DON'T HAVE FOOD FOR SO MUCH PEOPLE");
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60
		|| ft_atol(argv[4]) < 60)
		ft_print_error("Give them more time please.");
}

int	ft_end_simul(t_main *main)
{
	pthread_mutex_lock(&main->mutex);
	main->end_program = 1;
	pthread_mutex_unlock(&main->mutex);
	return (1);
}
