/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:35:17 by osarihan          #+#    #+#             */
/*   Updated: 2022/02/18 13:21:19 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int x)
{
	if (x > 127)
		return ((char *)s);
	while (*s)
	{
		if (*s == x)
			return ((char *)s);
		++s;
	}
	if (x == '\0')
		return ((char *)s);
	return (0);
}
