/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsayed <abdsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:56:20 by abdsayed          #+#    #+#             */
/*   Updated: 2024/12/15 19:07:38 by abdsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	get_current_program_time(t_input *philo)
{
	ssize_t	current_time;

	current_time = (get_current_time() - philo->program_start_time);
	return (current_time);
}

ssize_t	time_taken(t_philosopher *philosopher, t_input *philo)
{
	ssize_t	time;

	time = get_current_program_time(philo);
	if (time - philosopher->time_of_last_meal >= philo->time_to_die)
		return (true);
	return (false);
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
			break ;
		i++;
	}
	if (nb > 2147483647)
		return (-1);
	return (nb);
}

void	*safe_malloc(size_t bytes)
{
	void	*malloced_buffer;

	malloced_buffer = malloc(bytes + (size_t) sizeof(size_t));
	if (!malloced_buffer)
		abort();
	if (!malloced_buffer)
		return (NULL);
	ft_bzero(malloced_buffer, bytes + (size_t) sizeof(size_t));
	return (malloced_buffer);
}

void	free_all(t_input *input)
{
	int	i;

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
