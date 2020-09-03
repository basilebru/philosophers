/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 12:10:02 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/03 17:20:01 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "one.h"

void	*death_alarm(void *void_options)
{
	int	max;
	t_options *options;
	int elapsed_time;
	
	options = (t_options*)void_options;
	max = options->t_to_die;
	while (options->stop_all == NO) // pour que le thread soit arrêté en cas de fin du programme pour cause de enough_eat
	{
		if (options->latest_meal)
			elapsed_time = ft_get_mstime() - options->latest_meal;
		else
			elapsed_time = ft_get_mstime() - options->timestamp_start;
		if (elapsed_time > max)
		{
			ft_print_status(DIE, options);
			options->died = YES;
			return (NULL);
		}
		usleep(1); // 1 ms (pas plus de 10ms entre la mort et l'affichage de la mort)
	}
	return(NULL);
}

int     create_death_thread(t_options *options)
{
	pthread_t death_thread;

	if (pthread_create(&death_thread, NULL, &death_alarm, options))
	{
		ft_putendl_fd("pthread_create failed", 2);
		return (EXIT_FAILURE);
	}
	pthread_detach(death_thread);
	return (EXIT_SUCCESS);
}