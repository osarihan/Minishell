/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarihan <osarihan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:31:20 by osarihan          #+#    #+#             */
/*   Updated: 2022/02/13 11:31:22 by osarihan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *w, int val, size_t n)
{
	unsigned char	*x;

	x = (unsigned char *)w;
	while (n-- > 0)
		*x++ = val;
	return (w);
}
