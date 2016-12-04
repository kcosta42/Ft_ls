/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 18:43:57 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/04 14:04:14 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int				ft_error(int errnum, const char *filename)
{
	if (filename)
		ft_printf("ft_ls: %s: %s\n", filename, strerror(errnum));
	else
		ft_printf("ft_ls: %s\n", strerror(errnum));
	return (errnum);
}
