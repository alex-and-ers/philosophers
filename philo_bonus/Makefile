# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sebonie <sebonie@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 14:36:30 by sebonie           #+#    #+#              #
#    Updated: 2022/05/18 15:30:38 by sebonie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo
NAME_BONUS		= philo_bonus

SRCS 			= philosophers.c phil_lifecycle.c aux.c \
				monitor.c aux_lib.c
SRCS_BONUS		= philosophers_bonus.c phil_life_bon.c \
				aux_bon.c aux_lib_bon.c

HEADER			= philosophers.h
HEADER_BONUS	= philosophers_bonus.h

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

bonus: $(NAME_BONUS)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean $(NAME_BONUS)