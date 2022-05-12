/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phella <phella@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 15:58:31 by phella            #+#    #+#             */
/*   Updated: 2022/05/12 21:05:51 by phella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"

typedef struct s_rules
{
	int				id_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_eat;
	long			last_eat;
	pthread_mutex_t	mutex;
}	t_rules;

typedef struct s_utils
{
	t_rules			*rule;
	long			start_time;
	int				count_lunch;
	int				check_death;
	int				index;
	int				count;
	int				flag;
	pthread_mutex_t	lock;
}	t_utils;

// time_count.c
long	ft_time(void);
void	ft_true_usleep(int time);
// utils.c
void	print_error(char *str);
int		ft_atoi(const char *str);
int		ft_free_thread(t_utils *u, int flag, pthread_t *thread);
// init_rules.c
int		ft_init_ph(t_utils *u, int ac, char **argv);
void	*ft_check_ph(void *control);
int		ft_check_arg(int argc, char **argv);
// start_simulation.c
void	*ft_run_life_cycle(void *control);
void	ft_life_cycle(t_rules *p, t_utils *u, int i);
int		ft_simulation(pthread_t *thread, t_utils *u);
int		main(int argc, char **argv);

#endif