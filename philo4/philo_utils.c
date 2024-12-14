#include "philo.h"

void free_all(t_input *input)
{
	int i;

	if (input->fork)
	{
		i = 0;
		while (i < input->nb_of_philo)
		{
			pthread_mutex_destroy(&input->fork[i]);
			i++;
		}
		free(input->fork);
		input->fork = NULL;
	}
	if (input->fork_check)
	{
		free(input->fork_check);
		input->fork_check = NULL;
	}
	pthread_mutex_destroy(&input->printing);
	pthread_mutex_destroy(&input->check_death);
	if (input->philosophers)
	{
		free(input->philosophers);
		input->philosophers = NULL;
	}
}
