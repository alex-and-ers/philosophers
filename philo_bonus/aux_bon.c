/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_bon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:49:05 by sebonie           #+#    #+#             */
/*   Updated: 2022/05/18 15:36:47 by sebonie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
	usleep(time * 990);
	while ((time + tmp) > actual_time())
		usleep(400);
}

void	*monitor(void *base)
{
	t_base	*phil;

	phil = (t_base *)base;
	while (1)
	{
		if ((actual_time() - phil->meal_time) > (phil->ttd))
		{
			sem_wait(phil->sem);
			printf("%ld %d died\n", actual_time() - phil->time, phil->counter);
			exit (0);
		}
		usleep(1000);
	}
}

void	print_status(t_base *base, char type)
{
	long	time;

	time = actual_time() - base->time;
	sem_wait(base->sem);
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(base->counter, 1);
	if (type == 'e')
		printf(" is eating\n");
	if (type == 'f')
		printf(" has taken a fork\n");
	if (type == 't')
		printf(" is thinking\n");
	if (type == 's')
		printf(" is sleeping\n");
	sem_post(base->sem);
}
