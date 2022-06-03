/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:37:16 by sebonie           #+#    #+#             */
/*   Updated: 2022/05/18 14:58:44 by sebonie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct timeval	t_timeval;

typedef struct s_base
{
	int		nof;
	int		ttd;
	int		tte;
	int		tts;
	int		nom;
	int		counter;
	int		pids[201];
	long	time;
	long	meal_time;
	sem_t	*fork;
	sem_t	*sem;
}	t_base;

void	err_msg(char *err);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(long long n, int fd);
int		ft_atoi(const char *nptr);

void	err_msg(char *err);
long	actual_time(void);
void	usleep_custom(int time);
void	print_status(t_base *base, char type);
void	*monitor(void *base);

void	main_process(t_base *base);
void	secondary_process(t_base *base);
void	create_phil(t_base *base);
void	init_semaphore(t_base *base, char type);

int		err_exit(t_base *base, char err_code);

#endif