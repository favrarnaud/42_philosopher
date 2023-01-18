# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afavre <afavre@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 07:40:52 by afavre            #+#    #+#              #
#    Updated: 2023/01/12 07:26:38 by afavre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
NAME		= philo

SRC_PATH	= src/
OBJ_PATH	= obj/

SRC			= main error_handler utils initialisation run str_utils
SRCS		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(addsuffix .o, $(OBJ)))
INCS		= -I includes/

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
		@mkdir $(OBJ_PATH)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread -D_REENTRANT
		@echo "$(GREEN)Allez cette fois a toi de bosser !$(DEF_COLOR)"

clean:
		@rm -rf $(OBJ_PATH)
		@echo "$(CYAN)C'est tout de suite mieux !$(DEF_COLOR)"

fclean: clean
		@rm -f $(NAME)
		@rm -rf $(LIB_NAME)
		@echo "$(BLUE)Et ben ! ca fait de la place !$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re