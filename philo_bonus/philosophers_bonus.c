/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:37:03 by sebonie           #+#    #+#             */
/*   Updated: 2022/05/18 14:54:15 by sebonie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	err_exit(t_base *base, char err_code)
{	
	if (err_code == 'e')
		free(base);
	if (err_code == 'a')
		err_msg("You should use from 4 to 5 args!");
	if (err_code == 'p')
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
	t_base	*tmp;
	int		i;

	i = 0;
	if (!symbol_check(ac, av))
		return (NULL);
	tmp = malloc(sizeof (t_base));
	if (!tmp)
		return (NULL);
	while (++i < ac)
		if (ft_atoi(av[i]) <= 0)
			return (NULL);
	tmp->nof = ft_atoi(av[1]);
	if (tmp->nof > 200)
		return (NULL);
	tmp->ttd = ft_atoi(av[2]);
	tmp->tte = ft_atoi(av[3]);
	tmp->tts = ft_atoi(av[4]);
	tmp->nom = -1;
	if (ac == 6)
		tmp->nom = ft_atoi(av[5]);
	tmp->meal_time = actual_time();
	return (tmp);
}

int	main(int ac, char **av)
{
	t_base		*base;

	if (ac != 5 && ac != 6)
		return (err_exit(NULL, 'a'));
	base = init_base_struct(ac, av);
	if (!base)
		return (err_exit(NULL, 'p'));
	init_semaphore(base, 'o');
	create_phil(base);
	base->time = actual_time();
	if (base->counter == base->nof)
		main_process(base);
	else
		secondary_process(base);
	init_semaphore(base, 'c');
	free(base);
	return (0);
}
