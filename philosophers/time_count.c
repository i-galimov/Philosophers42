/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phella <phella@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:58:49 by phella            #+#    #+#             */
/*   Updated: 2022/05/08 16:03:59 by phella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_true_usleep(int time)
{
	long	end;
	long	start;

	start = ft_time();
	end = start + time;
	while (start < end)
	{
		usleep(500);
		start = ft_time();
	}
}
