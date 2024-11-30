#include "philo.h"

ssize_t	get_current_program_time(t_input *philo)
{
	ssize_t	current_time;

	current_time = (get_current_time() - philo->program_start_time);
	return (current_time);
}

ssize_t time_taken(t_philosopher *philosopher, t_input *philo)
{
	ssize_t time;
	
	time = get_current_program_time(philo);
	if (time - philosopher->time_of_last_meal > philo->time_to_die)
		return 1;
	return 0;
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

void	unset_mutex(t_input *input, t_philosopher *philospher)
{
	if (pthread_mutex_trylock(&input->fork[philospher->left_fork]) == 0)
		pthread_mutex_unlock(&input->fork[philospher->left_fork]);
	if (pthread_mutex_trylock(&input->fork[philospher->right_fork]) == 0)
		pthread_mutex_unlock(&input->fork[philospher->right_fork]);
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