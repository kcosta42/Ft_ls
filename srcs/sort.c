/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 13:52:50 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/06 12:23:39 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static t_list	*ft_sort_ascii(t_list *head)
{
	t_list	*top;
	t_list	*cursor;

	top = head;
	while (top)
	{
		cursor = top->next;
		while (cursor)
		{
			if (ft_strcmp(top->content, cursor->content) > 0)
				ft_swap_str((char**)&top->content, (char**)&cursor->content);
			cursor = cursor->next;
		}
		top = top->next;
	}
	return (head);
}

static t_list	*ft_sort_time(t_list *head, t_stat *stat)
{
	t_list	*top;
	t_list	*cur;
	t_stat	stat2;

	top = head;
	while (top)
	{
		cur = top->next;
		while (cur)
		{
			lstat(top->content, stat);
			lstat(cur->content, &stat2);
			if (stat->st_mtimespec.tv_sec < stat2.st_mtimespec.tv_sec)
				ft_swap_str((char**)&top->content, (char**)&cur->content);
			else if (stat->st_mtimespec.tv_sec == stat2.st_mtimespec.tv_sec)
				if (ft_strcmp(top->content, cur->content) > 0)
					ft_swap_str((char**)&top->content, (char**)&cur->content);
			cur = cur->next;
		}
		top = top->next;
	}
	return (head);
}

static t_list	*ft_sort_rev(t_list *head)
{
	t_list	*top;
	t_list	*cursor;

	top = head;
	while (top)
	{
		cursor = top->next;
		while (cursor)
		{
			ft_swap_str((char**)&top->content, (char**)&cursor->content);
			cursor = cursor->next;
		}
		top = top->next;
	}
	return (head);
}

t_list			*ft_sort(t_list *head, t_arg *arg)
{
	t_stat	stat;

	if (arg->f_time)
		head = ft_sort_time(head, &stat);
	else
		head = ft_sort_ascii(head);
	if (arg->f_rev)
		head = ft_sort_rev(head);
	return (head);
}
