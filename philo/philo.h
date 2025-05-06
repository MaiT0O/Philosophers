/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:36:45 by ebansse           #+#    #+#             */
/*   Updated: 2025/05/02 12:59:04 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>	// to create threads and mutex
# include <limits.h>	// INT_MIN/MAX
# include <unistd.h>	// for usleep() & write
# include <stdio.h>		// malloc
# include <stdlib.h>
# include <sys/time.h>	// To get current time
# include <stdbool.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	pthread_mutex_t	last_eat_mutex;
	time_t			last_eat;
	pthread_t		thread;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				philo_count;
	int				must_eat_count;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start;
	pthread_mutex_t	philo_full_mutex;
	int				philo_full;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	simulation_mutex;
	bool			simulation_running;
	pthread_t		monitor_thread;
	t_philo			*philos;
}				t_data;

/*fork.c*/
void	release_forks(t_philo *philo);
void	take_forks(t_philo *philo);

/*utils.c.*/
long	ft_atoi_custom(const char *str);
int		validate_arguments(int argc, char **argv);
void	free_all(t_data *data);
void	end(t_data *data);

/*utils2.c*/
bool	is_dead(t_philo *philo);
time_t	get_time_ms(void);
void	sync_threads(time_t start_meeting_at);
int		init_list(t_data *data);

/*routine.c*/
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);

/*print.c*/
void	set_phi_to(char *activity, t_philo *philo);
void	print_statement(t_philo *philo, char *status);

/*get.c*/
bool	is_running(t_data *data);
void	stop_simulation(t_data *data, bool state);
int		get_philo_full(t_data *data);
void	increment_philo_full(t_data *data);
time_t	get_last_eat(t_philo *philo);

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