/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:39:44 by sebonie           #+#    #+#             */
/*   Updated: 2022/05/18 14:05:53 by sebonie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	locksnprint(t_phil *phil, char type)
{
	pthread_mutex_lock(phil->lfork);
	print_status(phil, phil->base, type);
	pthread_mutex_lock(&phil->rfork);
	print_status(phil, phil->base, type);
}

static void	unlock_forks(t_phil *phil)
{
	pthread_mutex_unlock(phil->lfork);
	pthread_mutex_unlock(&phil->rfork);
}

void	*phil_lifecycle(void *phil)
{
	t_phil	*philo;

	philo = (t_phil *)phil;
	if (!(philo->id % 2))
		usleep(500);
	while (philo->nom)
	{
		locksnprint(philo, 'f');
		philo->tom = actual_time();
		print_status(philo, philo->base, 'e');
		usleep_custom(philo->base->tte);
		unlock_forks(philo);
		print_status(philo, philo->base, 's');
		usleep_custom(philo->base->tts);
		print_status(philo, philo->base, 't');
		if (philo->nom != -1)
			philo->nom--;
	}
	pthread_mutex_lock(&philo->base->mut);
	philo->base->meal_counter++;
	philo->final = 1;
	pthread_mutex_unlock(&philo->base->mut);
	return (NULL);
}

t_phil	*create_phil(t_base *base)
{
	int			i;
	t_phil		*phil;

	phil = malloc(sizeof(t_phil) * base->nof);
	if (!phil)
		return (NULL);
	i = -1;
	while (++i < base->nof)
	{
		phil[i].id = i + 1;
		pthread_mutex_init(&phil[i].rfork, NULL);
		phil[i].tom = actual_time();
		phil[i].nom = base->nom;
		phil[i].base = base;
	}
	i = 0;
	while (++i < base->nof)
		phil[i].lfork = &phil[i - 1].rfork;
	phil[0].lfork = &phil[i - 1].rfork;
	pthread_mutex_init(&phil->base->mut, NULL);
	return (phil);
}

pthread_t	*create_thread(t_base *base, t_phil *phil)
{
	int			i;
	int			thread_res;
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * (base->nof));
	if (!thread)
		err_exit(phil->base, 'm');
	base->time = actual_time();
	i = -1;
	while (++i < base->nof)
	{
		thread_res = pthread_create(&thread[i], NULL, phil_lifecycle,
				&(phil[i]));
		if (thread_res)
			return (NULL);
		pthread_detach(thread[i]);
	}
	thread_res = pthread_create(&thread[base->nof], NULL, monitor, phil);
	if (thread_res)
		return (NULL);
	pthread_join(thread[base->nof], NULL);
	return (thread);
}
