# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: GitHub Copilot <githubcopilot@student.42.fr>#+#  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 17:23:27 by GitHub Copilot    #+#    #+#              #
#    Updated: 2025/03/28 17:23:56 by GitHub Copilot   ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = main.c routine.c utils.c utils2.c
OBJS = $(SRCS:.c=.o)
NAME = philo

#colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Rules
all: $(NAME)
	@${MAKE} --no-print-directory clean

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${CYAN}$(NAME) compiled successfully!${RESET}"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "${MAGENTA}Object files cleaned!${RESET}"

fclean: clean
	@rm -f $(NAME)
	@echo "${MAGENTA}Binaries cleaned!${RESET}"

re: fclean all
	@${MAKE} --no-print-directory clean