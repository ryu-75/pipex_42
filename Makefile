PREFIXE						= pipex
EXEC						= $(PREFIXE)
DEBUG						= yes

SRCS_DIR					= src
SRCS						= $(SRCS_DIR)/pipex.c 			\
								$(SRCS_DIR)/parsing.c 		\
								$(SRCS_DIR)/utils.c 		\
								$(SRCS_DIR)/children.c	

BONUS						= bonus/src
SRCS_BONUS					= $(BONUS)/pipex.c 			\
								$(BONUS)/parsing.c 		\
								$(BONUS)/utils.c 		\
								$(BONUS)/children.c	


OBJ							= $(SRCS:.c=.o)
DEP							= $(SRCS:.c=.d)
OBJ_BONUS					= $(SRCS_BONUS:.c=.o)
DEP_BONUS					= $(SRCS_BONUS:.c=.d)

%.o							: %.c
							$(CC) -c $(CFLAGS) $*.c -o $*.o
							$(CC) -MM $(CFLAGS) $*.c -o $*.d

CC							= cc

$(EXEC)						: libft/libft.a $(OBJ)
							$(CC) $(CFLAGS) $(OBJ) -L libft -lft -o $(EXEC)

CFLAGS						= -Wall -Wextra -Werror

all							: $(EXEC)

bonus						: $(OBJ) $(OBJ_BONUS)

libft/libft.a				:
							make -C libft

clean						: 
							rm -f $(OBJ) $(DEP) $(OBJ_BONUS) $(DEP_BONUS)
							rm -rf obj
							make clean -C libft
					
fclean						: clean
							rm -f $(EXEC)
							make fclean -C libft

re							: fclean
							@make all

.PHONY						= all clean fclean bonus re