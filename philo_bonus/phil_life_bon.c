/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_life_bon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:48:04 by sebonie           #+#    #+#             */
/*   Updated: 2022/05/18 15:37:08 by sebonie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	main_process_aux(t_base *base, int code, int *arr)
{
	int	i;

	i = -1;
	if (code == 1)
	{
		while (++i < base->nof)
			kill(base->pids[i], SIGTERM);
	}
	if (code == 2)
	{
		while (++i < base->nof)
			if (arr[i] == 0)
				break ;
	}
}

void	main_process(t_base *base)
{
	int	i;
	int	sig;
	int	arr[201];

	memset(arr, 0, 201);
	i = -1;
	while (++i < base->nof)
	{
		waitpid(-1, &sig, 0);
		if (!sig)
		{
			main_process_aux(base, 1, arr);
			break ;
		}
		arr[i] = 1;
	}
	main_process_aux(base, 2, arr);
}

void	secondary_process(t_base *base)
{
	pthread_t	thread;

	base->counter++;
	pthread_create(&thread, NULL, monitor, base);
	pthread_detach(thread);
	if (!(base->counter % 2))
		usleep_custom(100);
	while (base->nom)
	{
		sem_wait(base->fork);
		print_status(base, 'f');
		sem_wait(base->fork);
		print_status(base, 'f');
		base->meal_time = actual_time();
		print_status(base, 'e');
		usleep_custom(base->tte);
		sem_post(base->fork);
		sem_post(base->fork);
		print_status(base, 's');
		usleep_custom(base->tts);
		print_status(base, 't');
		if (base->nom != -1)
			base->nom -= 1;
	}
	exit (1);
}

void	create_phil(t_base *base)
{
	base->counter = 0;
	while (base->counter < base->nof)
	{
		base->pids[base->counter] = fork();
		if (!base->pids[base->counter])
			break ;
		base->counter++;
	}
}

void	init_semaphore(t_base *base, char type)
{
	if (type == 'o')
	{
		sem_unlink("fork");
		sem_unlink("write");
		base->fork = sem_open("fork", O_CREAT, S_IRWXU, base->nof);
		base->sem = sem_open("write", O_CREAT, S_IRWXU, 1);
	}
	if (type == 'c')
	{
		sem_close(base->fork);
		sem_close(base->sem);
		sem_unlink("fork");
		sem_unlink("write");
	}
}
