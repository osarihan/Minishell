/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:27:35 by osarihan          #+#    #+#             */
/*   Updated: 2022/08/27 22:54:37 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int len_count(int number)
{
	int count;
	int nbr;

	nbr = number;
	count = 0;
	if (nbr < 0)
	{
		nbr = nbr * -1;
	}
	while(nbr > 0)
	{
		nbr = nbr / 10;
		count++;
	}
	if (count == 0)
		return (1);
	return (count);
}

int take_power_ten(int nbr)
{
	int total;

	total = 1;
	if (nbr == 0)
		return(1);
	while (nbr > 0)
	{
		total = total * 10;
		nbr--;
	}
 	return(total);
}

int find_bas(int number, int line)
{
	int turn;

	turn = ((number / (take_power_ten(line - 1))) % 10);
	return(turn);
}

char	*ft_itoa(int nbr)
{
	int j = 1;
	char *str;
	int i = 0;
	unsigned int len;
	len = len_count(nbr);
	str = malloc(sizeof(char *) * len);
	if (nbr == -2147483648)
	{
		str = "-2147483648";
		return(str);
	}
	if (nbr < 0)
	{
		nbr = nbr * -1;
		str[i] = '-';
		i++;
	}
	while (len)
	{
		str[i] = (find_bas(nbr, len) + 48);
		i++;
		j++;
		len--;
	}
	str[i] = '\0';
	return(str);
}
