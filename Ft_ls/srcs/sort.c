/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 13:52:50 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/05 20:49:41 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"

static void	ft_swap_str(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

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

static t_list	*ft_rev_sort_ascii(t_list *head)
{
	t_list	*top;
	t_list	*cursor;

	top = head;
	while (top)
	{
		cursor = top->next;
		while (cursor)
		{
			if (ft_strcmp(top->content, cursor->content) < 0)
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
	t_list	*cursor;
	t_stat	stat2;

	top = head;
	while (top)
	{
		cursor = top->next;
		while (cursor)
		{
			if ((lstat(top->content, stat) > 0)
				&& lstat(cursor->content, &stat2) > 0)
				if (stat->st_mtimespec.tv_sec < stat2.st_mtimespec.tv_sec)
					ft_swap_str((char**)&top->content,
													(char**)&cursor->content);
			cursor = cursor->next;
		}
		top = top->next;
	}
	return (head);
}

static t_list	*ft_rev_sort_time(t_list *head, t_stat *stat)
{
	t_list	*top;
	t_list	*cursor;
	t_stat	stat2;

	top = head;
	while (top)
	{
		cursor = top->next;
		while (cursor)
		{
			if ((lstat(top->content, stat) > 0)
				&& lstat(cursor->content, &stat2) > 0)
				if (stat->st_mtimespec.tv_sec > stat2.st_mtimespec.tv_sec)
					ft_swap_str((char**)&top->content,
													(char**)&cursor->content);
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
	{
		if (arg->f_rev)
			head = ft_rev_sort_time(head, &stat);
		else
			head = ft_sort_time(head, &stat);
	}
	else if (arg->f_rev)
		head = ft_rev_sort_ascii(head);
	else
		head = ft_sort_ascii(head);
	return (head);
}
