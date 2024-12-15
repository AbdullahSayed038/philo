#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philosopher
{
	int			id;
	int			meals_had;
	int			left_fork;
	int			right_fork;
	int			meals;
	ssize_t		time_of_last_meal;
	pthread_t	thread_id;
}	t_philosopher;

typedef struct s_input
{
	int				nb_of_philo;
	int				food_flag;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				dead;
	int				*fork_check;
	ssize_t			program_start_time;
	pthread_mutex_t	check_death;
	pthread_mutex_t	*fork;
	pthread_mutex_t	printing;
	t_philosopher	*philosophers;
} t_input;

typedef struct s_life_args 
{
	int				index;
	t_input			*input;
	t_philosopher	*philosopher;
} t_life_args;

void	ft_bzero(void *s, size_t n);
ssize_t get_current_time(void);
void	*philo_func_2(void	*args);
int	philo_with_stop(t_input *input);
void	*philo_func(void	*args);
int	philo_no_stop(t_input *input);
int	init_input(t_input *input, char **av, int ac);
int	init_philo(t_input *input);
ssize_t	init_mutexlocks(t_input *input);
void	eat(t_philosopher *philosopher, t_input *input, int index);
int	any_death(t_input *input);
void	action(t_input *philo, t_philosopher *philosopher, int nb, const char *str);
void	msleep(t_input *input, size_t ms);
ssize_t	get_current_program_time(t_input *philo);
ssize_t time_taken(t_philosopher *philosopher, t_input *philo);
int	ft_atoi_philo(char *str);
void	*safe_malloc(size_t bytes);
void 	set_death(t_input *philo, t_philosopher *philosopher, size_t index);
void	free_all(t_input *input);
void 	set_death(t_input *philo, t_philosopher *philosopher, size_t index);

#endif