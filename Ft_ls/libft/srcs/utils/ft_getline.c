/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:00:28 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 17:20:16 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "ft_list.h"
#include "ft_string.h"
#include "ft_memory.h"

static t_list	*create_new_file(const int fd)
{
	t_list		*file;

	file = ft_lstnew(NULL, 0);
	file->content_size = fd;
	return (file);
}

static void		delete_file(const int fd, t_list **files)
{
	t_list	*tmp;

	tmp = *files;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
		{
			tmp->content_size = -1;
			tmp->content = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

static t_list	*find_file(const int fd, t_list **files)
{
	t_list	*tmp;

	tmp = *files;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = create_new_file(fd);
	ft_lstadd(files, tmp);
	return (tmp);
}

static int		read_line(const int fd, char **stock, char **sub)
{
	char	*buff;
	char	*tmp;
	int		read_ret;

	buff = ft_strnew(BUFF_SIZE);
	read_ret = read(fd, buff, BUFF_SIZE);
	*sub = NULL;
	if (!*stock)
		*stock = ft_strnew(0);
	while (!*sub && read_ret > 0)
	{
		*sub = ft_strchr(*stock, '\n');
		tmp = *stock;
		*stock = ft_strjoin(*stock, buff);
		ft_strdel(&tmp);
		ft_strclr(buff);
		if (!*sub)
			read_ret = read(fd, buff, BUFF_SIZE);
	}
	ft_strdel(&buff);
	return (read_ret);
}

int				ft_getline(const int fd, char **line)
{
	static t_list	*files = NULL;
	t_list			*file;
	char			*sub;
	char			*tmp;

	if (fd < 0 || !line)
		return (-1);
	file = find_file(fd, &files);
	if (read_line(fd, (char**)(&file->content), &sub) == -1)
		return (-1);
	if (!file->content || !(ft_strcmp(file->content, "")))
	{
		delete_file(fd, &files);
		return (0);
	}
	if ((sub = ft_strchr(file->content, '\n')) == NULL)
		if ((sub = ft_strchr(file->content, '\0')) == NULL)
			return (0);
	*line = ft_strsub(file->content, 0, sub - (char*)file->content);
	tmp = file->content;
	file->content = ft_strdup(sub + (*sub > 0));
	ft_strdel(&tmp);
	return (1);
}
