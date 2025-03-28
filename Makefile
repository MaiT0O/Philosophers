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
SRCS = 
OBJS = $(SRCS:.c=.o)
NAME = philo

# Rules
all: $(NAME)
	@${MAKE} --print-no-directory clean

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Object files cleaned!"

fclean: clean
	@rm -f $(NAME)
	@echo "Binaries cleaned!"

re: fclean all
	@${MAKE} --print-no-directory clean