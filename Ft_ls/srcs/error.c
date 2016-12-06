/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 18:43:57 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/06 12:23:27 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

int			ft_error(int errnum, const char *filename)
{
	if (filename)
		ft_printf("ft_ls: %s: %s\n", filename, strerror(errnum));
	else
		ft_printf("ft_ls: %s\n", strerror(errnum));
	return (errnum);
}

int			ft_isvalid_file(char *filename)
{
	if (filename[ft_strlen(filename) - 1] == '.')
		return (0);
	if (filename[ft_strlen(filename) - 1] == '.'
		&& filename[ft_strlen(filename) - 2] == '.')
		return (0);
	return (1);
}

static int	ft_display_invalid_file(const char *parent, t_arg *arg)
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
		if (entry->d_name[0] != '.' || arg->f_all)
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

int			ft_open_invalid_dir(t_arg *arg, t_list *head)
{
	while (head)
	{
		if (!ft_isvalid_file(head->content))
			ft_display_invalid_file(head->content, arg);
		head = head->next;
	}
	return (0);
}
