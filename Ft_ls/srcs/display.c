/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 12:41:00 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/06 13:37:20 by kcosta           ###   ########.fr       */
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
		return (1);
	passwd = getpwuid(stat.st_uid);
	group = getgrgid(stat.st_gid);
	time_fmt = ft_get_time(stat.st_mtimespec.tv_sec);
	ft_print_mode(stat.st_mode);
	if (S_ISCHR(stat.st_mode) || S_ISBLK(stat.st_mode))
		ft_printf(" %2hu %s %8s %9u, %3u %s ",
		stat.st_nlink, passwd->pw_name, group->gr_name,
		major(stat.st_rdev), minor(stat.st_rdev), time_fmt);
	else
		ft_printf(" %3hu %6s %11s %6lld %s ",
		stat.st_nlink, passwd->pw_name, group->gr_name, stat.st_size, time_fmt);
	ft_strdel(&time_fmt);
	return (0);
}

static int		ft_display_col(int max_size, int *current_col,
											const char *filename, int f_color)
{
	t_stat	stat;
	mode_t	mode;
	char	*file;

	file = ft_strrchr(filename + 1, '/');
	file = (!file) ? (char*)filename : file + 1;
	if (lstat(filename, &stat) < 0)
		return (1);
	*current_col += max_size;
	mode = stat.st_mode;
	ft_printf("%s%-*s\033[0m", ft_get_color(f_color, mode), max_size, file);
	return (0);
}

static int		ft_display_name(const char *filename, int f_color, int f_long)
{
	t_stat	stat;
	mode_t	mode;
	char	*file;
	char	buf[BUFF_SIZE];
	int		size;

	file = ft_strrchr(filename + 1, '/');
	file = (!file) ? (char*)filename : file + 1;
	if (lstat(filename, &stat) < 0)
		return (1);
	mode = stat.st_mode;
	ft_printf("%s%s\033[0m", ft_get_color(f_color, mode), file);
	if (f_long && S_ISLNK(mode))
	{
		if ((size = readlink(filename, buf, BUFF_SIZE)) < 0)
			return (ft_error(errno, filename));
		buf[size] = 0;
		ft_printf(" -> %s", buf);
	}
	ft_putchar('\n');
	return (0);
}

int				ft_display(t_arg *arg, t_list *head)
{
	struct winsize	ws;
	int				cur_col;
	int				max;

	ioctl(0, TIOCGWINSZ, &ws);
	cur_col = 0;
	max = ft_get_max_size(head);
	while (head)
	{
		if (arg->f_long)
			(void)ft_display_long(head->content);
		if (arg->f_long || arg->f_simple)
			(void)ft_display_name(head->content, arg->f_color, arg->f_long);
		else
			(void)ft_display_col(max, &cur_col, head->content, arg->f_color);
		head = head->next;
		if (head && (cur_col + max > ws.ws_col))
		{
			ft_putchar('\n');
			cur_col = 0;
		}
	}
	if (!arg->f_long && !arg->f_simple)
		ft_putchar('\n');
	return (0);
}
