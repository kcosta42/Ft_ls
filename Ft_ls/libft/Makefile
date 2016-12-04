#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/11/02 10:00:00 by kcosta            #+#    #+#             *#
#*   Updated: 2016/12/04 18:17:59 by kcosta           ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

BOLD = $(shell echo "\033[1m")
BOLD_END = $(shell echo "\033[21m")
RED = $(shell echo "\033[31m")
GREEN = $(shell echo "\033[32m")
YELLOW = $(shell echo "\033[33m")
BLUE = $(shell echo "\033[34m")
MAGENTA = $(shell echo "\033[35m")
EOC = $(shell echo "\033[0m")

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS_PATH = srcs/
INCLUDES_PATH = includes/
INCLUDES =	libft.h \
			ft_string.h \
			ft_ctype.h \
			ft_memory.h \
			ft_utils.h \
			ft_print.h \
			ft_list.h
FILES =	string/ft_strcat.c \
		string/ft_strclr.c \
		string/ft_strchr.c \
		string/ft_strdel.c \
		string/ft_strcmp.c \
		string/ft_strcpy.c \
		string/ft_strequ.c \
		string/ft_striter.c \
		string/ft_strdup.c \
		string/ft_strlen.c \
		string/ft_striteri.c \
		string/ft_strlcat.c \
		string/ft_strjoin.c \
		string/ft_strmap.c \
		string/ft_strncat.c \
		string/ft_strmapi.c \
		string/ft_strnequ.c \
		string/ft_strncmp.c \
		string/ft_strncpy.c \
		string/ft_strnew.c \
		string/ft_strrev.c \
		string/ft_strrchr.c \
		string/ft_strnstr.c \
		string/ft_strsub.c \
		string/ft_strstr.c \
		string/ft_strtrim.c \
		string/ft_strsplit.c \
		ctype/ft_isalnum.c \
		ctype/ft_isascii.c \
		ctype/ft_isblank.c \
		ctype/ft_isdigit.c \
		ctype/ft_isalpha.c \
		ctype/ft_islower.c \
		ctype/ft_isspace.c \
		ctype/ft_isupper.c \
		ctype/ft_toupper.c \
		ctype/ft_tolower.c \
		ctype/ft_isprint.c \
		memory/ft_bzero.c \
		memory/ft_memalloc.c \
		memory/ft_memccpy.c \
		memory/ft_memcpy.c \
		memory/ft_memdel.c \
		memory/ft_memchr.c \
		memory/ft_memcmp.c \
		memory/ft_memset.c \
		memory/ft_memmove.c \
		memory/ft_memdup.c \
		utils/ft_atoi.c \
		utils/ft_itoa.c \
		utils/ft_getline.c \
		utils/ft_getopt.c \
		print/ft_printf_address.c \
		print/ft_printf_check.c \
		print/ft_printf.c \
		print/ft_printf_char.c \
		print/ft_printf_args.c \
		print/ft_printf_pourcent.c \
		print/ft_printf_octal.c \
		print/ft_printf_hex.c \
		print/ft_printf_str.c \
		print/ft_putchar.c \
		print/ft_putchar_fd.c \
		print/ft_putendl.c \
		print/ft_printf_wildcard.c \
		print/ft_putendl_fd.c \
		print/ft_putnbr_fd.c \
		print/ft_putnbr.c \
		print/ft_putnstr.c \
		print/ft_putstr.c \
		print/ft_putstr_fd.c \
		print/ft_printf_unsigned.c \
		print/ft_printf_num.c \
		list/ft_lstadd.c \
		list/ft_lstdelone.c \
		list/ft_lstaddback.c \
		list/ft_lstdel.c \
		list/ft_lstiter.c \
		list/ft_lstmap.c \
		list/ft_lstnew.c
SRCS = $(addprefix $(SRCS_PATH), $(FILES))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@/bin/echo -n $(YELLOW)[$(GREEN)$(BOLD)Compiling $(BLUE)$(notdir $@) $(EOC)$(YELLOW)...]- -$(EOC)
	@$(CC) $(FLAGS) -I $(INCLUDES_PATH) -c -o $@ $<
	@/bin/echo "$(YELLOW)[$(BOLD)$(GREEN)Done!$(EOC)$(YELLOW)]$(EOC)"

$(NAME): $(OBJS)
	@/bin/echo $(YELLOW)[$(MAGENTA)$(BOLD)Creating $(BLUE)$(NAME) $(EOC)$(YELLOW)...]$(EOC)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@/bin/echo "$(YELLOW)[$(BOLD)$(BLUE)$(NAME) $(MAGENTA)Created!$(EOC)$(YELLOW)]$(EOC)"

.PHONY: clean

clean:
	@/bin/echo "$(YELLOW)[$(RED)$(BOLD)Cleaning $(EOC)$(YELLOW)...]$(EOC)"
	@/bin/rm -f $(OBJS)
	@/bin/echo "$(YELLOW)[$(RED)$(BOLD)All .o Removed!$(EOC)$(YELLOW)]$(EOC)"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/echo "$(YELLOW)[$(BOLD)$(BLUE)$(NAME) $(RED)Removed!$(EOC)$(YELLOW)]$(EOC)"

re: fclean all
