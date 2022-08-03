# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 17:40:10 by rvrignon          #+#    #+#              #
#    Updated: 2022/08/03 13:52:13 by rvrignon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  	ft_philo/main.c \
		ft_philo/src/utils.c \
		ft_philo/src/utils_two.c
		
OBJ		=	$(SRC:.c=.o)
CC		=	gcc
RM		=	rm -f
CFLAGS	=	-Wall -Werror -Wextra -g -pthread

NAME	=	ft_philo/philo.a

PROG	=	philo

all:		$(NAME)

$(NAME):	$(OBJ)
			@make re -C libft
			@cp libft/libft.a $(NAME)
			@ar rcs $(NAME) $(OBJ)
			@$(CC) $(CFLAGS) -o $(PROG) $(SRC) $(NAME)
			@echo "\033[1;32m"
			@echo "\033[4;36mPHILOO Mandatory"
			@echo "\033[4;32mGOOD WORK\033[0m"

clean:		
			$(MAKE) fclean -C ./libft
			$(RM) $(NAME) $(OBJ)
			@echo "\033[1;32m"
			@echo "\033[4;36mPhilo is now clean!\033[0m"
			@echo "\033[4;32mGOOD WORK\033[0m"
			clear

fclean:		clean
			$(MAKE) fclean -C ./libft
			$(RM) $(PROG)
			$(RM) *.txt
			@echo "\033[1;32m"
			@echo "\033[4;36mPHilo is now fcleaned!\033[0m"
			@echo "\033[4;32mGOOD WORK\033[0m"
			clear


re:			fclean $(NAME)

.PHONY:		all clean fclean re