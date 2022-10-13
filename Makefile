PREFIXE						= pipex
EXEC						= $(PREFIXE)

# *********************** DIRECTORY ************************************* #
SRCS_DIR					= src/
OBJ_DIR						= obj/
INC							= -I ./include/

# *********************** SOURCES **************************************** #
SRC							= 	pipex.c 			\
								parsing.c	 		\
								utils.c		 		\
								children.c			
SRCS						= $(addprefix $(SRCS_DIR), $(SRC))

# *********************** OBJECT ***************************************** #
OBJ							= $(SRC:.c=.o)
OBJS						= $(addprefix $(OBJ_DIR), $(OBJ))
$(OBJ_DIR)%.o				: $(SRCS_DIR)%.c
							@mkdir -p $(OBJ_DIR)
							@$(CC) $(CFLAGS) -c $< -o $@

# *********************** COMPILATION ************************************ #
CC							= cc

$(EXEC)						: libft/libft.a $(OBJS)
							@$(CC) $(CFLAGS) $(INC) $(OBJS) -L libft -lft -o $(EXEC)

# ********************** FLAGS ******************************************* #
CFLAGS						= -Wall -Wextra -Werror -g

all							: $(EXEC)

libft/libft.a				:
							@make -C libft

clean						: 
							@rm -rf $(OBJ_DIR)
							@make clean -C libft
					
fclean						: clean
							@rm -f $(EXEC)
							@make fclean -C libft

re							: fclean
							@make all

.PHONY						= all clean fclean re