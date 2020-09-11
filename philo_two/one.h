/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunet <bbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:14:39 by bbrunet           #+#    #+#             */
/*   Updated: 2020/09/11 11:31:50 by bbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ONE_H
# define ONE_H

# include <pthread.h>
# include <sys/time.h>
#include <semaphore.h>
# include <unistd.h> // usleep, write
# include <stdlib.h> //malloc
# include <string.h> // memset
# include "stdio.h" // printf
#include <fcntl.h> // for sem_open flags
#include <sys/stat.h> // for sem_open modes

typedef struct	s_options
{
	int				identifier;
	int				num_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				eat_max;
	long int		latest_meal; //  timestamp du dernier repas
	long int		timestamp_start; // timestamp debut simulation
	int				*eat_num; // tableau qui contient le nombre de repas pris par chaque philo
	int				*stop_all; // signal pour les threads qu'il faut exit (un int partagé par l'ensemble des threads)
	sem_t			*sem;
	sem_t			*display;
}				t_options;

typedef struct	s_input
{
	pthread_t		*threads_philo;
	sem_t			*sem; // semaphore qui représente le nombre de fourchettes dispo
	sem_t			*display;
	int				*eat_num;
	int				stop_all;
}				t_input;

enum	e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

# define UNSET -1
# define YES 1
# define NO 0
# define ODD 0
# define EVEN 1

/*
** ---------------------- Main prototypes ---------------------
*/

int		init_input(int num_philo, t_input **input);
int		init_options(t_options ***opt, char **argv, t_input *in, int num);

int		create_threads(t_input *input, t_options **options, int num_philo);
int		create_death_thread(t_options **options);

int		destroy_sem(t_input *input);
void	free_stuff(t_options **options, t_input *input);
int		join_threads(int num, pthread_t *threads);

/*
** ---------------------- Thread prototypes ---------------------
*/

void	*cycle(void *void_options);
void	*stop(void *void_options);

int		lock_forks(t_options *options);
int		unlock_forks(t_options *options);
int		ft_print_status(int status, t_options *options);
void	check_stop(t_options *options, int status);

long	ft_get_mstime();

/*
** ---------------------- Libft prototypes ---------------------
*/

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(long int nlong);
int		ft_isdigit_str(char *str);

#endif