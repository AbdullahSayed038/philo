#include "philo.h"

ssize_t get_current_time(void)
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

ssize_t	get_current_program_time(t_input *philo)
{
	ssize_t	current_time;

	current_time = (get_current_time() - philo->program_start_time);
	return (current_time);
}

void	sleep_the_action(int time)
{
	usleep(time * 1000);
}

void	ft_bzero(void *s, size_t n)
{
	if (!s)
		return (perror("bzero: sending null"));
//	if ((size_t)s + n < n || (size_t)s + n < (size_t)s)
//		return(perror("bzero: crazy count"));
	while (n--)
		*(unsigned char *)s++ = 0;
}

void	*safe_malloc(size_t bytes)
{
	void	*malloced_buffer;

	malloced_buffer = malloc(bytes + (size_t)sizeof(size_t));
	if (!malloced_buffer)
		abort();
	if (!malloced_buffer)
		return (NULL);
	ft_bzero(malloced_buffer, bytes + (size_t)sizeof(size_t));
	return (malloced_buffer);
}

int	ft_atoi_philo(char *str)
{
	long long	nb;
	int			i;

	if (!str)
		return (-1);
	nb = 0;
	i = 0;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') && str[i])
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (*str)
	{
		if ((str[i] >= '0' && str[i] <= '9') && nb <= 2147483647)
			nb = nb * 10 + (str[i] - '0');
		else
			break;
		i++;
	}
	if (nb > 2147483647)
		return (-1);
	return (nb);
}

int	init_init(t_input *input, char **av, int ac)
{
	input->nb_of_philo = ft_atoi_philo(av[1]);
	input->time_to_die = ft_atoi_philo(av[2]);
	input->time_to_eat = ft_atoi_philo(av[3]);
	input->time_to_sleep = ft_atoi_philo(av[4]);
	input->food_flag = 0;
	if (ac == 6)
		input->meals = ft_atoi_philo(av[5]), input->food_flag = 1;
	else
		input->meals = 0;
	if (input->nb_of_philo <= 0 || input->time_to_die <= 0 || input->time_to_eat <= 0 || input->time_to_sleep<= 0)
		return (-1);
	if (input->food_flag = 1)
		if (input->meals <= 0)
			return (-1);
	return (0);
}

int	init_philo(t_input *input)
{
	int i;

	i = input->nb_of_philo - 1;
	input->philosophers = safe_malloc((sizeof(t_philosopher *) * input->nb_of_philo) + 1);
	if (!input->philosophers)
		return (-1);
	while (i >= 0)
	{
		input->philosophers[i].id = i;
		input->philosophers[i].time_of_last_meal = input->program_start_time;
		input->philosophers[i].left_fork = i;
		input->philosophers[i].right_fork = (i + 1) % input->nb_of_philo;
		input->philosophers[i].meals = 0;
		i--;
	}
	input->fork = safe_malloc((sizeof(pthread_mutex_t *) * input->nb_of_philo) + 1);
	if (!input->fork)
		return (-1);
	return (0);
}

void	*philo_func(void	*args)
{
	t_life_args		*life_args;
	t_philosopher	*philosopher;
	t_input 		*input;
	int				index;

	life_args = (t_life_args *)args;
	philosopher = life_args->philosopher;
	input = life_args->input;
	index = life_args->index;
}

int	philo_no_stop(t_input *input)
{
	int i;
	t_life_args *args;

	i = 0;
	while (i < input->nb_of_philo)
	{
		args = malloc(sizeof(t_life_args));
		if (!args)
			return (-1);
		args->philosopher = &input->philosophers[i];
		args->input = input;
		args->index = i;
		if (pthread_create(&(input->philosophers[i].thread_id), NULL, philo_func, args) != 0)
		{
			free(args);
			return (-1);
		}
		i++;
		sleep_the_action(1);
	}
	i = 0;
	while (i < input->nb_of_philo)
	{
		if (pthread_join(input->philosophers[i].thread_id, NULL) != 0)
			return (-1);
		i++;
	}
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
	return (0);
}

int	main(int ac, char **av)
{
	t_input	input;

	if (ac != 5 || ac != 6)
		abort();
	if (init_input(&input, av, ac) != 0)
		abort();
	if (init_philo(&input) != 0)
		abort();
	if (init_mutexlocks(&input) != 0)
		abort();
	if (input.food_flag == 0)
		if (philo_no_stop(&input) != 0)
			abort();
	else
		if (philo_with_stop(&input) != 0)
			abort();
	return (0);
}
