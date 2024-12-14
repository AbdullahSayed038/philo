#include "philo.h"

int	init_input(t_input *input, char **av, int ac)
{
	input->nb_of_philo = ft_atoi_philo(av[1]);
	input->time_to_die = ft_atoi_philo(av[2]);
	input->time_to_eat = ft_atoi_philo(av[3]);
	input->time_to_sleep = ft_atoi_philo(av[4]);
	input->program_start_time = get_current_time();
	input->food_flag = 0;
	if (ac == 6)
		input->meals = ft_atoi_philo(av[5]), input->food_flag = 1;
	else
		input->meals = 0;
	if (input->nb_of_philo <= 0 || input->time_to_die <= 0 || input->time_to_eat <= 0 || input->time_to_sleep<= 0)
		return (-1);
	if (input->food_flag == 1)
		if (input->meals <= 0)
			return (-1);
	return (0);
}

int	init_philo(t_input *input)
{
	int	i;

	input->philosophers = safe_malloc(sizeof(t_philosopher) * input->nb_of_philo);
	if (!input->philosophers)
		return (-1);
	i = input->nb_of_philo - 1;
	while (i >= 0)
	{
		input->philosophers[i].id = i;
		input->philosophers[i].time_of_last_meal = input->program_start_time;
		input->philosophers[i].left_fork = i;
		input->philosophers[i].right_fork = (i + 1) % input->nb_of_philo;
		input->philosophers[i].meals = 0;
		i--;
	}
	input->fork = safe_malloc(sizeof(pthread_mutex_t) * input->nb_of_philo);
	input->fork_check = safe_malloc(sizeof(int) * input->nb_of_philo);
	if (!input->fork)
		return (-1);
	return (0);
}

ssize_t	init_mutexlocks(t_input *input)
{
	int	i;

	i = input->nb_of_philo - 1;
	while (i >= 0)
	{
		if (pthread_mutex_init(&(input->fork[i]), NULL))
			return (-1);
		i--;
	}
	if (pthread_mutex_init(&(input->printing), NULL))
		return (1);
	i = input->nb_of_philo - 1;
	while (i >= 0)
	{
		if (pthread_mutex_init(&(input->fork[i]), NULL))
			return (-1);
		i--;
	}
	pthread_mutex_init(&(input->check_death), NULL);
	return (0);
}
