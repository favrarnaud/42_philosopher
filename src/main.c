/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 07:43:00 by afavre            #+#    #+#             */
/*   Updated: 2023/01/12 13:06:50 by afavre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		ret;

	if (argc != 5 && argc != 6)
		return (write_error("Wrong amount of arguments"));
	ret = init_rules(&rules, argv);
	if (ret == 1)
		return (error_manager(ret));
	if (launcher(&rules))
		return (write_error("There was an error creating the threads"));
	return (0);
}
