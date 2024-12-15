#include "philo.h"

void	*philo_func_2(void	*args)
{
	t_life_args		*life_args;
	t_philosopher	*philosopher;
	t_input 		*input;
	int				index;

	life_args = (t_life_args *)args;
	philosopher = life_args->philosopher;
	input = life_args->input;
	index = life_args->index;
	while ((any_death(input) == false) && (philosopher->meals_had != input->meals))
	{
		eat(philosopher, input, index);
		if (any_death(input) == true)
			break;
		if (philosopher->meals_had == input->meals)
			break;
		action(input, philosopher, index + 1, "is sleeping");
		msleep(input, input->time_to_sleep);
		if (time_taken(philosopher, input) == true)
			set_death(input, philosopher, index);
		if (any_death(input) == true)
			break;
		action(input, philosopher, index + 1, "is thinking");
	}
	return (NULL);
}

int	philo_with_stop(t_input *input)
{
	int i;
	t_life_args *args;

	i = 0;
	while (i < input->nb_of_philo)
	{
		if (i % 2 != 0)
			usleep(1000);
		args = safe_malloc(sizeof(t_life_args));
		if (!args)
			return (-1);
		args->philosopher = &input->philosophers[i];
		args->input = input;
		args->index = i;
		if (pthread_create(&(input->philosophers[i].thread_id), NULL, philo_func_2, args) != 0)
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