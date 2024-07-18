# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rshaheen <rshaheen@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2024/06/24 16:44:43 by rshaheen      #+#    #+#                  #
#    Updated: 2024/07/18 17:58:42 by rshaheen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

MANDATORY_NAME = pipex

BONUS_NAME = pipex_bonus

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

OBJ_DIR = obj

SOURCE_MAN = main.c \
			parse_exe.c \
			errors_free.c
		
SOURCE_BONUS = main_bonus.c \
				heredoc_bonus.c \
				errors_free_bonus.c \
				execute_pipe_bonus.c \
				parse_exe_bonus.c

ifdef BONUS 
SOURCE = $(SOURCE_BONUS)
NAME = $(BONUS_NAME)
else
SOURCE = $(SOURCE_MAN)
NAME = $(MANDATORY_NAME)
endif

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

bonus:
	$(MAKE) BONUS=1 all

clean: 
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus