/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:41:53 by osarihan          #+#    #+#             */
/*   Updated: 2022/02/18 13:03:31 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int x)
{
	char	*last_pos;

	last_pos = (0);
	if (x > 127)
		return ((char *)s);
	while (*s)
	{
		if (*s == x)
			last_pos = (char *)s;
		++s;
	}
	if (last_pos)
		return (last_pos);
	if (x == '\0')
		return ((char *)s);
	return (0);
}
