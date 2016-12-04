/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 13:52:50 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/04 17:41:05 by kcosta           ###   ########.fr       */
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

t_list		*ft_sort_ascii(t_list *head)
{
	t_list	*tmp;
	int		sorted;

	if (!head)
		return (NULL);
	sorted = 0;
	while (!sorted)
	{
		tmp = head;
		sorted = 1;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->content, tmp->next->content) > 0)
			{
				ft_swap_str((char**)&tmp->content, (char**)&tmp->next->content);
				sorted = 0;
			}
			tmp = tmp->next;
		}
	}
	return (head);
}
