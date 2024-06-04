/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr >              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:38:12 by bince             #+#    #+#             */
/*   Updated: 2023/11/13 21:38:55 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	strsize;

	if (!s)
		return ;
	strsize = (size_t)ft_strlen(s);
	write(fd, s, sizeof(char) * strsize);
	write(fd, "\n", sizeof(char));
}
