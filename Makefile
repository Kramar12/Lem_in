# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/11 15:21:59 by ariabyi           #+#    #+#              #
#    Updated: 2018/09/30 16:32:41 by ariabyi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:         all clean fclean re $(NAME)

CC = gcc
NAME = lem_in
SRC = main.c get_ways.c

CFLAGS = #-Wall -Wextra -Werror
HEADER = -I ./header
LIBINCL = -L. libft/libft.a
LIBDIR = ./libft
OBJFOLD = ./obj/
OBJ = $(addprefix $(OBJFOLD),$(patsubst %.c, %.o, $(SRC)))
all:            $(NAME)
$(NAME):        $(OBJ)
	@make -C $(LIBDIR) -f Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBINCL) $(LIBPRINTINCL)
	@echo "lem_in: done"
$(OBJFOLD)%.o: %.c
	@mkdir -p $(OBJFOLD)
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<
clean:
	@rm -rf $(OBJFOLD)
	@make -C $(LIBDIR) -f Makefile clean
	@echo "objects removed"
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBDIR) -f Makefile fclean
	@echo "binary removed"
re:             fclean all

