/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsayed <abdsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:51:39 by abdsayed          #+#    #+#             */
/*   Updated: 2024/10/21 14:00:09 by abdsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	index_thinkers(t_philosophers *info)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (i < info->amount)
	{
		info->thinkers[i].number = j;
		i++;
		j++;
	}
	 
}

int main(int ac, char **av)
{
	t_philosophers	info;
	int	i;
	
	i = 0;
	if (ac == 4 || ac == 5)
	{
		gettimeofday(&info.tv, NULL);
		info.time_start = info.tv.tv_usec * 1000;
		info.amount = ft_atoi(av[1]);
		info.death_timer = ft_atoi(av[2]);
		info.eat_timer = ft_atoi(av[3]);
		info.sleep_timer = ft_atoi(av[4]);
		info.thinkers = safe_malloc(info.amount * sizeof(t_thinkers *));
		if (!info.thinkers)
			return (NULL);
		index_thinkers(&info);
		if (start_philo(&info) == ERROR)
			end_of_world(&info);
	}
	return (0);
}
