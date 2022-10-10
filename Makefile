PREFIXE						= pipex
EXEC						= $(PREFIXE)


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
SRC_B						=	pipex.c 			\
								parsing.c	 		\
								utils.c		 		\
								children_bonus.c	
SRCS_B						= $(addprefix $(BONUS_DIR), $(SRC_B))

# *********************** OBJECT & DEPENDENCIES ************************* #
OBJ							= $(SRC:.c=.o)
OBJS						= $(addprefix $(OBJ_DIR), $(OBJ))

OBJ_B						= $(SRC_B:.c=.o)
OBJS_B						= $(addprefix $(OBJ_DIR), $(OBJ_B))

# *********************** BONUS OBJECT & DEPEDENCY ********************** #

$(OBJ_DIR)%.o				: $(SRCS_DIR)%.c
							@mkdir -p $(OBJ_DIR)
							$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_DIR)%.o				: $(BONUS_DIR)%.c
							@mkdir -p $(OBJ_DIR)
							$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# *********************** COMPILATION *********************************** #
CC							= cc

$(EXEC)						: libft/libft.a $(OBJS)
							$(CC) $(CFLAGS) $(OBJS) -L libft -lft -o $(EXEC)

# ********************** FLAGS ****************************************** #
CFLAGS						= -Wall -Wextra -Werror

all							: $(EXEC)

bonus						: clean $(EXEC) libft/libft.a $(OBJS_B)
							$(CC) $(CFLAGS) $(OBJS_B) -L libft -lft -o $(EXEC)

libft/libft.a				:
							make -C libft

clean						: 
							rm -rf $(OBJ_DIR)
							make clean -C libft
					
fclean						: clean
							rm -f $(EXEC)
							make fclean -C libft

re							: fclean
							@make all

.PHONY						= all clean fclean bonus re