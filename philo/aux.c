/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:40:28 by sebonie           #+#    #+#             */
/*   Updated: 2022/05/17 20:10:56 by sebonie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	err_msg(char *err)
{
	ft_putstr_fd("Error ", 2);
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\n', 2);
}

long	actual_time(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	usleep_custom(int time)
{
	long	tmp;

	tmp = actual_time();
	usleep(time * 950);
	while ((time + tmp) > actual_time())
		usleep(250);
}

void	finish_all(t_phil *phil, pthread_t *thread)
{
	int	nof;

	nof = phil->base->nof;
	while (nof > 0)
	{
		pthread_mutex_destroy(&phil[nof].rfork);
		nof--;
	}
	pthread_mutex_destroy(&phil->base->mut);
	free(thread);
	free(phil->base);
	free(phil);
}

void	print_status(t_phil *ph, t_base *data, char type)
{
	long	time;

	time = actual_time() - data->time;
	pthread_mutex_lock(&ph->base->mut);
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(ph->id, 1);
	if (type == 'e')
		printf(" is eating\n");
	if (type == 'f')
		printf(" has taken a fork\n");
	if (type == 't')
		printf(" is thinking\n");
	if (type == 's')
		printf(" is sleeping\n");
	pthread_mutex_unlock(&(ph->base->mut));
}
