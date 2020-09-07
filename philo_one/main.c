/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:29:36 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/07 15:45:32 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

int		check_args(int argc, char **argv)
{
	int i;
	
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("wrong number of args", 2);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_isdigit_str(argv[i]) == 0)
		{
			ft_putendl_fd("non digit argument", 2);
			return (EXIT_FAILURE);
		}
		if (ft_strlen(argv[i]) > 9)
		{
			ft_putendl_fd("too big number", 2); // facon de protéger les ft_atoi
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}


int     main(int argc, char **argv)
{
	pthread_t		*threads_philo; // tableau de pthreads: un thread par philo
	pthread_mutex_t	*forks; // tableau de mutex: chacun pour une fourchette
	pthread_mutex_t	display; // mutex pour l'affichage à l'écran des statuts
	t_options		**options; // tableau de t_options* (arguments envoyés aux threads)
	int				num_philo;
	int				*eat_num;
	int				stop_all;
	
	if (check_args(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	num_philo = ft_atoi(argv[1]);
	if (init_mutexes(num_philo, &forks, &display) == EXIT_FAILURE
		|| malloc_options(&options, num_philo) == EXIT_FAILURE
		|| fill_vars(num_philo, &eat_num, &stop_all) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fill_options_args(options, argv, eat_num, &stop_all);
	fill_options_mutexes(options, &display, forks);
	if (create_threads(&threads_philo, options, num_philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	join_threads(num_philo, threads_philo);

	if (destroy_mutexes(num_philo, forks, display) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	free_options(num_philo, options);
}
