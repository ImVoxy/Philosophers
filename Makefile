# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alpascal <alpascal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/29 16:34:58 by alpascal          #+#    #+#              #
#    Updated: 2021/12/23 13:27:17 by alpascal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = `tput setaf 2`
RED = `tput setaf 1`
END = `tput sgr0`

NAME 				= philo

INCLUDES 			= -lpthread

HEADER				= -Iincludes

PHILOSOPHERS_NAME	= philo.c \
						loop.c \
						utils.c

OBJ_PHILOSOPHERS 	= $(SRC_PHILOSOPHERS:.c=.o)
SRCS_PATH			= srcs

SRC					= $(addprefix $(SRCS_PATH)/,$(SRC_NAME))
SRC_PHILOSOPHERS	= $(addprefix $(SRCS_PATH)/,$(PHILOSOPHERS_NAME))
RM 					= rm -rf
CC 					= clang
MEM					= -g -O3 -fsanitize=address

all:	$(NAME)

$(NAME): $(OBJ)$(OBJ_PHILOSOPHERS)
	$(CC) -Wall -Wextra -Werror $(OBJ_PHILOSOPHERS) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)$(NAME) binary is ready !$(END)"

%.o: %.c $(HEADER)
	@echo "$(GREEN)Compiling source files to objects $<$ ...$(END)"
	$(CC) -Wall -Wextra -Werror $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_PHILOSOPHERS)

fclean:		clean
	$(RM) $(NAME) a.out vgcore.*
	@echo "$(RED)$(NAME) removed$(END)"

re: clean fclean all
