/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:33:08 by afavre            #+#    #+#             */
/*   Updated: 2023/01/12 13:15:04 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	action_print(rules, philo->id, "has taken a fork");
	if (rules->nb_philo >= 2)
	{
		pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
		action_print(rules, philo->id, "has taken a fork");
		pthread_mutex_lock(&(rules->meal_check));
		action_print(rules, philo->id, "is eating");
		philo->t_last_meal = timestamp();
		pthread_mutex_unlock(&(rules->meal_check));
		philo_sleep(rules->time_eat, rules);
		(philo->nb_eat)++;
		pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
		pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
	}
	else
	{
		usleep(rules->time_death * 1000);
		action_print(rules, philo->id, "died");
		rules->dieded = 1;
	}
}

void	*p_thread(void *void_philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->dieded))
	{
		philo_eats(philo);
		if (rules->all_ate)
			break ;
		action_print(rules, philo->id, "is sleeping");
		philo_sleep(rules->time_sleep, rules);
		action_print(rules, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	exit_launcher(t_rules *rules, t_philosopher *philos)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
}

void	death_checker(t_rules *rules, t_philosopher *philo)
{
	int	i;

	while (!(rules->all_ate))
	{
		i = -1;
		while (++i < rules->nb_philo && !(rules->dieded))
		{
			pthread_mutex_lock(&(rules->meal_check));
			if (time_diff(philo[i].t_last_meal, \
				timestamp()) > rules->time_death)
			{
				action_print(rules, i, "died");
				rules->dieded = 1;
			}
			pthread_mutex_unlock(&(rules->meal_check));
		}
		if (rules->dieded)
			break ;
		i = 0;
		while (rules->nb_eat != -1 && i < rules->nb_philo \
			&& philo[i].nb_eat >= rules->nb_eat)
			i++;
		if (i == rules->nb_philo)
			rules->all_ate = 1;
	}
}

int	launcher(t_rules *rules)
{
	int				i;
	t_philosopher	*phi;

	i = 0;
	phi = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		phi[i].t_last_meal = timestamp();
		i++;
	}
	death_checker(rules, rules->philosophers);
	exit_launcher(rules, phi);
	return (0);
}
