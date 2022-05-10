/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phella <phella@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:58:39 by phella            #+#    #+#             */
/*   Updated: 2022/05/10 18:16:45 by phella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_run_life_cycle(void *control)
{
	int		i;
	t_utils	*u;

	u = (t_utils *)control;
	i = u->index;
	u->rule[i].count_eat = u->count_lunch;
	u->rule[i].last_eat = ft_time();
	while (u->check_death != 1)
	{
		if (u->flag == 1 && u->rule[i].count_eat == 0)
			return ((void *)0);
		if (u->rule[i].id_ph == 1)
			pthread_mutex_lock(&u->rule[u->count - 1].mutex);
		else
			pthread_mutex_lock(&u->rule[i - 1].mutex);
		if (u->check_death == 0)
			printf("%ld %d has taken a fork\n",
				ft_time() - u->start_time, u->rule[i].id_ph);
		pthread_mutex_lock(&u->rule[i].mutex);
		if (u->check_death == 0)
			printf("%ld %d has taken a fork\n",
				ft_time() - u->start_time, u->rule[i].id_ph);
		ft_life_cycle(&u->rule[i], u, i);
	}
	return ((void *)0);
}

void	ft_life_cycle(t_rules *p, t_utils *u, int i)
{
	pthread_mutex_lock(&u->lock);
	p->last_eat = ft_time();
	if (u->check_death == 0)
		printf("%ld %d is eating\n", ft_time() - u->start_time, p->id_ph);
	pthread_mutex_unlock(&u->lock);
	ft_true_usleep(p->time_to_eat);
	if (p->id_ph == 1)
		pthread_mutex_unlock(&u->rule[u->count - 1].mutex);
	else
		pthread_mutex_unlock(&u->rule[i - 1].mutex);
	pthread_mutex_unlock(&u->rule[i].mutex);
	pthread_mutex_lock(&u->lock);
	if ((u->flag == 0 && u->check_death == 0)
		|| (u->check_death == 0 && u->flag == 1 && p->count_eat != 1))
		printf("%ld %d is sleeping\n", ft_time() - u->start_time, p->id_ph);
	pthread_mutex_unlock(&u->lock);
	ft_true_usleep(p->time_to_sleep);
	pthread_mutex_lock(&u->lock);
	if ((u->flag == 0 && u->check_death == 0)
		|| (u->check_death == 0 && u->flag == 1 && p->count_eat != 1))
		printf("%ld %d is thinking\n", ft_time() - u->start_time, p->id_ph);
	pthread_mutex_unlock(&u->lock);
	p->count_eat--;
}

int	ft_simulation(pthread_t *thread, t_utils *u)
{
	u->index = -1;
	u->start_time = ft_time();
	while (++u->index < u->count)
		u->rule[u->index].last_eat = u->start_time;
	u->index = 0;
	while (u->index < u->count)
	{
		if (pthread_create(&thread[u->index], NULL, ft_run_life_cycle, u) != 0)
			return (1);
		usleep(50);
		u->index += 2;
	}
	u->index = 1;
	while (u->index < u->count)
	{
		if (pthread_create(&thread[u->index], NULL, ft_run_life_cycle, u) != 0)
			return (1);
		usleep(50);
		u->index += 2;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_utils		u;
	pthread_t	control;
	pthread_t	*thread;

	if (ft_check_arg(argc, argv))
		return (1);
	if (ft_init_ph(&u, argc, argv))
		return (1);
	thread = malloc(sizeof(pthread_t *) * u.count);
	if (!thread || pthread_create(&control, NULL, ft_check_ph, &u)
		|| ft_simulation(thread, &u))
	{
		ft_free_thread(&u, 1, 0);
		return (1);
	}
	u.index = 0;
	while (u.index < u.count && u.count > 1)
		pthread_join(thread[u.index++], NULL);
	pthread_join(control, NULL);
	ft_free_thread(&u, 0, thread);
	return (0);
}
