PREFIXE						= pipex
EXEC						= $(PREFIXE)
EXEC_BONUS					= $(PREFIXE)

# *********************** DIRECTORY ************************************* #
SRCS_DIR					= src/
OBJ_DIR						= obj/
BONUS_DIR					= bonus/src/
INC							= -I ./include/

# *********************** SOURCES **************************************** #
SRC							= 	pipex.c 			\
								parsing.c	 		\
								utils.c		 		\
								children.c			
SRCS						= $(addprefix $(SRCS_DIR), $(SRC))

# *********************** BONUS SOURCES ********************************** #
SRC_B						=	pipex_bonus.c 			\
								parsing_bonus.c	 		\
								utils_bonus.c		 		\
								children_bonus.c	
SRCS_B						= $(addprefix $(BONUS_DIR), $(SRC_B))

# *********************** OBJECT ***************************************** #
OBJ							= $(SRC:.c=.o)
OBJS						= $(addprefix $(OBJ_DIR), $(OBJ))

OBJ_B						= $(SRC_B:.c=.o)
OBJS_B						= $(addprefix $(OBJ_DIR), $(OBJ_B))

# *********************** BONUS OBJECT & DEPEDENCY *********************** #

$(OBJ_DIR)%.o				: $(SRCS_DIR)%.c
							@mkdir -p $(OBJ_DIR)
							@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o				: $(BONUS_DIR)%.c
							@mkdir -p $(OBJ_DIR)
							@$(CC) $(CFLAGS) -c $< -o $@

# *********************** COMPILATION ************************************ #
CC							= cc

$(EXEC)						: libft/libft.a $(OBJS)
							@$(CC) $(CFLAGS) $(INC) $(OBJS) -L libft -lft -o $(EXEC)

# ********************** FLAGS ******************************************* #
CFLAGS						= -Wall -Wextra -Werror -g

all							: $(EXEC)

bonus						: clean libft/libft.a $(OBJS_B)
							@$(CC) $(CFLAGS) $(INC) $(OBJS_B) -L libft -lft -o $(EXEC_BONUS)

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

.PHONY						= all clean fclean bonus re