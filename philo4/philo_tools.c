
#include "philo.h"

void	msleep(t_input *input, size_t ms)
{
	size_t	start;

	start = get_current_program_time(input);
	while (!any_death(input) && ((get_current_program_time(input) - start) < ms))
		usleep(100);
}

void	action(t_input *philo, t_philosopher *philosopher, int nb, const char *str)
{
	ssize_t	time;

	(void)philosopher;
	time = get_current_program_time(philo);
	pthread_mutex_lock(&philo->printing);
	printf("%zi %i %s\n", time, nb, str);
	pthread_mutex_unlock(&philo->printing);
}

int	any_death(t_input *input)
{
	pthread_mutex_lock(&input->check_death);
	if (input->dead != 0)
	{
		pthread_mutex_unlock(&input->check_death);
		return (true);
	}
	pthread_mutex_unlock(&input->check_death);
	return (false);
}

void	grab_fork(t_philosopher *philosopher, t_input *input, int index)
{
	int	claimed;

	(void)index;
	claimed = 0;
	while (any_death(input) == false && !claimed)
	{
		pthread_mutex_lock(&input->fork[philosopher->left_fork]);
		claimed = input->fork_check[philosopher->left_fork];
		if (claimed == 0)
			input->fork_check[philosopher->left_fork] = 1;
		pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
		if (!claimed)
			usleep(100);
	}
}

void	grab_second_fork(t_philosopher *philosopher, t_input *input, int index)
{
	int	claimed;

	(void)index;
	claimed = 0;
	while (any_death(input) == false && !claimed)
	{
		pthread_mutex_lock(&input->fork[philosopher->right_fork]);
		claimed = input->fork_check[philosopher->right_fork];
		if (claimed == 0)
			input->fork_check[philosopher->right_fork] = 1;
		pthread_mutex_unlock(&input->fork[philosopher->right_fork]);
		if (!claimed)
			usleep(100);
	}
}

void	release_fork(t_input *input, t_philosopher *philosopher)
{
	pthread_mutex_lock(&input->fork[philosopher->left_fork]);
	input->fork_check[philosopher->left_fork] = 0;
	pthread_mutex_unlock(&input->fork[philosopher->left_fork]);
}

void	release_second_fork(t_input *input, t_philosopher *philosopher)
{
	pthread_mutex_lock(&input->fork[philosopher->right_fork]);
	input->fork_check[philosopher->right_fork] = 0;
	pthread_mutex_unlock(&input->fork[philosopher->right_fork]);
}

void	eat(t_philosopher *philosopher, t_input *input, int index)
{
	if (any_death(input) == true)
		return ;
	grab_fork(philosopher, input, index);
	if (any_death(input) == true)
	{
		release_fork(input, philosopher);
		return ;
	}
	action(input, philosopher, index + 1, "has taken a fork");
	grab_second_fork(philosopher, input, index);
	if (any_death(input) == true)
	{
		release_fork(input, philosopher);
		release_second_fork(input, philosopher);
		return ;
	}
	action(input, philosopher, index + 1, "has taken a fork");
	action(input, philosopher, index + 1, "is eating"); 
	philosopher->meals_had++;
	philosopher->time_of_last_meal = get_current_program_time(input);
	msleep(input, input->time_to_eat);
	if (time_taken(philosopher, input) != 0)
	{
		release_fork(input, philosopher);
		release_second_fork(input, philosopher);
		set_death(input, philosopher, index);
		return ;
	}
	release_fork(input, philosopher);
	release_second_fork(input, philosopher);
}
