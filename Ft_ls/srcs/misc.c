/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 17:29:26 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/04 23:01:54 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

int				ft_error(int errnum, const char *filename)
{
	if (filename)
		ft_printf("ft_ls: %s: %s\n", filename, strerror(errnum));
	else
		ft_printf("ft_ls: %s\n", strerror(errnum));
	return (errnum);
}

void	ft_delnode(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
}

int		ft_isvalid_file(char *filename)
{
	if (filename[ft_strlen(filename) - 1] == '.')
		return (0);
	if (filename[ft_strlen(filename) - 1] == '.'
		&& filename[ft_strlen(filename) - 2] == '.')
		return (0);
	return (1);
}
