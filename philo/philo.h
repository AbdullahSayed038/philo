/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsayed <abdsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:51:44 by abdsayed          #+#    #+#             */
/*   Updated: 2024/10/21 13:57:32 by abdsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# define bool _Bool
# define true 1
# define false 0
# define ERROR -1
# define SUCCESS 0
# define FAILURE 1

typedef struct s_thinkers
{
	ssize_t	number;
	
} t_thinkers;

typedef struct s_philosophers
{
	struct timeval	tv;
	ssize_t		time_start;
	size_t		amount;
	size_t		death_timer;
	size_t		eat_timer;
	size_t		sleep_timer;
	t_thinkers	*thinkers;
	size_t		alive;
} t_philosophers;

int	ft_atoi(const char *str);
void	*safe_malloc(size_t bytes);
ssize_t	start_philo(t_philosophers *info);

#endif