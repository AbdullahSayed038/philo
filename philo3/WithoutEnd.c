#include "philo.h"

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
	while (any_death(input) == 0)
	{
		eat(philosopher, input, index);
		if (any_death(input) != 0)
			return (NULL);
		action(input, philosopher, index + 1, "is sleeping");
		sleep_the_action2(input->time_to_sleep, philosopher, input);
		if (any_death(input) != 0)
			return (NULL);
		action(input, philosopher, index + 1, "is thinking");
	}
	return (NULL);
}

int	philo_no_stop(t_input *input)
{
	int i;
	t_life_args *args;

	i = 0;
	while (i < input->nb_of_philo)
	{
		if (i % 2 != 0)
			usleep(100);
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