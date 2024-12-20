/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsayed <abdsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:56:18 by abdsayed          #+#    #+#             */
/*   Updated: 2024/12/18 14:28:17 by abdsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	set_death(t_input *philo, t_philosopher *philosopher, size_t index)
{
	ssize_t	time;

	(void)index;
	time = get_current_program_time(philo);
	pthread_mutex_lock(&philo->check_death);
	if (philo->dead == 0)
	{
		philo->dead = 1;
		pthread_mutex_lock(&philo->printing);
		printf("%zi %i %s\n", time, philosopher->id + 1, "has died");
		pthread_mutex_unlock(&philo->printing);
	}
	pthread_mutex_unlock(&philo->check_death);
}

void	ft_bzero(void *s, size_t n)
{
	if (!s)
		return (perror("bzero: sending null"));
	while (n--)
		*(unsigned char *)s++ = 0;
}

void	solo_dolo(t_input *input)
{
	action(input, 1, "has taken a fork");
	msleep(input, input->time_to_die, &input->philosophers[0]);
	action(input, 1, "has died");
}

int	main(int ac, char **av)
{
	t_input	input;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (-1);
	if (init_input(&input, av, ac) != 0)
		return (-1);
	if (init_philo(&input) != 0)
		i = -1;
	if (input.nb_of_philo == 1 && i == 0)
		solo_dolo(&input), free_all(&input);
	else if (input.food_flag == 0 && i == 0)
	{
		if (philo_no_stop(&input) != 0)
			i = -1;
	}
	else if (i == 0)
	{
		if (philo_with_stop(&input) != 0)
			i = -1;
	}
	free_all(&input);
	return (i);
}
