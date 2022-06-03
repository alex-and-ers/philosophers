# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 17:10:04 by sebonie           #+#    #+#              #
#    Updated: 2022/05/18 15:30:31 by sebonie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo

SRCS 			= philosophers.c phil_lifecycle.c aux.c \
				monitor.c aux_lib.c

HEADER			= philosophers.h

OBJS 			= $(SRCS:.c=.o)
OBJS_BONUS 		= $(SRCS_BONUS:.c=.o)

FLAGS 			= -Wextra -Werror -Wall

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME) 

$(NAME_BONUS): $(OBJS_BONUS)
	gcc $(FLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o : %.c
	gcc $(FLAGS) -c $<

$(OBJS): $(HEADER)

$(OBJS_BONUS): $(HEADER_BONUS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all
