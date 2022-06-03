/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:09:37 by sebonie           #+#    #+#             */
/*   Updated: 2022/05/18 14:00:36 by sebonie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	err_exit(t_base *base, char err_code)
{	
	if (err_code == 'e')
		free(base);
	if (err_code == 'a')
		err_msg("You should use from 4 to 5 args!");
	if (err_code == 'b')
		err_msg("Bad args!");
	if (err_code == 'm')
		err_msg("Malloc err!");
	return (1);
}

static int	symbol_check(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] == ' ' || (av[i][j] >= '0' && av[i][j] <= '9')))
				return (0);
			j++;
		}
	}
	return (1);
}

static t_base	*init_base_struct(int ac, char **av)
{
	int		i;
	t_base	*res;

	i = 0;
	if (!symbol_check(ac, av))
		return (NULL);
	res = malloc(sizeof (t_base));
	if (!res)
		return (NULL);
	while (++i < ac)
		if (ft_atoi(av[i]) <= 0)
			return (NULL);
	res->nof = ft_atoi(av[1]);
	res->ttd = ft_atoi(av[2]);
	res->tte = ft_atoi(av[3]);
	res->tts = ft_atoi(av[4]);
	res->nom = -1;
	res->meal_counter = 0;
	if (ac == 6)
		res->nom = ft_atoi(av[5]);
	return (res);
}

int	main(int ac, char **av)
{
	t_base		*base;
	t_phil		*phil;
	pthread_t	*threads;

	if (ac != 5 && ac != 6)
		return (err_exit(NULL, 'a'));
	base = init_base_struct(ac, av);
	if (!base)
		return (err_exit(NULL, 'b'));
	phil = create_phil(base);
	if (!phil)
		return (err_exit(NULL, 'm'));
	threads = create_thread(base, phil);
	if (!threads)
		return (err_exit(base, 'e'));
	finish_all(phil, threads);
	return (0);
}
