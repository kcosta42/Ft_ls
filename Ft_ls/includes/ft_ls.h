/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 14:51:17 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/03 19:02:47 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>

# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <sys/types.h>

# include <uuid/uuid.h>

# include "libft.h"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct	s_arg
{
	int			f_rec;
	int			f_all;
	int			f_long;
	int			f_rev;
	int			f_time;
	int			f_color;
}				t_arg;

int				ft_display(t_arg *arg, t_list *head);
int				ft_error(int errnum, const char *filename);

#endif