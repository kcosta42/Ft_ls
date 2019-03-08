/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 17:29:26 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/06 09:41:43 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

int		ft_show_total(t_list *head, t_arg *arg)
{
	int		blksize;
	t_stat	stat;

	if (!arg->f_long)
		return (1);
	blksize = 0;
	while (head)
	{
		if (lstat(head->content, &stat) < 0)
			break ;
		blksize += stat.st_blocks;
		head = head->next;
	}
	ft_printf("total %d\n", blksize);
	return (0);
}

int		ft_show_name(const char *parent, t_arg *arg)
{
	static int	dir = 0;

	if (parent)
	{
		if (dir > 1 || (dir && arg->f_rec && arg->f_long))
			ft_printf("\n%s:\n", parent);
		else if (dir)
			ft_printf("%s:\n", parent);
	}
	dir++;
	return (0);
}

char	*ft_get_time(time_t tv_sec)
{
	char		*time_fmt;
	char		*tmp;
	char		*tmp2;
	time_t		today;

	(void)time(&today);
	if (today - tv_sec > 14515200)
	{
		tmp = ctime(&tv_sec);
		tmp2 = ft_strsub(tmp, 4, 7);
		tmp = ft_strsub(tmp, 19, 5);
		time_fmt = ft_strjoin(tmp2, tmp);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	else
		time_fmt = ft_strsub(ctime(&tv_sec), 4, 12);
	return (time_fmt);
}

char	*ft_get_color(int f_color, mode_t mode)
{
	char		*color;

	color = "\033[0m";
	if (f_color)
	{
		color = ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH)) ?
			"\033[31m" : color;
		color = (S_ISDIR(mode)) ? "\033[34m" : color;
		color = (S_ISCHR(mode)) ? "\033[43;34m" : color;
		color = (S_ISBLK(mode)) ? "\033[106;34m" : color;
		color = (S_ISFIFO(mode)) ? "\033[100;32m" : color;
		color = (S_ISLNK(mode)) ? "\033[35m" : color;
		color = (S_ISSOCK(mode)) ? "\033[43;34m" : color;
	}
	return (color);
}

size_t	ft_get_max_size(t_list *head)
{
	size_t	max;
	char	*file;

	max = 0;
	while (head)
	{
		file = ft_strrchr(head->content + 1, '/');
		file = (!file) ? (char*)head->content : file + 1;
		if (ft_strlen(file) > max)
			max = ft_strlen(file);
		head = head->next;
	}
	return (max + 1);
}
