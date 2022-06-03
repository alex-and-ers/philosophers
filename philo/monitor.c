/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:32:57 by sebonie           #+#    #+#             */
/*   Updated: 2022/05/18 13:54:15 by sebonie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	checker1(t_phil *phil, int i)
{
	int	res;

	pthread_mutex_lock(&phil->base->mut);
	res = ((actual_time() - phil[i].tom) > phil->base->ttd);
	pthread_mutex_unlock(&phil->base->mut);
	return (res);
}

static int	checker2(t_phil *phil)
{
	int	res;

	pthread_mutex_lock(&phil->base->mut);
	res = phil->base->nof == phil->base->meal_counter;
	pthread_mutex_unlock(&phil->base->mut);
	return (res);
}

static int	monitor2(t_phil *phil)
{
	int	i;

	i = -1;
	while (++i < phil->base->nof)
	{
		if (checker2(phil))
		{
			pthread_mutex_lock(&phil->base->mut);
			printf("Meals(%d) finished\n", phil->base->nom);
			return (1);
		}
		if (!phil[i].final)
		{
			if (checker1(phil, i))
			{
				pthread_mutex_lock(&phil->base->mut);
				printf("%ld %d died\n", actual_time() - phil->base->time,
					phil->id);
				return (1);
			}
		}
		usleep(1000);
	}
	return (0);
}

void	*monitor(void *phil)
{
	t_phil	*philo;

	philo = (t_phil *)phil;
	while (1)
	{
		if (monitor2(phil))
			break ;
	}
	return (NULL);
}
