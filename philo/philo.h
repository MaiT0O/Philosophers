/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:36:45 by ebansse           #+#    #+#             */
/*   Updated: 2025/04/30 13:38:49 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	pthread_mutex_t	last_eat_mutex;
	long			last_eat;
	pthread_t		thread;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				die;
	pthread_mutex_t	philo_full_mutex;
	int				philo_full;
	pthread_mutex_t	start_mutex;
	long			start;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	simulation_mutex;
	int				simulation_running;
	pthread_t		monitor_thread;
	t_philo			*philos;
}				t_data;

/*fork.c*/
void	release_forks(t_philo *philo);
void	take_forks(t_philo *philo);

/*utils.c.*/
long	ft_atoi_custom(const char *str);
int		validate_arguments(int argc, char **argv);
int		free_all(t_data *data);
int		end(t_data *data);

/*utils2.c*/
int		is_dead(t_philo *philo);
int		is_full(t_data *data);
long	get_time_ms(void);
long	correct_time(t_data *data);

/*routine.c*/
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);
void	philosopher_think(t_philo *philo);

/*print.c*/
void	print_fork(t_philo *philo);
void	print_death(t_philo *philo);
void	print_meal(t_data *data);

/*init.c*/
int		init_alone_philo(t_data *data);
void	*alone_philosophe_routine(void *arg);
int		create_monitor_thread(t_data *data);
int		init_list(t_data *data);
void	set_last_eat(t_philo *philo);

/*main.c*/
int		data_philo_init(t_data *data, int i);

/*get.c*/
int		is_running(t_data *data);
void	stop_simulation(t_philo *philo);
int		get_philo_full(t_data *data);
void	increment_philo_full(t_data *data);
long	get_last_eat(t_philo *philo);

// Messages pour les philosophes
# define MSG_TAKE_FORK "has taken a fork"
# define MSG_EATING "is eating"
# define MSG_SLEEPING "is sleeping"
# define MSG_THINKING "is thinking"
# define MSG_DIED "died"

// Autres messages
# define ERR_INVALID_ARGS "Error: Invalid arguments."
# define ERR_MEMORY_ALLOC "Error: Failed to allocate memory."
# define ERR_MUTEXES "Error: Failed to initialize mutex."
# define USAGE "Usage: ./philo number_of_philo die_in_ms eat_in_ms sleep_in_ms"
# define ERR_THREAD "Error: Failed to create thread"

#endif