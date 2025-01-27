/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peferrei <peferrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:17:28 by peferrei          #+#    #+#             */
/*   Updated: 2025/01/21 15:56:55 by peferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_args(char **argv)
{
	int i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return	(0);
		}
		//printf("HERE");
		if (!ft_atol(argv[i]) || ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > INT_MAX)
			return	(0);
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
