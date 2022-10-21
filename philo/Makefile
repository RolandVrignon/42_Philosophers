# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 14:32:28 by rvrignon          #+#    #+#              #
#    Updated: 2022/10/22 01:54:55 by rvrignon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
CC				= 	gcc
FLAGS			= 	-fsanitize=thread -Wall -Wextra -Werror -pthread

### EXECUTABLE ###
NAME			= 	philo

### PATHS ###
INCLUDE			= 	includes
SRC_PATH		= 	src
OBJ_PATH		= 	obj

### SOURCE FILES ###
SOURCES			 =	main.c \
					threads_one.c \
					threads_two.c \
					threads_utils.c \
					threads_utils_two.c \
					utils.c \
					utils_two.c \

### OBJECTS ###
SRC				= 	$(addprefix $(SRC_PATH)/,$(SOURCES))
OBJ				= 	$(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

### COLORS ###
NOC				= 	\033[0m
RED				= 	\033[1;31m
GREEN			= 	\033[1;32m
YELLOW			= 	\033[1;33m
BLUE			= 	\033[1;34m
WHITE			= 	\033[1;37m

### RULES ###

# ------- ALL

all: 	$(NAME)

$(NAME): $(OBJ)
	@$(CC) $^ $(FLAGS) -o $(NAME)
	@echo "$(GREEN)$@ ✅$(NOC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCLUDE)/$(NAME).h
	@mkdir -p obj
	@$(CC) $(FLAGS) -I$(INCLUDE) -c -o $@ $<
	@echo "$(BLUE)gcc $(WHITE)$(notdir $@)$(NOC)"

# ------- Clean

clean:
	@echo "$(RED)clean$(NOC)"
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(RED)fclean$(NOC)"
	@rm -f $(NAME)

re: fclean all

# ------- Gadget

norm:
	-@norminette $(SRC_PATH)
	-@norminette $(INCLUDE)

push: fclean
	git add .
	git status
	git commit -m philo
	git push

.PHONY:	 default mandatory clean fclean re norm push