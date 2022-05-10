/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phella <phella@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:58:58 by phella            #+#    #+#             */
/*   Updated: 2022/05/08 16:02:11 by phella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *str)
{
	printf("%s\n", str);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long long	res;

	i = 0;
	res = 0;
	neg = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		print_error("ARG_NUM_ERROR");
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + neg * (str[i] - 48);
		i++;
		if (res > 2147483647 || res < -2147483648)
			print_error("ARG_NUM_OVERFLOW_ERROR");
	}
	return (res);
}

int	ft_free_thread(t_utils *o, int flag, pthread_t *thread)
{
	int	i;

	i = -1;
	if (o->rule)
	{
		while (++i < o->count - 1)
			pthread_mutex_destroy(&(o->rule[i].mutex));
		free(o->rule);
		if (thread)
			free(thread);
		if (flag == 0)
			return (0);
		print_error("ERROR_WE_FREE_MEMORY");
	}
	return (1);
}
