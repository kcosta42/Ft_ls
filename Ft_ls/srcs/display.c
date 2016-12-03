/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 12:41:00 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/03 19:15:22 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

static void		ft_print_mode(mode_t st_mode)
{
	char	c;

	c = '-';
	c = (S_ISDIR(st_mode)) ? 'd' : c;
	c = (S_ISCHR(st_mode)) ? 'c' : c;
	c = (S_ISBLK(st_mode)) ? 'b' : c;
	c = (S_ISFIFO(st_mode)) ? 'p' : c;
	c = (S_ISLNK(st_mode)) ? 'l' : c;
	c = (S_ISSOCK(st_mode)) ? 's' : c;
	ft_putchar(c);
	ft_putchar((st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((st_mode & S_IXOTH) ? 'x' : '-');
}

static int		ft_display_long(const char *filename)
{
	t_stat		stat;
	t_passwd	*passwd;
	t_group		*group;
	char		*time_fmt;

	if (lstat(filename, &stat) < 0)
		return (ft_error(errno, filename));
	passwd = getpwuid(stat.st_uid);
	group = getgrgid(stat.st_gid);
	time_fmt = ft_strsub(ctime(&stat.st_mtimespec.tv_sec), 4, 12);
	ft_print_mode(stat.st_mode);
	ft_printf(" %hu %s %s %lld %s ",
		stat.st_nlink, passwd->pw_name, group->gr_name, stat.st_size, time_fmt);
	return (0);
}

static int		ft_display_name(const char *filename, int f_color)
{
	t_stat	stat;
	mode_t	mode;
	char	*color;

	color = "\033[0m";
	if (lstat(filename, &stat) < 0)
		return (ft_error(errno, filename));
	mode = stat.st_mode;
	if (f_color)
	{
		color = ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH)) ? 
									"\033[31m" : color;
		color = (S_ISDIR(mode)) ? "\033[34m" : color;
		color = (S_ISCHR(mode)) ? "\033[43;34m" : color;
		color = (S_ISBLK(mode)) ? "\033[43;34m" : color;
		color = (S_ISFIFO(mode)) ? "\033[100;32m" : color;
		color = (S_ISLNK(mode)) ? "\033[35m" : color;
		color = (S_ISSOCK(mode)) ? "\033[106;30m" : color;
	}
	ft_printf("%s%s\033[0m\n", color, filename);
	return (0);
}

int				ft_display(t_arg *arg, t_list *head)
{
	while (head)
	{
		if (arg->f_long)
			(void)ft_display_long(head->content);
		(void)ft_display_name(head->content, arg->f_color);
		head = head->next;
	}
	return (0);
}