/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proceed.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 10:11:49 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/06 09:41:57 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

static int	ft_first_proceed(t_arg *arg, t_list *head)
{
	t_stat	stat;
	t_list	*new;

	new = NULL;
	while (head)
	{
		if (lstat(head->content, &stat) < 0)
		{
			ft_error(errno, head->content);
			head = head->next;
			continue ;
		}
		if (!S_ISDIR(stat.st_mode))
			ft_lstadd(&new, ft_lstnew(head->content,
												ft_strlen(head->content) + 1));
		head = head->next;
	}
	if (new)
		ft_display(arg, ft_sort(new, arg));
	if (new && !(arg->f_long && arg->f_rec))
		ft_putchar('\n');
	ft_lstdel(&new, &ft_delnode);
	return (0);
}

static char	*ft_get_name(const char *parent, const char *name, int nam_len)
{
	char	*tmp;
	char	*del;
	char	*path;

	tmp = NULL;
	path = ft_strnew(nam_len + 1);
	ft_strncpy(path, name, nam_len);
	if (parent[ft_strlen(parent) - 1] != '/')
		tmp = ft_strjoin(parent, "/");
	del = path;
	path = ft_strjoin((tmp) ? tmp : parent, path);
	if (tmp)
		ft_strdel(&tmp);
	ft_strdel(&del);
	return (path);
}

static int	ft_lookthrough(t_list *head)
{
	int		dir;

	dir = 0;
	while (head)
	{
		dir++;
		head = head->next;
	}
	return (dir);
}

int			ft_opendir(const char *parent, t_arg *arg)
{
	DIR			*dirp;
	t_dirent	*entry;
	t_list		*head;
	char		*name;

	head = NULL;
	ft_show_name(parent, arg);
	if (!(dirp = opendir(parent)))
		return (ft_error(errno, parent));
	while ((entry = readdir(dirp)))
	{
		name = ft_get_name(parent, entry->d_name, entry->d_namlen);
		if (entry->d_name[0] != '.'
							|| (arg->f_all && ft_isvalid_file(entry->d_name)))
			ft_lstadd(&head, ft_lstnew(name, ft_strlen(name) + 1));
		ft_strdel(&name);
	}
	if (closedir(dirp) == -1)
		return (ft_error(errno, parent));
	ft_show_total(head, arg);
	ft_display(arg, ft_sort(head, arg));
	if (arg->f_rec)
		ft_proceed(arg, ft_sort(head, arg));
	ft_lstdel(&head, &ft_delnode);
	return (0);
}

int			ft_proceed(t_arg *arg, t_list *head)
{
	static int	first = 0;
	t_stat		stat;

	if (!first)
	{
		first++;
		if (ft_lookthrough(head) > 1)
			ft_show_name(NULL, arg);
		(void)ft_first_proceed(arg, head);
	}
	while (head)
	{
		if (lstat(head->content, &stat) < 0)
			return (1);
		if (S_ISDIR(stat.st_mode))
			ft_opendir(head->content, arg);
		head = head->next;
	}
	return (0);
}
