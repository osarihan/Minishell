/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:40 by osarihan          #+#    #+#             */
/*   Updated: 2022/10/07 16:12:55 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *asd;
	char *name = NULL;
	printf("|----------------|Minishell|-----------------|\n");
	
	name = get_name(name);
	while (1)
	{
		asd = readline(name);
		if (check_cmnd(asd))
		{
			continue;
		}
		else
			printf("%s: command not found.\n", asd);
	}
	return(1);
}