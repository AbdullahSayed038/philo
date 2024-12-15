#include "philo.h"

void sleep_the_action2(int time_in_ms, t_philosopher *philosopher, t_input *input)
{
	int	remaining_time;
	int	interval;

	remaining_time = time_in_ms * 1000;
	while (remaining_time > 0)
	{
		if (remaining_time >= 12000)
			interval = 12000;
		else
			interval = remaining_time;
		usleep(interval);
		remaining_time -= interval;
		if (time_taken(philosopher, input) != 0)
		{
			set_death(input, philosopher, philosopher->id);
			unset_mutex(input, philosopher);
			return;
		}
		if (any_death(input) != 0){
			unset_mutex(input, philosopher); 
			break;}
	}
}

void sleep_the_action(int time_in_ms, t_philosopher *philosopher, t_input *input)
{
	int	remaining_time;
	int	interval;

	remaining_time = time_in_ms * 1000;
	while (remaining_time > 0)
	{
		if (remaining_time >= 5000)
			interval = 5000;
		else
			interval = remaining_time;
		usleep(interval);
		remaining_time -= interval;
		if (time_taken(philosopher, input) != 0)
		{
			set_death(input, philosopher, philosopher->id);
			return;
		}
		if (any_death(input) != 0)
			return ;
	}
}

void	action(t_input *philo, t_philosopher *philosopher, int nb, const char *str)
{
	ssize_t	time;

	(void)philosopher;
	time = get_current_program_time(philo);
	pthread_mutex_lock(&philo->printing);
	printf("%zi Philosopher %i is %s.\n", time, nb, str);
	pthread_mutex_unlock(&philo->printing);
}

int	any_death(t_input *input)
{
	pthread_mutex_lock(&input->check_death);
	if (input->dead != 0)
	{
		pthread_mutex_unlock(&input->check_death);
		return (0);
	}
	pthread_mutex_unlock(&input->check_death);
	return (1);
}

void	eat(t_philosopher *philosopher, t_input *input, int index)
{
	if (any_death(input) != 0)
		return ;
	if (input->fork_check[philosopher->left_fork] == 1)
		while (input->fork_check[philosopher->left_fork] == 1)
			usleep(10);
	pthread_mutex_lock(&input->fork[philosopher->left_fork]);
	input->fork_check[philosopher->left_fork] = 1;
	pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
	action(input, philosopher, index + 1, "has taken a fork");
	if (any_death(input) != 0)
	{
		pthread_mutex_lock(&input->fork[philosopher->left_fork]);
		input->fork_check[philosopher->left_fork] = 0;
		pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
		return ;
	}
	if (input->fork_check[philosopher->right_fork] == 1)
		while (input->fork_check[philosopher->right_fork] == 1)
			usleep(10);
	pthread_mutex_lock(&input->fork[philosopher->right_fork]);
	input->fork_check[philosopher->right_fork] = 1;
	action(input, philosopher, index + 1, "has taken a fork");
	pthread_mutex_unlock(&input->fork[philosopher->right_fork]);
	action(input, philosopher, index + 1, "is eating"); 
	philosopher->meals_had++;
	philosopher->time_of_last_meal = get_current_program_time(input);
	sleep_the_action(input->time_to_eat, philosopher, input);
	if (time_taken(philosopher, input) != 0)
	{
		pthread_mutex_lock(&input->fork[philosopher->left_fork]);
		input->fork_check[philosopher->left_fork] = 0;
		pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
		pthread_mutex_lock(&input->fork[philosopher->right_fork]);
		input->fork_check[philosopher->right_fork] = 0;
		pthread_mutex_unlock(&input->fork[philosopher->right_fork]);
		set_death(input, philosopher, index);
		return ;
	}
	pthread_mutex_lock(&input->fork[philosopher->left_fork]);
	input->fork_check[philosopher->left_fork] = 0;
	pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
	pthread_mutex_lock(&input->fork[philosopher->right_fork]);
	input->fork_check[philosopher->right_fork] = 0;
	pthread_mutex_unlock(&input->fork[philosopher->right_fork]);
}
