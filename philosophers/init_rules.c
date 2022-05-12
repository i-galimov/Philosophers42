/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phella <phella@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:57:57 by phella            #+#    #+#             */
/*   Updated: 2022/05/12 21:07:45 by phella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_ph(t_utils *u, int argc, char **argv)
{
	int	i;

	i = -1;
	u->flag = 0;
	u->check_death = 0;
	u->count = ft_atoi(argv[1]);
	u->rule = malloc(sizeof(t_rules) * u->count);
	if (!u->rule || pthread_mutex_init(&u->lock, NULL) != 0)
		return (1);
	while (++i < u->count)
	{
		if (pthread_mutex_init(&u->rule[i].mutex, NULL) != 0)
			return (1);
		u->rule[i].id_ph = i + 1;
		u->rule[i].time_to_die = ft_atoi(argv[2]);
		u->rule[i].time_to_eat = ft_atoi(argv[3]);
		u->rule[i].time_to_sleep = ft_atoi(argv[4]);
	}
	if (argc == 5)
		return (0);
	u->flag = 1;
	u->count_lunch = ft_atoi(argv[5]);
	return (0);
}

void	*ft_check_ph(void *control)
{
	int		i;
	t_utils	*u;

	u = (t_utils *)control;
	while (1)
	{
		i = -1;
		while (++i < u->count)
		{
			if (ft_time() - u->rule[i].last_eat > u->rule[i].time_to_die)
			{
				u->check_death = 1;
				if (u->flag == 0
					|| (u->flag == 1 && u->rule[i].count_eat > 0))
					printf(RED"%ld %d died\n",
						ft_time() - u->start_time, u->rule[i].id_ph);
				return ((void *)0);
			}
		}
	}
}

int	ft_check_arg(int c_arg, char **v_arg)
{
	if ((c_arg != 5 && c_arg != 6) || ft_atoi(v_arg[1]) <= 0
		|| ft_atoi(v_arg[2]) < 60 || ft_atoi(v_arg[3]) < 60
		|| ft_atoi(v_arg[4]) < 60 || (c_arg == 6 && ft_atoi(v_arg[5]) <= 0))
	{
		print_error("ARG_VALUE_ERROR");
		return (1);
	}
	else
		return (0);
}
