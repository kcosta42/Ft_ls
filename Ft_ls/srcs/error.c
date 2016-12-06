/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 18:43:57 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/06 08:52:29 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int		ft_error(int errnum, const char *filename)
{
	if (filename)
		ft_printf("ft_ls: %s: %s\n", filename, strerror(errnum));
	else
		ft_printf("ft_ls: %s\n", strerror(errnum));
	return (errnum);
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
