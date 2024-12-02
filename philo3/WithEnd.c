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
	while ((any_death(input) == 0) && (philosopher->meals_had != input->meals))
	{
		eat(philosopher, input, index);
		if (any_death(input) != 0){
			unset_mutex(input, philosopher); 
			break;}
		if (philosopher->meals_had == input->meals){
			unset_mutex(input, philosopher); 
			break;}
		action(input, philosopher, index + 1, "is sleeping");
		sleep_the_action2(input->time_to_sleep, philosopher, input);
		// usleep(input->time_to_sleep * 1000);
		if (any_death(input) != 0)
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
			usleep(100);
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