# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: celva <celva@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 12:51:03 by celva             #+#    #+#              #
#    Updated: 2019/11/19 16:06:24 by celva            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS =	ft_printf.c \
		parsing_flags.c \
		parsing_type2.c \
		parsing_hashtag.c \
		parsing_type.c \
		float.c \
		insert_accuracy.c \
		line_creation.c \
		parsing_flags_main.c \
		insert_w_pars_spec.c \
		parsing_type3.c \
		f_parsing_type.c \
		basic_processing.c

LIBDIR = libft/
LIB = $(addprefix $(LIBDIR), libft.a)

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(LIB):
		make -C $(LIBDIR)

$(OBJECTS): %.o:%.c
		gcc -g -c -I $(LIBDIR) -Wall -Wextra -Werror $<

$(NAME): $(LIB) $(OBJECTS)
		@cp libft/libft.a ./$(NAME)
		@ar rc $(NAME) $(OBJECTS)
		@ranlib $(NAME)

clean:
		@/bin/rm -f $(OBJECTS)
		@make -C $(LIBDIR) clean

fclean: clean
		@/bin/rm -f $(NAME)
		@make -C $(LIBDIR) fclean

re:		fclean all

.PHONY: clean fclean all re
