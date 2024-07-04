# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rshaheen <rshaheen@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2024/06/24 16:44:43 by rshaheen      #+#    #+#                  #
#    Updated: 2024/07/03 16:32:11 by rshaheen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror #g -fsanitize=address

OBJ_DIR = obj

SOURCE = main.c \
		split.c \
		errors_free.c

OBJECTS = $(SOURCE:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)/%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJECTS)
	@cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

clean: 
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re