/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 12:40:14 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/05 23:09:05 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

static int	ft_usage(int opt)
{
	if (opt)
		ft_printf("ft_ls: illegal option -- %c\n", opt);
	ft_printf("usage: ./ft_ls [-1GRalrt] [file ...]\n");
	return (1);
}

static void	ft_init_arg(t_arg *arg)
{
	arg->f_rec = 0;
	arg->f_all = 0;
	arg->f_long = 0;
	arg->f_rev = 0;
	arg->f_time = 0;
	arg->f_color = 0;
	arg->f_simple = 0;
}

static int	ft_ls(int argc, char **argv, int ft_optind, t_arg *arg)
{
	t_list	*head;

	head = NULL;
	while (ft_optind < argc)
	{
		if (!head)
			head = ft_lstnew(argv[ft_optind], ft_strlen(argv[ft_optind]) + 1);
		else
			ft_lstadd(&head,
					ft_lstnew(argv[ft_optind], ft_strlen(argv[ft_optind]) + 1));
		ft_optind++;
	}
	if (!head)
		head = ft_lstnew(".", 2);
	return (ft_proceed(arg, ft_sort(head, arg)));
}

static int	ft_parse_arg(int argc, char **argv, int *ft_optind, t_arg *arg)
{
	int		c;
	ft_init_arg(arg);
	while ((c = ft_getopt(argc, argv, "1GRalrt", ft_optind)) > 0)
	{
		if (c == 'R')
			arg->f_rec = 1;
		else if (c == 'a')
			arg->f_all = 1;
		else if (c == 'l')
			arg->f_long = 1;
		else if (c == 'r')
			arg->f_rev = 1;
		else if (c == 't')
			arg->f_time = 1;
		else if (c == 'G')
			arg->f_color = 1;
		else if (c == '1')
			arg->f_simple = 1;
		else
			return (ft_usage(c));
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_arg	arg;
	int		ft_optind;

	ft_optind = 1;
	if (ft_parse_arg(argc, argv, &ft_optind, &arg))
		return (1);
	return (ft_ls(argc, argv, ft_optind, &arg));
}
