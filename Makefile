# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elyzouli <elyzouli@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 05:25:19 by elyzouli          #+#    #+#              #
#    Updated: 2024/04/22 21:46:57 by elyzouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=pipex
NAME_BONUS = pipex_bonus
INCLUDES_DIR = INC
SRC_FILES = $(wildcard SRC/*.c)
OBJ = $(SRC_FILES:.c=.o)
SRCBNS_FILES = $(wildcard BONUS/*.c) $(wildcard GNL/*.c)
OBJBNS = $(SRCBNS_FILES:.c=.o)
CFLAGS = -g -Wall -Werror -Wextra -fsanitize=address

all: $(NAME)


$(NAME): $(OBJ)

	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)


bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(OBJBNS)
	$(CC) $(CFLAGS)  $(OBJBNS) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJBNS)

fclean: clean

	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
.SECONDARY : $(OBJ) $(OBJBNS)