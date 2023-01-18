/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 07:44:40 by afavre            #+#    #+#             */
/*   Updated: 2023/01/06 16:37:52 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int					id;
	int					nb_eat;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					dieded;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[200];
	pthread_mutex_t		writing;
	t_philosopher		philosophers[200];
}						t_rules;

// error_handler.c
int			write_error(char *msg);
int			error_manager(int error);

// initialisation.c
int			init_rules(t_rules *rules, char **av);

// run.c
int			launcher(t_rules *rules);

//utils.c
int			ft_atoi(const char *str);
void		action_print(t_rules *rules, int id, char *string);
long long	timestamp(void);
void		philo_sleep(long long time, t_rules *rules);
long long	time_diff(long long past, long long pres);

// str_utils
void		ft_putstr(char *str);

#endif