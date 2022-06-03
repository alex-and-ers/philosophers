/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:09:50 by sebonie           #+#    #+#             */
/*   Updated: 2022/05/18 13:54:49 by sebonie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

//nof - number of philsophers
//tod - time to die
//toe - time to eat
//tos - time to sleep
//nom - number of eat/meal
//st_t - time;
//eat counter - meal counter
//err_num - exit code
//mut - write
typedef struct s_base
{
	int			nof;
	int			ttd;
	int			tte;
	int			tts;
	int			nom;
	int			meal_counter;
	long		time;
	t_mutex		mut;
	t_mutex		meal_mut;
}	t_base;

//data - in_data
//lfork - left_f
//rfork - right_f
//final - finish act
//meals - eat_iter
//time of meal - tom - st_eat
//nom - number of eat/meal
typedef struct s_phil
{
	int			id;
	t_mutex		rfork;
	t_mutex		*lfork;
	int			meals;
	long		tom;
	int			nom;
	int			final;
	t_base		*base;
}	t_phil;

int			err_exit(t_base *base, char err_code);
void		*monitor(void *phil);

void		*phil_lifecycle(void *phil);
t_phil		*create_phil(t_base *data);
pthread_t	*create_thread(t_base *data, t_phil *phil);
void		finish_all(t_phil *phil, pthread_t *thread);

void		err_msg(char *err);
long		actual_time(void);
void		usleep_custom(int time);
void		print_status(t_phil *ph, t_base *data, char type);

int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *s);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(long long n, int fd);

#endif