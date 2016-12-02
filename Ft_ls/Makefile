#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/12/02 14:01:12 by kcosta            #+#    #+#             *#
#*   Updated: 2016/12/02 15:02:41 by kcosta           ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = ft_ls
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/
LIB = -L $(LIBFT) -lft
INCLUDES = -I includes/ -I libft/includes/
SRCS_PATH = srcs/
FILES = ft_ls.c
SRCS = $(addprefix $(SRCS_PATH), $(FILES))
OBJS = $(SRCS:.c=.o)

all : lib $(NAME)

lib :
	@make -C $(LIBFT)

%.o : %.c
	$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(INCLUDES) $(OBJS) $(LIB)

clean :
	@make -C $(LIBFT) clean
	/bin/rm -f $(OBJS)

fclean : clean
	@make -C $(LIBFT) fclean
	/bin/rm -f $(NAME)

re : fclean all
